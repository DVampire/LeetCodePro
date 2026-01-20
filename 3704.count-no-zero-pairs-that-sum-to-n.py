#
# @lc app=leetcode id=3704 lang=python3
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        s = str(n)
        L = len(s)
        d = [int(c) for c in s]
        ways = [[[(0, 0) for _ in range(2)] for _ in range(2)] for _ in range(L + 1)]
        for sa in range(2):
            for sb in range(2):
                ways[L][sa][sb] = (1 if sa == 1 and sb == 1 else 0, 0)
        for pos in range(L - 1, -1, -1):
            for sa in range(2):
                for sb in range(2):
                    res0 = 0
                    res1 = 0
                    mina = 1 if sa == 1 else 0
                    minb = 1 if sb == 1 else 0
                    for da in range(mina, 10):
                        nsa = 1 if sa == 1 or da > 0 else 0
                        for db in range(minb, 10):
                            nsb = 1 if sb == 1 or db > 0 else 0
                            sub0, sub1 = ways[pos + 1][nsa][nsb]
                            for c in range(2):
                                subways = sub0 if c == 0 else sub1
                                if subways > 0:
                                    total = da + db + c
                                    if total % 10 == d[pos]:
                                        cout = total // 10
                                        if cout == 0:
                                            res0 += subways
                                        else:
                                            res1 += subways
                    ways[pos][sa][sb] = (res0, res1)
        return ways[0][0][0][0]
# @lc code=end