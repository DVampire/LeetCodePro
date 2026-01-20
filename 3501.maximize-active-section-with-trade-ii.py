#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
import bisect

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        # Identify 0-blocks
        blocks = []
        i = 0
        while i < n:
            if s[i] == '0':
                start = i
                while i < n and s[i] == '0':
                    i += 1
                end = i - 1
                blocks.append((start, end))
            else:
                i += 1
        
        total_ones_in_s = s.count('1')
        k = len(blocks)
        
        if k == 0:
            return [total_ones_in_s] * len(queries)

        block_lens = [end - start + 1 for start, end in blocks]
        
        # Precompute merge values (sum of adjacent 0-blocks)
        # block_merges[i] corresponds to merging blocks[i] and blocks[i+1]
        block_merges = []
        for i in range(k - 1):
            block_merges.append(block_lens[i] + block_lens[i+1])
            
        # Build Sparse Table for block lengths
        # st_lens[j][i] covers range [i, i + 2^j - 1]
        max_log_k = k.bit_length()
        st_lens = [[0] * k for _ in range(max_log_k + 1)]
        for i in range(k):
            st_lens[0][i] = block_lens[i]
        for j in range(1, max_log_k + 1):
            length = 1 << (j - 1)
            for i in range(k - (1 << j) + 1):
                st_lens[j][i] = max(st_lens[j-1][i], st_lens[j-1][i + length])
                
        def query_lens(L, R):
            if L > R: return 0
            length = R - L + 1
            bit = length.bit_length() - 1
            return max(st_lens[bit][L], st_lens[bit][R - (1 << bit) + 1])

        # Build Sparse Table for merges
        m = k - 1
        query_merges = None
        if m > 0:
            max_log_m = m.bit_length()
            st_merges = [[0] * m for _ in range(max_log_m + 1)]
            for i in range(m):
                st_merges[0][i] = block_merges[i]
            for j in range(1, max_log_m + 1):
                length = 1 << (j - 1)
                for i in range(m - (1 << j) + 1):
                    st_merges[j][i] = max(st_merges[j-1][i], st_merges[j-1][i + length])
            
            def query_merges_fn(L, R):
                if L > R: return 0
                length = R - L + 1
                bit = length.bit_length() - 1
                return max(st_merges[bit][L], st_merges[bit][R - (1 << bit) + 1])
            query_merges = query_merges_fn
        else:
            def query_merges_fn(L, R): return 0
            query_merges = query_merges_fn

        starts = [b[0] for b in blocks]
        ends = [b[1] for b in blocks]
        
        ans_list = []
        
        for l, r in queries:
            # Find range of intersecting blocks
            # Find first block ending >= l
            idx_L = bisect.bisect_left(ends, l)
            # Find last block starting <= r
            idx_R = bisect.bisect_right(starts, r) - 1
            
            if idx_L > idx_R:
                ans_list.append(total_ones_in_s)
                continue
            
            # Calculate lengths of partial blocks at boundaries
            b_L = blocks[idx_L]
            len_L = min(b_L[1], r) - max(b_L[0], l) + 1
            
            b_R = blocks[idx_R]
            len_R = min(b_R[1], r) - max(b_R[0], l) + 1
            
            current_gain = 0
            
            if idx_L == idx_R:
                current_gain = len_L
            elif idx_L + 1 == idx_R:
                current_gain = len_L + len_R
            else:
                # At least 3 blocks involved: L, L+1, ..., R-1, R
                
                # 1. Single flips at boundaries
                current_gain = max(len_L, len_R)
                
                # 2. Merges at boundaries
                # Merge L with L+1
                current_gain = max(current_gain, len_L + block_lens[idx_L+1])
                # Merge R-1 with R
                current_gain = max(current_gain, block_lens[idx_R-1] + len_R)
                
                # 3. Internal single flips: range [L+1, R-1]
                current_gain = max(current_gain, query_lens(idx_L + 1, idx_R - 1))
                
                # 4. Internal merges: ranges (i, i+1) where i >= L+1 and i+1 <= R-1
                # i.e., indices i from L+1 to R-2
                current_gain = max(current_gain, query_merges(idx_L + 1, idx_R - 2))
            
            ans_list.append(total_ones_in_s + current_gain)
            
        return ans_list
# @lc code=end