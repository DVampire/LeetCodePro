#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        MAX_VAL = 100001
        is_prime = [True] * MAX_VAL
        is_prime[0] = is_prime[1] = False
        for p in range(2, int(MAX_VAL**0.5) + 1):
            if is_prime[p]:
                for i in range(p * p, MAX_VAL, p):
                    is_prime[i] = False
        
        n = len(nums)
        tree_size = 1
        while tree_size < n: tree_size *= 2
        tree = [0] * (2 * tree_size)
        lazy = [0] * (2 * tree_size)

        def update(l, r, val, node, start, end):
            if lazy[node] != 0:
                tree[node] += lazy[node]
                if start != end:
                    lazy[2 * node] += lazy[node]
                    lazy[2 * node + 1] += lazy[node]
                lazy[node] = 0
            if start > end or start > r or end < l: return
            if start >= l and end <= r:
                tree[node] += val
                if start != end:
                    lazy[2 * node] += val
                    lazy[2 * node + 1] += val
                return
            mid = (start + end) // 2
            update(l, r, val, 2 * node, start, mid)
            update(l, r, val, 2 * node + 1, mid + 1, end)
            tree[node] = max(tree[2 * node], tree[2 * node + 1])

        prime_indices = collections.defaultdict(SortedList)
        for i, v in enumerate(nums):
            if is_prime[v]: prime_indices[v].add(i)

        def update_prime_contribution(p, delta):
            if not prime_indices[p]: return
            first, last = prime_indices[p][0], prime_indices[p][-1]
            if first + 1 <= n - 1: update(first + 1, n - 1, delta, 1, 1, n - 1)
            if 1 <= last: update(1, last, delta, 1, 1, n - 1)

        for p in prime_indices: update_prime_contribution(p, 1)

        results = []
        for idx, val in queries:
            old_val = nums[idx]
            if old_val != val:
                if is_prime[old_val]:
                    update_prime_contribution(old_val, -1)
                    prime_indices[old_val].remove(idx)
                    update_prime_contribution(old_val, 1)
                nums[idx] = val
                if is_prime[val]:
                    update_prime_contribution(val, -1)
                    prime_indices[val].add(idx)
                    update_prime_contribution(val, 1)
            results.append(tree[1])
        return results

from sortedcontainers import SortedList
import collections
# @lc code=end