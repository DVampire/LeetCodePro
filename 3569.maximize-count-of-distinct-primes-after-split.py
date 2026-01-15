#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
from typing import List

class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        MAX_VAL = 10**5 + 1
        is_prime = [True] * MAX_VAL
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(MAX_VAL**0.5) + 1):
            if is_prime[i]:
                for j in range(i*i, MAX_VAL, i):
                    is_prime[j] = False
        
        n = len(nums)
        
        tree = [0] * (4 * n)
        lazy = [0] * (4 * n)
        
        def push_down(node):
            if lazy[node] != 0:
                tree[2*node] += lazy[node]
                tree[2*node+1] += lazy[node]
                lazy[2*node] += lazy[node]
                lazy[2*node+1] += lazy[node]
                lazy[node] = 0
        
        def range_add(node, start, end, l, r, val):
            if l > r or r < start or end < l:
                return
            if l <= start and end <= r:
                tree[node] += val
                lazy[node] += val
                return
            push_down(node)
            mid = (start + end) // 2
            range_add(2*node, start, mid, l, r, val)
            range_add(2*node+1, mid+1, end, l, r, val)
            tree[node] = max(tree[2*node], tree[2*node+1])
        
        prime_occ = {}
        prime_first = {}
        prime_last = {}
        
        def add_prime_contribution(f, l):
            range_add(1, 1, n-1, f+1, n-1, 1)
            range_add(1, 1, n-1, 1, l, 1)
        
        def remove_prime_contribution(f, l):
            range_add(1, 1, n-1, f+1, n-1, -1)
            range_add(1, 1, n-1, 1, l, -1)
        
        def add_occurrence(p, idx):
            if p in prime_occ:
                old_f, old_l = prime_first[p], prime_last[p]
                prime_occ[p].add(idx)
                new_f = min(old_f, idx)
                new_l = max(old_l, idx)
                if new_f != old_f or new_l != old_l:
                    remove_prime_contribution(old_f, old_l)
                    prime_first[p] = new_f
                    prime_last[p] = new_l
                    add_prime_contribution(new_f, new_l)
            else:
                prime_occ[p] = {idx}
                prime_first[p] = idx
                prime_last[p] = idx
                add_prime_contribution(idx, idx)
        
        def remove_occurrence(p, idx):
            if p not in prime_occ:
                return
            old_f, old_l = prime_first[p], prime_last[p]
            prime_occ[p].remove(idx)
            if prime_occ[p]:
                if idx == old_f or idx == old_l:
                    remove_prime_contribution(old_f, old_l)
                    prime_first[p] = min(prime_occ[p])
                    prime_last[p] = max(prime_occ[p])
                    add_prime_contribution(prime_first[p], prime_last[p])
            else:
                remove_prime_contribution(old_f, old_l)
                del prime_occ[p]
                del prime_first[p]
                del prime_last[p]
        
        for i, num in enumerate(nums):
            if is_prime[num]:
                add_occurrence(num, i)
        
        results = []
        for idx, val in queries:
            old_val = nums[idx]
            
            if old_val != val:
                if is_prime[old_val]:
                    remove_occurrence(old_val, idx)
                
                nums[idx] = val
                
                if is_prime[val]:
                    add_occurrence(val, idx)
            
            max_val = tree[1]
            results.append(max(0, max_val))
        
        return results
# @lc code=end