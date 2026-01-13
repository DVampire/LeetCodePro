#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
from typing import List

class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        # Collect distinct letters and forced duplicates from "xx".
        letters_set = set()
        forced_chars = set()
        for w in words:
            a, b = w[0], w[1]
            letters_set.add(a)
            letters_set.add(b)
            if a == b:
                forced_chars.add(a)

        letters = sorted(letters_set)
        m = len(letters)  # <= 16
        idx = {ch: i for i, ch in enumerate(letters)}
        alpha_idx = [ord(ch) - 97 for ch in letters]

        forcedmask = 0
        for ch in forced_chars:
            forcedmask |= 1 << idx[ch]

        self_idx = []
        edges = []  # (a_idx, b_idx) with a!=b
        for w in words:
            a, b = w[0], w[1]
            ai, bi = idx[a], idx[b]
            if ai == bi:
                self_idx.append(ai)
            else:
                edges.append((ai, bi))

        V = 2 * m  # nodes 0..2m-1

        def feasible(dupmask: int) -> bool:
            # Self constraints require duplication.
            for i in self_idx:
                if ((dupmask >> i) & 1) == 0:
                    return False

            adj = [0] * V

            # Internal edges for duplicated letters: first -> last
            for i in range(m):
                if (dupmask >> i) & 1:
                    u = 2 * i
                    v = 2 * i + 1
                    adj[u] |= 1 << v

            # Edges for constraints a -> b: first(a) -> last(b)
            for ai, bi in edges:
                u = 2 * ai
                v = 2 * bi + (1 if ((dupmask >> bi) & 1) else 0)
                adj[u] |= 1 << v

            # Kahn topological sort to detect cycle
            indeg = [0] * V
            for u in range(V):
                bits = adj[u]
                while bits:
                    lsb = bits & -bits
                    v = lsb.bit_length() - 1
                    indeg[v] += 1
                    bits -= lsb

            q = [i for i in range(V) if indeg[i] == 0]
            head = 0
            processed = 0
            while head < len(q):
                u = q[head]
                head += 1
                processed += 1
                bits = adj[u]
                while bits:
                    lsb = bits & -bits
                    v = lsb.bit_length() - 1
                    bits -= lsb
                    indeg[v] -= 1
                    if indeg[v] == 0:
                        q.append(v)

            return processed == V

        optional = [i for i in range(m) if ((forcedmask >> i) & 1) == 0]
        optn = len(optional)

        best = 10**9
        best_masks: List[int] = []

        for s in range(1 << optn):
            k = s.bit_count()
            if k > best:
                continue

            dupmask = forcedmask
            tmp = s
            while tmp:
                lsb = tmp & -tmp
                j = lsb.bit_length() - 1
                dupmask |= 1 << optional[j]
                tmp -= lsb

            if feasible(dupmask):
                if k < best:
                    best = k
                    best_masks = [dupmask]
                elif k == best:
                    best_masks.append(dupmask)

        ans = []
        for dupmask in best_masks:
            freq = [0] * 26
            for i in range(m):
                freq[alpha_idx[i]] = 2 if ((dupmask >> i) & 1) else 1
            ans.append(freq)

        return ans

# @lc code=end
