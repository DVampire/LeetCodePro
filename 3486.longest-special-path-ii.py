import sys
import heapq

# Increase recursion depth to handle deep trees
sys.setrecursionlimit(100000)

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            
        # pos[val] stores the list of depths where val appears in the current path
        pos = {} 
        
        # Max-heaps for lazy removal to maintain the set S of "penultimate" indices
        # S stores the indices that trigger a duplicate (i.e., the index of the second-to-last occurrence)
        # We use negative values to simulate a max-heap with Python's heapq
        max_heap = [] 
        remove_heap = [] 
        
        self.max_len = -1
        self.min_nodes = 0
        path_dists = [] 
        
        def get_max_s():
            while remove_heap and max_heap[0] == remove_heap[0]:
                heapq.heappop(max_heap)
                heapq.heappop(remove_heap)
            return -max_heap[0] if max_heap else -1
            
        def get_second_max_s():
            first = get_max_s()
            if first == -1: return -1
            
            # Temporarily remove the max to find the second max
            heapq.heappop(max_heap)
            second = get_max_s()
            # Restore the max
            heapq.heappush(max_heap, -first)
            return second

        def add_to_s(val):
            heapq.heappush(max_heap, -val)
            
        def remove_from_s(val):
            heapq.heappush(remove_heap, -val)

        def dfs(u, p, depth, current_dist, current_path_start_limit):
            path_dists.append(current_dist)
            val = nums[u]
            if val not in pos: pos[val] = []
            pos[val].append(depth)
            
            # Constraint 1: No value appears >= 3 times
            # If a value appears for the 3rd time (or more), the path must start after the 3rd-to-last occurrence
            new_path_start_limit = current_path_start_limit
            if len(pos[val]) >= 3:
                new_path_start_limit = max(new_path_start_limit, pos[val][-3] + 1)
                
            # Manage S for Constraint 2: At most one value appears 2 times
            added_trigger = -1
            removed_trigger = -1
            
            if len(pos[val]) >= 2:
                # The penultimate occurrence is now a trigger for a duplicate
                added_trigger = pos[val][-2]
                add_to_s(added_trigger)
                
                # If there were already >= 2 occurrences before this one, the OLD penultimate
                # (which is now antepenultimate) was in S. We must remove it because it's no longer the trigger.
                # The trigger is always the second-to-last occurrence.
                if len(pos[val]) > 2:
                    removed_trigger = pos[val][-3]
                    remove_from_s(removed_trigger)
                    
            s_second_max = get_second_max_s()
            # Start index must be > second largest trigger point to allow at most 1 duplicate
            valid_start = max(new_path_start_limit, s_second_max + 1)
            
            path_len = current_dist - path_dists[valid_start]
            num_nodes = depth - valid_start + 1
            
            if path_len > self.max_len:
                self.max_len = path_len
                self.min_nodes = num_nodes
            elif path_len == self.max_len:
                self.min_nodes = min(self.min_nodes, num_nodes)
                
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, depth + 1, current_dist + w, new_path_start_limit)
            
            # Backtrack state changes
            if added_trigger != -1: remove_from_s(added_trigger)
            if removed_trigger != -1: add_to_s(removed_trigger)
            pos[val].pop()
            path_dists.pop()

        dfs(0, -1, 0, 0, 0)
        return [self.max_len, self.min_nodes]