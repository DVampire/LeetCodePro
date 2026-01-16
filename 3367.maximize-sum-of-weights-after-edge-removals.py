#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        
        # Build adjacency list with weights
        graph = [[] for _ in range(n)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        # Memoization for DP results
        memo = {}
        
        def dfs(node, parent, parent_edge_used):
            # State: (node, parent, parent_edge_used)
            state = (node, parent, parent_edge_used)
            if state in memo:
                return memo[state]
            
            # Get all children edges (excluding parent edge)
            children_edges = []
            for neighbor, weight in graph[node]:
                if neighbor != parent:
                    children_edges.append((neighbor, weight))
            
            if not children_edges:
                memo[state] = 0
                return 0
            
            # Calculate all possible combinations
            # For each child edge, we can either take it or not
            # If we take it, we recursively solve for that child with parent_edge_used=True
            
            # Generate options: (value_if_taken, value_if_not_taken) for each child edge
            options = []
            for neighbor, weight in children_edges:
                # Value if we don't take this edge (weight 0)
                not_taken = 0 + dfs(neighbor, node, False)
                # Value if we take this edge
                taken = weight + dfs(neighbor, node, True)
                options.append((taken, not_taken))
            
            # Now we need to choose at most k edges (or k-1 if parent_edge_used is True)
            max_edges = k if not parent_edge_used else k - 1
            max_edges = max(0, max_edges)  # Ensure non-negative
            
            # Sort by difference (taken - not_taken) in descending order
            # This tells us which edges give us the most benefit when taken
            diffs = [(options[i][0] - options[i][1], i) for i in range(len(options))]
            diffs.sort(reverse=True)
            
            # Calculate base value (all edges not taken)
            base_value = sum(options[i][1] for i in range(len(options)))
            
            # Add the top 'max_edges' differences
            additional_value = sum(diffs[i][0] for i in range(min(max_edges, len(diffs))))
            
            result = base_value + max(0, additional_value)
            memo[state] = result
            return result
        
        # Start DFS from node 0 with no parent and parent_edge_used=False
        return dfs(0, -1, False)
# @lc code=end