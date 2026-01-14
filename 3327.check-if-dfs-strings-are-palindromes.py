#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        
        # Build adjacency list (children for each node)
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[parent[i]].append(i)
        
        # Children are already in sorted order since we iterate i from 1 to n-1
        
        # Iterative DFS to build the full DFS string
        dfs_str = []
        start = [0] * n
        end = [0] * n
        
        stack = [(0, False)]  # (node, exiting)
        
        while stack:
            node, exiting = stack.pop()
            
            if exiting:
                dfs_str.append(s[node])
                end[node] = len(dfs_str)
            else:
                start[node] = len(dfs_str)
                stack.append((node, True))
                for child in reversed(children[node]):
                    stack.append((child, False))
        
        dfs_str = ''.join(dfs_str)
        
        # Manacher's algorithm to find all palindromic substrings
        t = '#' + '#'.join(dfs_str) + '#'
        t_len = len(t)
        p = [0] * t_len
        center = right = 0
        
        for i in range(t_len):
            if i < right:
                p[i] = min(right - i, p[2 * center - i])
            
            # Expand around center i
            while i + p[i] + 1 < t_len and i - p[i] - 1 >= 0 and t[i + p[i] + 1] == t[i - p[i] - 1]:
                p[i] += 1
            
            # Update center and right boundary
            if i + p[i] > right:
                center = i
                right = i + p[i]
        
        # Check palindrome for each node
        answer = [False] * n
        for i in range(n):
            left, r = start[i], end[i] - 1
            if left > r:
                answer[i] = True
            else:
                # For substring [left, r], center in transformed string is left + r + 1
                # Needed radius is r - left
                mid = left + r + 1
                needed_radius = r - left
                answer[i] = p[mid] >= needed_radius
        
        return answer
# @lc code=end