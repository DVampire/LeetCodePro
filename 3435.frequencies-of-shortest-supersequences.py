#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
from typing import List
import collections

class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        all_chars = set()
        for w in words:
            all_chars.update(w)
        char_list = sorted(all_chars)
        m = len(char_list)
        if m == 0:
            return []
        ch_to_id = {ch: i for i, ch in enumerate(char_list)}
        has_edge = [[False] * m for _ in range(m)]
        for w in words:
            x = ch_to_id[w[0]]
            y = ch_to_id[w[1]]
            has_edge[x][y] = True
        min_req = [0] * m
        neigh = [0] * m
        for x in range(m):
            has_self = has_edge[x][x]
            has_out = False
            has_in = False
            for j in range(m):
                if has_edge[x][j]:
                    neigh[x] |= (1 << j)
                    has_out = True
                if has_edge[j][x]:
                    has_in = True
            if has_self:
                min_req[x] = 2
            elif has_out or has_in:
                min_req[x] = 1
        # precompute popcount
        MAX = 1 << m
        pop = [0] * MAX
        for i in range(1, MAX):
            pop[i] = pop[i >> 1] + (i & 1)
        # precompute is_dag
        is_dag = [False] * MAX
        for smask in range(MAX):
            indeg = [0] * m
            for x in range(m):
                if (smask & (1 << x)) == 0:
                    continue
                adj = neigh[x] & smask
                for y in range(m):
                    if adj & (1 << y):
                        indeg[y] += 1
            q = collections.deque()
            for y in range(m):
                if (smask & (1 << y)) and indeg[y] == 0:
                    q.append(y)
            count = 0
            while q:
                x = q.popleft()
                count += 1
                adj = neigh[x] & smask
                for y in range(m):
                    if adj & (1 << y):
                        indeg[y] -= 1
                        if indeg[y] == 0:
                            q.append(y)
            is_dag[smask] = (count == pop[smask])
        # find min_L
        min_L = float('inf')
        for dmask in range(MAX):
            if not is_dag[dmask]:
                continue
            feasible = True
            for c in range(m):
                if dmask & (1 << c):
                    if min_req[c] > 1:
                        feasible = False
                        break
            if not feasible:
                continue
            num_singles = pop[dmask]
            num_forced_out = 0
            for c in range(m):
                if (dmask & (1 << c)) == 0 and min_req[c] >= 1:
                    num_forced_out += 1
            L = num_singles + 2 * num_forced_out
            if L < min_L:
                min_L = L
        # collect freqs at min_L
        freq_set = set()
        a_ord = ord('a')
        for dmask in range(MAX):
            if not is_dag[dmask]:
                continue
            feasible = True
            for c in range(m):
                if dmask & (1 << c):
                    if min_req[c] > 1:
                        feasible = False
                        break
            if not feasible:
                continue
            num_singles = pop[dmask]
            num_forced_out = 0
            for c in range(m):
                if (dmask & (1 << c)) == 0 and min_req[c] >= 1:
                    num_forced_out += 1
            L = num_singles + 2 * num_forced_out
            if L == min_L:
                freq = [0] * 26
                for c in range(m):
                    ch_idx = ord(char_list[c]) - a_ord
                    if dmask & (1 << c):
                        freq[ch_idx] = 1
                    elif min_req[c] >= 1:
                        freq[ch_idx] = 2
                freq_set.add(tuple(freq))
        ans = [list(t) for t in freq_set]
        return ans

# @lc code=end