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
        
        for u in range(n):
            adj[u].sort()
            
        post_order = []
        start_indices = [0] * n
        end_indices = [0] * n
        
        # Iterative post-order traversal to build the DFS string and track ranges
        stack = [(0, False)]
        while stack:
            u, processed = stack.pop()
            if processed:
                post_order.append(s[u])
                end_indices[u] = len(post_order) - 1
            else:
                start_indices[u] = len(post_order)
                stack.append((u, True))
                # Push children in reverse order to process them in increasing order
                for v in reversed(adj[u]):
                    stack.append((v, False))
        
        # Manacher's Algorithm for O(1) palindrome substring checks
        def get_manacher(S):
            T = ['#'] * (2 * len(S) + 1)
            for i, char in enumerate(S):
                T[2 * i + 1] = char
            
            n_t = len(T)
            d = [0] * n_t
            l, r = 0, -1
            for i in range(n_t):
                k = 1 if i > r else min(d[l + r - i], r - i + 1)
                while 0 <= i - k and i + k < n_t and T[i - k] == T[i + k]:
                    k += 1
                d[i] = k
                if i + k - 1 > r:
                    l = i - k + 1
                    r = i + k - 1
            return d
            
        d = get_manacher(post_order)
        
        ans = [False] * n
        for i in range(n):
            L = end_indices[i] - start_indices[i] + 1
            # Map the center of the substring in post_order to its index in the transformed string T
            mid = start_indices[i] + end_indices[i] + 1
            # If the radius (d[mid]-1) covers the length L, it is a palindrome
            if d[mid] - 1 >= L:
                ans[i] = True
        return ans
# @lc code=end