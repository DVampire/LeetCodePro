#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        # Build the graph
        adj = [[] for _ in range(n)]
        for u, v in invocations:
            adj[u].append(v)
        
        # Find all suspicious methods (reachable from k)
        suspicious = set()
        queue = [k]
        suspicious.add(k)
        
        # BFS traversal
        head = 0
        while head < len(queue):
            curr = queue[head]
            head += 1
            for neighbor in adj[curr]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    queue.append(neighbor)
        
        # Check if any non-suspicious method invokes a suspicious method
        can_remove = True
        for u, v in invocations:
            if u not in suspicious and v in suspicious:
                can_remove = False
                break
        
        if can_remove:
            result = []
            for i in range(n):
                if i not in suspicious:
                    result.append(i)
            return result
        else:
            return list(range(n))
        
# @lc code=end