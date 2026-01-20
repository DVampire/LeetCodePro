#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
from collections import defaultdict, deque
from typing import List

class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        adj = defaultdict(list)
        for a, b, c in edges:
            adj[a].append((b, c))
            adj[b].append((a, c))
        
        parent = [-1] * (n + 1)
        weight_to_parent = [0] * (n + 1)
        dist = [0] * (n + 1)
        visited = [False] * (n + 1)
        q = deque([1])
        visited[1] = True
        dist[1] = 0
        parent[1] = -1
        while q:
            node = q.popleft()
            for nei, w in adj[node]:
                if not visited[nei]:
                    visited[nei] = True
                    parent[nei] = node
                    weight_to_parent[nei] = w
                    dist[nei] = dist[node] + w
                    q.append(nei)
        
        children = [[] for _ in range(n + 1)]
        for i in range(1, n + 1):
            if parent[i] != -1:
                children[parent[i]].append(i)
        
        in_time = [-1] * (n + 1)
        out_time = [-1] * (n + 1)
        order = [0] * n
        timer = 0
        stack = []
        in_time[1] = timer
        order[timer] = dist[1]
        timer += 1
        stack.append((1, 0))
        while stack:
            node, child_idx = stack[-1]
            if child_idx < len(children[node]):
                stack[-1] = (node, child_idx + 1)
                child = children[node][child_idx]
                in_time[child] = timer
                order[timer] = dist[child]
                timer += 1
                stack.append((child, 0))
            else:
                out_time[node] = timer
                stack.pop()
        
        class SegTree:
            def __init__(self, arr):
                self.n = len(arr)
                self.tree = [0] * (4 * self.n)
                self.lazy = [0] * (4 * self.n)
                self.build(1, 0, self.n - 1, arr)
            
            def build(self, node, start, end, arr):
                if start == end:
                    self.tree[node] = arr[start]
                    return
                mid = (start + end) // 2
                self.build(2 * node, start, mid, arr)
                self.build(2 * node + 1, mid + 1, end, arr)
                self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]
            
            def propagate(self, node, start, end):
                if self.lazy[node] != 0:
                    self.tree[node] += (end - start + 1) * self.lazy[node]
                    if start != end:
                        self.lazy[2 * node] += self.lazy[node]
                        self.lazy[2 * node + 1] += self.lazy[node]
                    self.lazy[node] = 0
            
            def update_range(self, node, start, end, l, r, val):
                self.propagate(node, start, end)
                if start > end or start > r or end < l:
                    return
                if l <= start and end <= r:
                    self.lazy[node] += val
                    self.propagate(node, start, end)
                    return
                mid = (start + end) // 2
                self.update_range(2 * node, start, mid, l, r, val)
                self.update_range(2 * node + 1, mid + 1, end, l, r, val)
                self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]
            
            def query_range(self, node, start, end, l, r):
                self.propagate(node, start, end)
                if start > end or start > r or end < l:
                    return 0
                if l <= start and end <= r:
                    return self.tree[node]
                mid = (start + end) // 2
                p1 = self.query_range(2 * node, start, mid, l, r)
                p2 = self.query_range(2 * node + 1, mid + 1, end, l, r)
                return p1 + p2
        
        seg = SegTree(order)
        
        ans = []
        for query in queries:
            tp = query[0]
            if tp == 2:
                x = query[1]
                pos = in_time[x]
                ans.append(seg.query_range(1, 0, n - 1, pos, pos))
            else:
                u, v, wnew = query[1], query[2], query[3]
                child = v if parent[v] == u else u
                old_w = weight_to_parent[child]
                delta = wnew - old_w
                weight_to_parent[child] = wnew
                L = in_time[child]
                R = out_time[child] - 1
                if delta != 0 and L <= R:
                    seg.update_range(1, 0, n - 1, L, R, delta)
        return ans
# @lc code=end