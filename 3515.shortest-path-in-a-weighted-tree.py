#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n + 1)]
        # Use a map to store edge weights to handle updates easily
        # Key: tuple(sorted((u, v))), Value: weight
        edge_weights = {}
        
        for u, v, w in edges:
            adj[u].append(v)
            adj[v].append(u)
            if u < v:
                edge_weights[(u, v)] = w
            else:
                edge_weights[(v, u)] = w
        
        # DFS to linearize the tree (Euler Tour / DFS order)
        # and compute initial distances and subtree ranges
        tin = [0] * (n + 1)
        tout = [0] * (n + 1)
        initial_dist = [0] * (n + 1)
        # To identify which node is the child in an edge for updates
        # parent[x] is not strictly needed if we check depth, but depth is useful.
        # Let's verify parent/child relationship using depth or entry time.
        # tin[child] > tin[parent] and tout[child] < tout[parent].
        
        timer = 0
        stack = [(1, 0, 0)] # node, parent, current_dist
        
        # Iterative DFS to avoid recursion limit issues
        # We need to process node on entry and on exit.
        # To do this iteratively, we can push to stack or use a specific order.
        # A simple way for tin/tout is to store the order.
        
        # Let's stick to recursive for clarity, usually fine for 10^5 in Python if limit raised
        import sys
        sys.setrecursionlimit(200000)
        
        def dfs(u, p, d):
            nonlocal timer
            timer += 1
            tin[u] = timer
            initial_dist[u] = d
            
            for v in adj[u]:
                if v != p:
                    # Weight of edge u-v
                    w = edge_weights[(min(u, v), max(u, v))]
                    dfs(v, u, d + w)
            
            tout[u] = timer

        dfs(1, 0, 0)
        
        # Binary Indexed Tree for Range Update, Point Query
        # We update range [l, r] with val, query point i
        # Standard BIT: update(i, val) adds to i..n, query(i) sums 1..i
        # Range update [l, r] with v:
        #   update(l, v)
        #   update(r + 1, -v)
        # Point query at i:
        #   query(i) returns the accumulated value
        
        bit = [0] * (n + 2)
        
        def bit_update(idx, val):
            while idx <= n:
                bit[idx] += val
                idx += idx & (-idx)
        
        def bit_query(idx):
            s = 0
            while idx > 0:
                s += bit[idx]
                idx -= idx & (-idx)
            return s
        
        ans = []
        
        for q in queries:
            type = q[0]
            if type == 1:
                u, v, w_new = q[1], q[2], q[3]
                # Determine which is child
                # The child is the one with the larger tin because it was visited later in the descent
                # Actually, in a tree edge (u, v), the child's interval is strictly inside the parent's interval (except for the root logic).
                # The one with the larger tin is the child.
                if tin[u] > tin[v]:
                    child = u
                else:
                    child = v
                
                key = (min(u, v), max(u, v))
                old_w = edge_weights[key]
                diff = w_new - old_w
                edge_weights[key] = w_new
                
                # Update range [tin[child], tout[child]]
                bit_update(tin[child], diff)
                bit_update(tout[child] + 1, -diff)
                
            else:
                x = q[1]
                current_d = initial_dist[x] + bit_query(tin[x])
                ans.append(current_d)
                
        return ans
# @lc code=end