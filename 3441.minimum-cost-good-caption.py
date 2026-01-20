#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        INF = 10**9 + 7
        n = len(caption)
        ords = [ord(ch) - ord('a') for ch in caption]
        
        dp = [[[INF] * 26 for _ in range(4)] for _ in range(n + 1)]
        for c in range(26):
            dp[0][0][c] = 0
        
        for i in range(n):
            for pk in range(4):
                for pc in range(26):
                    if dp[i][pk][pc] == INF:
                        continue
                    for d in range(26):
                        cost = abs(ords[i] - d)
                        nc = dp[i][pk][pc] + cost
                        valid = False
                        nk = -1
                        ncc = -1
                        if pk == 0:
                            valid = True
                            nk = 1
                            ncc = d
                        elif d == pc:
                            valid = True
                            nk = min(3, pk + 1)
                            ncc = pc
                        elif pk == 3:
                            valid = True
                            nk = 1
                            ncc = d
                        if valid:
                            dp[i + 1][nk][ncc] = min(dp[i + 1][nk][ncc], nc)
        
        suff = [[[INF] * 26 for _ in range(4)] for _ in range(n + 1)]
        for c in range(26):
            suff[n][3][c] = 0
        
        for i in range(n - 1, -1, -1):
            for pk in range(4):
                for pc in range(26):
                    for d in range(26):
                        cost = abs(ords[i] - d)
                        valid = False
                        nk = -1
                        ncc = -1
                        if pk == 0:
                            valid = True
                            nk = 1
                            ncc = d
                        elif d == pc:
                            valid = True
                            nk = min(3, pk + 1)
                            ncc = pc
                        elif pk == 3:
                            valid = True
                            nk = 1
                            ncc = d
                        if valid and suff[i + 1][nk][ncc] < INF:
                            suff[i][pk][pc] = min(suff[i][pk][pc], cost + suff[i + 1][nk][ncc])
        
        min_cost = INF
        for c in range(26):
            min_cost = min(min_cost, dp[n][3][c])
        if min_cost == INF:
            return ""
        
        # Build lex smallest
        res = []
        curr_i = 0
        curr_k = 0
        curr_c = 0  # dummy
        curr_cost = 0
        while curr_i < n:
            found = False
            for d in range(26):
                cost_add = abs(ords[curr_i] - d)
                tent_cost = curr_cost + cost_add
                valid = False
                nk = -1
                ncc = -1
                if curr_k == 0:
                    valid = True
                    nk = 1
                    ncc = d
                elif d == curr_c:
                    valid = True
                    nk = min(3, curr_k + 1)
                    ncc = curr_c
                elif curr_k == 3:
                    valid = True
                    nk = 1
                    ncc = d
                if valid and tent_cost + suff[curr_i + 1][nk][ncc] == min_cost:
                    res.append(chr(ord('a') + d))
                    curr_k = nk
                    curr_c = ncc
                    curr_cost = tent_cost
                    curr_i += 1
                    found = True
                    break
            if not found:
                return ""  # should not happen
        return ''.join(res)
# @lc code=end