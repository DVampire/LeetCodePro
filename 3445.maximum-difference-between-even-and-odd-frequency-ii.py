#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        n = len(s)
        prefix = [[0] * (n + 1) for _ in range(5)]
        for i in range(n):
            c = int(s[i])
            for j in range(5):
                prefix[j][i + 1] = prefix[j][i]
            prefix[c][i + 1] += 1
        ans = float('-inf')
        for a in range(5):
            for b in range(5):
                if a == b:
                    continue
                pa = prefix[a]
                pb = prefix[b]
                groups = [[] for _ in range(4)]
                for i in range(n + 1):
                    par_a = pa[i] % 2
                    par_b = pb[i] % 2
                    gidx = par_a * 2 + par_b
                    st = pa[i] - pb[i]
                    groups[gidx].append((i, st, pb[i]))
                prefix_mins = []
                for gidx in range(4):
                    lst = groups[gidx]
                    if not lst:
                        prefix_mins.append([])
                        continue
                    pm = [0] * len(lst)
                    pm[0] = lst[0][1]
                    for j in range(1, len(lst)):
                        pm[j] = min(pm[j - 1], lst[j][1])
                    prefix_mins.append(pm)
                for endd in range(k, n + 1):
                    if pb[endd] < 2:
                        continue
                    p_a_e = pa[endd] % 2
                    p_b_e = pb[endd] % 2
                    t_pa = 1 - p_a_e
                    t_pb = p_b_e
                    gidx = t_pa * 2 + t_pb
                    lst = groups[gidx]
                    if not lst:
                        continue
                    pm = prefix_mins[gidx]
                    pos_max = endd - k
                    pb_max = pb[endd] - 2
                    # binary search for largest index satisfying conditions
                    l, r = 0, len(lst) - 1
                    res_idx = -1
                    while l <= r:
                        m = (l + r) // 2
                        pos_m, pb_m = lst[m][0], lst[m][2]
                        if pos_m <= pos_max and pb_m <= pb_max:
                            res_idx = m
                            l = m + 1
                        else:
                            r = m - 1
                    if res_idx != -1:
                        min_st = pm[res_idx]
                        cand = (pa[endd] - pb[endd]) - min_st
                        if cand > ans:
                            ans = cand
        return ans if ans != float('-inf') else -1

# @lc code=end
