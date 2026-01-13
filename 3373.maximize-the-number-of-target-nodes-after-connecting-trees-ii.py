#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
from collections import deque
from typing import List

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        # Build adjacency list
        def build_graph(edges):
            n = len(edges) + 1
            graph = [[] for _ in range(n)]
            for u, v in edges:
                graph[u].append(v)
                graph[v].append(u)
            return graph, n
        
        # Color the tree using BFS (bipartite coloring)
        def color_tree(graph, n):
            colors = [-1] * n
            colors[0] = 0
            queue = deque([0])
            while queue:
                u = queue.popleft()
                for v in graph[u]:
                    if colors[v] == -1:
                        colors[v] = 1 - colors[u]
                        queue.append(v)
            return colors
        
        # Tree 1
        graph1, n = build_graph(edges1)
        colors1 = color_tree(graph1, n)
        count1 = [0, 0]
        for c in colors1:
            count1[c] += 1
        
        # Tree 2
        graph2, m = build_graph(edges2)
        colors2 = color_tree(graph2, m)
        count2 = [0, 0]
        for c in colors2:
            count2[c] += 1
        
        # Calculate answer
        max_count2 = max(count2[0], count2[1])
        answer = []
        for i in range(n):
            answer.append(count1[colors1[i]] + max_count2)
        
        return answer
# @lc code=end