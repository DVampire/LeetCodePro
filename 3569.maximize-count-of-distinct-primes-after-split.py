#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
import heapq

class SegmentTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (4 * n)
        self.lazy = [0] * (4 * n)

    def _push(self, node):
        if self.lazy[node] != 0:
            self.tree[2 * node] += self.lazy[node]
            self.lazy[2 * node] += self.lazy[node]
            self.tree[2 * node + 1] += self.lazy[node]
            self.lazy[2 * node + 1] += self.lazy[node]
            self.lazy[node] = 0

    def update(self, node, start, end, l, r, val):
        if l > end or r < start:
            return
        if l <= start and end <= r:
            self.tree[node] += val
            self.lazy[node] += val
            return
        self._push(node)
        mid = (start + end) // 2
        self.update(2 * node, start, mid, l, r, val)
        self.update(2 * node + 1, mid + 1, end, l, r, val)
        self.tree[node] = max(self.tree[2 * node], self.tree[2 * node + 1])

    def query(self, node, start, end, l, r):
        if l > end or r < start:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        self._push(node)
        mid = (start + end) // 2
        return max(self.query(2 * node, start, mid, l, r), 
                   self.query(2 * node + 1, mid + 1, end, l, r))

# Precompute primes up to 10^5 + 5
MAX_VAL = 100005
is_prime = [True] * MAX_VAL
is_prime[0] = is_prime[1] = False
for i in range(2, int(MAX_VAL**0.5) + 1):
    if is_prime[i]:
        for j in range(i*i, MAX_VAL, i):
            is_prime[j] = False

class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        st = SegmentTree(n)
        
        # Structures to manage prime indices
        # active_indices[p] = set of indices where p appears
        # min_heap[p] = min heap of indices
        # max_heap[p] = max heap of negative indices (to simulate max heap)
        active_indices = {}
        min_heap = {}
        max_heap = {}
        
        distinct_primes_count = 0
        
        def get_range(p):
            # Clean heaps
            while min_heap[p] and min_heap[p][0] not in active_indices[p]:
                heapq.heappop(min_heap[p])
            while max_heap[p] and (-max_heap[p][0]) not in active_indices[p]:
                heapq.heappop(max_heap[p])
            
            if not min_heap[p]: return -1, -1
            return min_heap[p][0], -max_heap[p][0]

        def add_prime_idx(p, idx):
            nonlocal distinct_primes_count
            if p not in active_indices:
                active_indices[p] = set()
                min_heap[p] = []
                max_heap[p] = []
                distinct_primes_count += 1
            
            if not active_indices[p]: # Was empty, now getting first element
                active_indices[p].add(idx)
                heapq.heappush(min_heap[p], idx)
                heapq.heappush(max_heap[p], -idx)
                # Range is [idx, idx], L < R is false, no tree update
                return

            # Already had elements. Remove old contribution.
            l, r = get_range(p)
            if l < r:
                st.update(1, 0, n - 1, l + 1, r, -1)
            
            active_indices[p].add(idx)
            heapq.heappush(min_heap[p], idx)
            heapq.heappush(max_heap[p], -idx)
            
            # Add new contribution
            l_new, r_new = get_range(p)
            if l_new < r_new:
                st.update(1, 0, n - 1, l_new + 1, r_new, 1)

        def remove_prime_idx(p, idx):
            nonlocal distinct_primes_count
            # Assumes p is in active_indices and idx is in it
            l, r = get_range(p)
            if l < r:
                st.update(1, 0, n - 1, l + 1, r, -1)
            
            active_indices[p].remove(idx)
            
            if not active_indices[p]:
                distinct_primes_count -= 1
                return
            
            l_new, r_new = get_range(p)
            if l_new < r_new:
                st.update(1, 0, n - 1, l_new + 1, r_new, 1)

        # Initial build
        # Instead of calling add_prime_idx repeatedly which does tree updates,
        # we can batch build. But N is small enough to just loop.
        # Optimization: group indices first then update tree.
        initial_indices = {}
        for i, x in enumerate(nums):
            if is_prime[x]:
                if x not in initial_indices:
                    initial_indices[x] = []
                initial_indices[x].append(i)
        
        for p, idxs in initial_indices.items():
            distinct_primes_count += 1
            active_indices[p] = set(idxs)
            min_heap[p] = list(idxs)
            heapq.heapify(min_heap[p])
            max_heap[p] = [-i for i in idxs]
            heapq.heapify(max_heap[p])
            
            l, r = idxs[0], idxs[-1]
            if l < r:
                st.update(1, 0, n - 1, l + 1, r, 1)

        ans = []
        for idx, val in queries:
            old_val = nums[idx]
            if old_val != val:
                if is_prime[old_val]:
                    remove_prime_idx(old_val, idx)
                
                nums[idx] = val
                
                if is_prime[val]:
                    add_prime_idx(val, idx)
            
            if distinct_primes_count == 0:
                ans.append(0)
            else:
                # Query range [1, n-1]
                mx_overlap = st.query(1, 0, n - 1, 1, n - 1)
                ans.append(distinct_primes_count + mx_overlap)
                
        return ans
# @lc code=end