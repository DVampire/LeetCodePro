#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        
        # Build adjacency list for original tree
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[parent[i]].append(i)
        
        # Find new parent for each node using iterative DFS
        new_parent = parent[:]
        char_stack = [[] for _ in range(26)]
        
        stack = [(0, True)]
        
        while stack:
            node, entering = stack.pop()
            char_idx = ord(s[node]) - ord('a')
            
            if entering:
                if char_stack[char_idx]:
                    new_parent[node] = char_stack[char_idx][-1]
                char_stack[char_idx].append(node)
                stack.append((node, False))
                for child in children[node]:
                    stack.append((child, True))
            else:
                char_stack[char_idx].pop()
        
        # Build new tree
        new_children = [[] for _ in range(n)]
        for i in range(1, n):
            new_children[new_parent[i]].append(i)
        
        # Calculate subtree sizes using iterative post-order DFS
        answer = [1] * n
        stack = [(0, False)]
        
        while stack:
            node, visited = stack.pop()
            if visited:
                for child in new_children[node]:
                    answer[node] += answer[child]
            else:
                stack.append((node, True))
                for child in new_children[node]:
                    stack.append((child, False))
        
        return answer
# @lc code=end