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
        for i, p in enumerate(parent):
            if p != -1:
                adj[p].append(i)
        
        for i in range(n):
            adj[i].sort()
        
        # Post-order traversal to build the string T and find ranges [L, R]
        T_list = []
        ranges = [None] * n
        starts = [0] * n
        
        # Iterative DFS to handle large trees and avoid recursion limits
        stack = [(0, 0)] # (node, state: 0 for pre-order, 1 for post-order)
        while stack:
            u, state = stack.pop()
            if state == 0:
                starts[u] = len(T_list)
                stack.append((u, 1))
                # Push children in reverse order to process them in increasing order
                for v in reversed(adj[u]):
                    stack.append((v, 0))
            else:
                T_list.append(s[u])
                ranges[u] = (starts[u], len(T_list) - 1)
        
        T = "".join(T_list)
        
        # Manacher's Algorithm to find palindromic substrings in O(n)
        # Transform T into T_prime: "aba" -> "#a#b#a#"
        T_prime = "#" + "#".join(T) + "#"
        n_p = len(T_prime)
        P = [0] * n_p
        C = R = 0
        for i in range(n_p):
            if i < R:
                P[i] = min(R - i, P[2 * C - i])
            
            # Attempt to expand the palindrome centered at i
            a, b = i + (P[i] + 1), i - (P[i] + 1)
            while a < n_p and b >= 0 and T_prime[a] == T_prime[b]:
                P[i] += 1
                a += 1
                b -= 1
            
            # Update the center and right boundary
            if i + P[i] > R:
                C, R = i, i + P[i]
        
        # For each node, verify if its substring range in T is a palindrome
        ans = [False] * n
        for i in range(n):
            L, R_idx = ranges[i]
            length = R_idx - L + 1
            # The center of T[L...R] in T_prime is at index L + R + 1
            center_prime = L + R_idx + 1
            if P[center_prime] >= length:
                ans[i] = True
                
        return ans
# @lc code=end