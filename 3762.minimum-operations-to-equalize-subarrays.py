#
# @lc app=leetcode id=3762 lang=python3
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
import bisect

class FenwickTree:
    def __init__(self, n):
        self.tree = [0] * (n + 1)

    def add(self, i, delta):
        i += 1
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & (-i)

    def query(self, i):
        i += 1
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & (-i)
        return s

class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        rems = [x % k for x in nums]
        bad_rem = [0] * n
        for i in range(1, n):
            bad_rem[i] = bad_rem[i-1] + (1 if rems[i] != rems[i-1] else 0)
        
        vals = [x // k for x in nums]
        sorted_vals = sorted(list(set(vals)))
        rank_map = {v: i for i, v in enumerate(sorted_vals)}
        m = len(sorted_vals)
        
        q_len = len(queries)
        ans = [0] * q_len
        valid_queries = []
        for i, (l, r) in enumerate(queries):
            if bad_rem[r] - bad_rem[l] > 0:
                ans[i] = -1
            else:
                valid_queries.append((l, r, i))
        
        # Use offline processing with Fenwick trees to calculate median-based sum
        # For each query [L, R], median is at index (R-L)//2 in sorted nums[L..R]
        # Sum |x - median| = (count_gt * median - sum_gt) + (sum_lt - count_lt * median) 
        # No, it's (sum_gt - count_gt * median) + (count_lt * median - sum_lt)
        
        # To solve this efficiently, we use a persistent segment tree or wavelet tree logic.
        # Since Python might be slow for complex trees, we use a simpler approach if possible.
        # Given constraints, we'll use a segment tree approach to find the kth element and sums.
        
        tree_cnt = [0] * (4 * m)
        tree_sum = [0] * (4 * m)

        def update(node, start, end, idx, val, delta_cnt):
            if start == end:
                tree_cnt[node] += delta_cnt
                tree_sum[node] += val * delta_cnt
                return
            mid = (start + end) // 2
            if idx <= mid:
                update(2 * node, start, mid, idx, val, delta_cnt)
            else:
                update(2 * node + 1, mid + 1, end, idx, val, delta_cnt)
            tree_cnt[node] = tree_cnt[2 * node] + tree_cnt[2 * node + 1]
            tree_sum[node] = tree_sum[2 * node] + tree_sum[2 * node + 1]

        def query_kth(node, start, end, k_rank):
            if start == end:
                return sorted_vals[start]
            mid = (start + end) // 2
            if tree_cnt[2 * node] >= k_rank:
                return query_kth(2 * node, start, mid, k_rank)
            else:
                return query_kth(2 * node + 1, mid + 1, end, k_rank - tree_cnt[2 * node])

        def query_stats(node, start, end, limit_val):
            if sorted_vals[end] <= limit_val:
                return tree_cnt[node], tree_sum[node]
            if sorted_vals[start] > limit_val:
                return 0, 0
            mid = (start + end) // 2
            c1, s1 = query_stats(2 * node, start, mid, limit_val)
            c2, s2 = query_stats(2 * node + 1, mid + 1, end, limit_val)
            return c1 + c2, s1 + s2

        # Mo's algorithm or similar is too slow. Use a persistent segment tree logic.
        # But since we need a single file, let's use a Fenwick tree with offline queries.
        # Actually, the standard way is a Persistent Segment Tree.
        
        class PersistentSegmentTree:
            def __init__(self, size):
                self.size = size
                self.cnt = [0] * (size * 40)
                self.sum = [0] * (size * 40)
                self.L = [0] * (size * 40)
                self.R = [0] * (size * 40)
                self.roots = [0]
                self.node_count = 0

            def update(self, prev_root, start, end, idx, val):
                self.node_count += 1
                node = self.node_count
                self.cnt[node] = self.cnt[prev_root] + 1
                self.sum[node] = self.sum[prev_root] + val
                self.L[node] = self.L[prev_root]
                self.R[node] = self.R[prev_root]
                if start == end: return node
                mid = (start + end) // 2
                if idx <= mid: self.L[node] = self.update(self.L[node], start, mid, idx, val)
                else: self.R[node] = self.update(self.R[node], mid + 1, end, idx, val)
                return node

            def query(self, node_l, node_r, start, end, k):
                if start == end: return sorted_vals[start]
                mid = (start + end) // 2
                count_left = self.cnt[self.L[node_r]] - self.cnt[self.L[node_l]]
                if k <= count_left: return self.query(self.L[node_l], self.L[node_r], start, mid, k)
                else: return self.query(self.R[node_l], self.R[node_r], mid + 1, end, k - count_left)

            def get_sum_and_cnt(self, node_l, node_r, start, end, limit_idx):
                if end <= limit_idx:
                    return self.cnt[node_r] - self.cnt[node_l], self.sum[node_r] - self.sum[node_l]
                mid = (start + end) // 2
                c, s = self.get_sum_and_cnt(self.L[node_l], self.L[node_r], start, mid, limit_idx)
                if limit_idx > mid:
                    c2, s2 = self.get_sum_and_cnt(self.R[node_l], self.R[node_r], mid + 1, end, limit_idx)
                    c += c2; s += s2
                return c, s

        pst = PersistentSegmentTree(n)
        roots = [0] * (n + 1)
        for i in range(n):
            roots[i+1] = pst.update(roots[i], 0, m - 1, rank_map[vals[i]], vals[i])

        for l, r, idx in valid_queries:
            total_cnt = r - l + 1
            median_rank = (total_cnt + 1) // 2
            median = pst.query(roots[l], roots[r+1], 0, m - 1, median_rank)
            
            # find sum of elements <= median
            # We need to find the index of the largest value in sorted_vals <= median
            m_idx = bisect.bisect_right(sorted_vals, median) - 1
            count_le, sum_le = pst.get_sum_and_cnt(roots[l], roots[r+1], 0, m - 1, m_idx)
            
            count_gt = total_cnt - count_le
            sum_gt = (pst.sum[roots[r+1]] - pst.sum[roots[l]]) - sum_le
            
            ans[idx] = (count_le * median - sum_le) + (sum_gt - count_gt * median)
            
        return ans
# @lc code=end