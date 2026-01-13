#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        
        # Build the original tree
        original_children = [[] for _ in range(n)]
        for i in range(1, n):
            original_children[parent[i]].append(i)
        
        new_parent = [-1] * n
        new_parent[0] = -1
        
        # DFS to find new parents using character stack
        def find_new_parents(node, char_stack):
            for child in original_children[node]:
                child_char = s[child]
                
                # Find closest ancestor with same character
                if child_char in char_stack and char_stack[child_char]:
                    new_parent[child] = char_stack[child_char][-1]
                else:
                    new_parent[child] = parent[child]
                
                # Add child to character stack
                if child_char not in char_stack:
                    char_stack[child_char] = []
                char_stack[child_char].append(child)
                
                # Recursively process children
                find_new_parents(child, char_stack)
                
                # Remove child from character stack
                char_stack[child_char].pop()
        
        # Start DFS from root
        char_stack = {s[0]: [0]}
        find_new_parents(0, char_stack)
        
        # Build the new tree
        new_children = [[] for _ in range(n)]
        for i in range(1, n):
            new_children[new_parent[i]].append(i)
        
        # Calculate subtree sizes
        answer = [0] * n
        
        def calculate_sizes(node):
            size = 1
            for child in new_children[node]:
                size += calculate_sizes(child)
            answer[node] = size
            return size
        
        calculate_sizes(0)
        return answer
# @lc code=end