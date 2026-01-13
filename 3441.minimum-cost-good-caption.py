#
# @lc app=leetcode id=3441 lang=python3
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
from array import array

class Solution:
    def minCostGoodCaption(self, caption: str) -> str:
        n = len(caption)
        ALPHA = 26
        START = 26
        STATES = (ALPHA + 1) * 3  # 27 * 3 = 81
        INF = 10**18

        # dp is a flat array storing dp[i][last][lenState]
        # index = i*STATES + last*3 + lenState
        dp = array('q', [INF]) * ((n + 1) * STATES)

        def idx(i: int, last: int, ls: int) -> int:
            return i * STATES + last * 3 + ls

        # Base: at end, valid only if current run length >= 3 (lenState==2)
        for last in range(ALPHA + 1):
            dp[idx(n, last, 2)] = 0
            dp[idx(n, last, 0)] = INF
            dp[idx(n, last, 1)] = INF

        # Fill backwards
        for i in range(n - 1, -1, -1):
            nxt_base = (i + 1) * STATES
            cur_base = i * STATES
            s = ord(caption[i]) - 97

            # Precompute A[ch] = w + dp[i+1][ch][0]
            A = [0] * ALPHA
            minVal = INF
            countMin = 0
            secondVal = INF

            for ch in range(ALPHA):
                w = s - ch
                if w < 0:
                    w = -w
                val = w + dp[nxt_base + ch * 3 + 0]
                A[ch] = val
                if val < minVal:
                    secondVal = minVal
                    minVal = val
                    countMin = 1
                elif val == minVal:
                    countMin += 1
                elif val < secondVal:
                    secondVal = val

            # START state (only lenState=2 is meaningful)
            dp[cur_base + START * 3 + 2] = minVal
            dp[cur_base + START * 3 + 0] = INF
            dp[cur_base + START * 3 + 1] = INF

            # Normal states
            for last in range(ALPHA):
                wlast = s - last
                if wlast < 0:
                    wlast = -wlast

                # Extend same run
                ext0 = wlast + dp[nxt_base + last * 3 + 1]  # 1 -> 2
                ext1 = wlast + dp[nxt_base + last * 3 + 2]  # 2 -> >=3
                ext2 = wlast + dp[nxt_base + last * 3 + 2]  # >=3 -> >=3

                dp[cur_base + last * 3 + 0] = ext0
                dp[cur_base + last * 3 + 1] = ext1

                # Switch run only if lenState==2
                # best over ch != last
                if A[last] != minVal or countMin > 1:
                    sw = minVal
                else:
                    sw = secondVal

                dp[cur_base + last * 3 + 2] = ext2 if ext2 < sw else sw

        # If impossible
        best = dp[idx(0, START, 2)]
        if best >= INF // 2:
            return ""

        # Reconstruct lexicographically smallest
        res = []
        last = START
        ls = 2

        for i in range(n):
            cur_base = i * STATES
            nxt_base = (i + 1) * STATES
            target = dp[cur_base + last * 3 + ls]
            s = ord(caption[i]) - 97

            for ch in range(ALPHA):
                w = s - ch
                if w < 0:
                    w = -w

                if last == START:
                    cost = w + dp[nxt_base + ch * 3 + 0]
                    if cost == target:
                        res.append(chr(ch + 97))
                        last = ch
                        ls = 0
                        break
                else:
                    if ch == last:
                        new_ls = 1 if ls == 0 else 2
                        cost = w + dp[nxt_base + ch * 3 + new_ls]
                        if cost == target:
                            res.append(chr(ch + 97))
                            ls = new_ls
                            break
                    else:
                        if ls != 2:
                            continue
                        cost = w + dp[nxt_base + ch * 3 + 0]
                        if cost == target:
                            res.append(chr(ch + 97))
                            last = ch
                            ls = 0
                            break

        return "".join(res)
# @lc code=end
