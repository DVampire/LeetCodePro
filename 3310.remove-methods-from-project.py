#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
from collections import defaultdict, deque

class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        # Build adjacency list
        graph = defaultdict(list)
        for a, b in invocations:
            graph[a].append(b)
        
        # Find all suspicious methods using BFS from k
        suspicious = set([k])
        queue = deque([k])
        
        while queue:
            method = queue.popleft()
            for neighbor in graph[method]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    queue.append(neighbor)
        
        # Check if any non-suspicious method invokes a suspicious method
        for a, b in invocations:
            if a not in suspicious and b in suspicious:
                # Can't remove suspicious methods
                return list(range(n))
        
        # Return non-suspicious methods
        return [i for i in range(n) if i not in suspicious]
# @lc code=end