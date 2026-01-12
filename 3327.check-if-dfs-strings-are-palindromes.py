#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        adj = [[] for _ in range(n)]
        for child in range(1, n):
            adj[parent[child]].append(child)
            
        start = [0] * n
        end = [0] * n
        T = [None] * n
        curr_idx = 0
        
        # Iterative DFS to build the global DFS string and record ranges
        stack = [(0, False)]
        while stack:
            u, visited = stack.pop()
            if visited:
                T[curr_idx] = s[u]
                curr_idx += 1
                end[u] = curr_idx - 1
            else:
                start[u] = curr_idx
                stack.append((u, True))
                # Push children in reverse order to process them in increasing order
                for v in reversed(adj[u]):
                    stack.append((v, False))
                    
        T_str = "".join(T)
        
        # Manacher's Algorithm
        # Transform T_str: "aba" -> "#a#b#a#"
        t = '#' + '#'.join(T_str) + '#'
        m = len(t)
        p = [0] * m
        c = r = 0
        for i in range(m):
            if i < r:
                p[i] = min(r - i, p[2 * c - i])
            while i + p[i] + 1 < m and i - p[i] - 1 >= 0 and t[i + p[i] + 1] == t[i - p[i] - 1]:
                p[i] += 1
            if i + p[i] > r:
                c, r = i, i + p[i]
                
        ans = [False] * n
        for i in range(n):
            L, R = start[i], end[i]
            # The center of substring T[L...R] in the transformed string t is L + R + 1
            # p[center] gives the length of the longest palindrome at that center
            if p[L + R + 1] >= R - L + 1:
                ans[i] = True
        return ans
# @lc code=end