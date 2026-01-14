#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        n = len(caption)
        if n < 3:
            return ""
        
        # Precompute prefix counts
        caption_indices = [ord(ch) - ord('a') for ch in caption]
        prefix_cnt = [[0] * (n + 1) for _ in range(26)]
        for i, c_idx in enumerate(caption_indices):
            for c in range(26):
                prefix_cnt[c][i + 1] = prefix_cnt[c][i]
            prefix_cnt[c_idx][i + 1] += 1
        
        def cost(start, end, c):
            total = 0
            for c_prime in range(26):
                cnt = prefix_cnt[c_prime][end + 1] - prefix_cnt[c_prime][start]
                total += abs(c - c_prime) * cnt
            return total
        
        INF = float('inf')
        
        dp = [INF] * (n + 1)
        dp[n] = 0
        
        choice = [None] * (n + 1)
        run_length = [0] * (n + 1)
        
        def eff_c_length(L, c, i):
            next_pos = i + L
            if next_pos >= n or choice[next_pos] is None or choice[next_pos][1] != c:
                return L
            return L + run_length[next_pos]
        
        def compare_choices_fast(L1, L2, c, i):
            eff1 = eff_c_length(L1, c, i)
            eff2 = eff_c_length(L2, c, i)
            
            if eff1 == eff2:
                return 0
            
            if eff1 < eff2:
                after1 = i + eff1
                if after1 >= n or choice[after1] is None:
                    return -1
                next_char = choice[after1][1]
                return -1 if next_char < c else 1
            else:
                after2 = i + eff2
                if after2 >= n or choice[after2] is None:
                    return 1
                next_char = choice[after2][1]
                return 1 if next_char < c else -1
        
        for i in range(n - 1, -1, -1):
            best_cost = INF
            candidates = {}
            
            for L in [3, 4, 5]:
                if i + L > n or dp[i + L] == INF:
                    continue
                for c in range(26):
                    curr_cost = cost(i, i + L - 1, c) + dp[i + L]
                    if curr_cost < best_cost:
                        best_cost = curr_cost
                        candidates = {c: [L]}
                    elif curr_cost == best_cost:
                        if c in candidates:
                            candidates[c].append(L)
                        else:
                            candidates[c] = [L]
            
            dp[i] = best_cost
            
            if not candidates:
                continue
            
            best_c = min(candidates.keys())
            best_lengths = candidates[best_c]
            
            best_L = best_lengths[0]
            for L in best_lengths[1:]:
                if compare_choices_fast(best_L, L, best_c, i) > 0:
                    best_L = L
            
            choice[i] = (best_L, best_c)
            
            next_pos = i + best_L
            if next_pos < n and choice[next_pos] is not None and choice[next_pos][1] == best_c:
                run_length[i] = best_L + run_length[next_pos]
            else:
                run_length[i] = best_L
        
        if dp[0] == INF:
            return ""
        
        result = []
        i = 0
        while i < n:
            L, c = choice[i]
            result.append(chr(ord('a') + c) * L)
            i += L
        
        return ''.join(result)
# @lc code=end