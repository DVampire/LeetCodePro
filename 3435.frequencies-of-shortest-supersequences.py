#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

from typing import List
from collections import deque

# @lc code=start
class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        all_chars = set()
        for w in words:
            all_chars.update(w)
        letters = sorted(all_chars)
        K = len(letters)
        if K == 0:
            return []
        char_to_idx = {c: i for i, c in enumerate(letters)}
        words_idx = [[char_to_idx[c] for c in w] for w in words]
        MAXN = 32
        adj = [[] for _ in range(MAXN)]
        min_L = float('inf')
        candidates: List[List[int]] = []
        for choice in range(1 << K):
            # clear adj
            for i in range(2 * K):
                adj[i].clear()
            num_doubles = 0
            for i in range(K):
                if choice & (1 << i):
                    adj[2 * i].append(2 * i + 1)
                    num_doubles += 1
            this_L = K + num_doubles
            # cross edges
            for x, y in words_idx:
                fx = 2 * x
                ly = 2 * y + 1 if (choice & (1 << y)) else 2 * y
                adj[fx].append(ly)
            # num_included
            num_included = K + num_doubles
            # indeg
            indeg = [0] * (2 * K)
            for u in range(2 * K):
                for v in adj[u]:
                    indeg[v] += 1
            # Kahn
            q = deque()
            for u in range(2 * K):
                is_inc = (u % 2 == 0) or bool(choice & (1 << (u // 2)))
                if is_inc and indeg[u] == 0:
                    q.append(u)
            count = 0
            while q:
                u = q.popleft()
                count += 1
                for v in adj[u]:
                    indeg[v] -= 1
                    if indeg[v] == 0:
                        is_inc_v = (v % 2 == 0) or bool(choice & (1 << (v // 2)))
                        if is_inc_v:
                            q.append(v)
            if count == num_included:
                # valid
                freq = [0] * 26
                for i in range(K):
                    cnt = 2 if (choice & (1 << i)) else 1
                    ci = ord(letters[i]) - ord('a')
                    freq[ci] = cnt
                if this_L < min_L:
                    min_L = this_L
                    candidates = [freq]
                elif this_L == min_L:
                    candidates.append(freq)
        return candidates

# @lc code=end
