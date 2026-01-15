#
# @lc app=leetcode id=3710 lang=python3
#
# [3710] Maximum Partition Factor
#

# @lc code=start
from typing import List

class Solution:
    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        n = len(points)
        if n == 2:
            return 0
        # compute all pairwise Manhattan distances
        distances = []
        for i in range(n):
            for j in range(i+1, n):
                d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                distances.append((d, i, j))
        # sort distances descending
        distances.sort(reverse=True, key=lambda x: x[0])
        # we need to find the maximum d such that we can split points into two groups where every pair with distance >= d can be placed in same group without violating the condition that the minimum intra-group distance is at least d.
        # Actually we want to maximize the minimum intra-group distance. This is similar to the problem of maximizing the minimum edge weight in a partition of vertices into two groups.
        # This can be solved by binary search on answer d.
        # For a candidate d, we need to check if we can partition points into two groups such that all intra-group pairs have distance >= d.
        # That is equivalent to checking if the graph with edges only for pairs with distance < d is bipartite? Wait: We want each group to have all pairs within group with distance >= d. So if two points have distance < d, they cannot be in the same group. Therefore they must be placed in different groups. So we can think of a graph where edges connect points that are too close (distance < d). Then we need to color the graph with two colors (i.e., bipartite) such that adjacent vertices are in different groups. If it's bipartite, then we have a valid partition. However, there might be multiple connected components; as long as each component is bipartite, we can assign colors consistently across components arbitrarily (since components are independent). But note: we require exactly two non-empty groups. That means after coloring, each color set must be non-empty. If the graph is bipartite and has at least one edge, then both color sets are non-empty. But if the graph has no edges (i.e., all distances >= d), then we can arbitrarily split points into two non-empty groups as long as both groups are non-empty; but we must ensure both groups are non-empty. Since n>=2, we can always put at least one point in each group.
        # However there is nuance: if graph has isolated vertices (no constraints), they can be placed arbitrarily. We just need to ensure that after coloring we don't end up with one color empty. But since we can assign isolated vertices arbitrarily, we can always make both groups non-empty unless n==1 which is not possible.
        # So condition reduces to: graph G_d (edges for pairs with distance < d) is bipartite.
        # Then maximum d such that G_d is bipartite.
        # We binary search over possible distances.
        # Precompute all distances and sort unique distances.
        unique_dists = sorted(set(d for d, _, _ in distances))
        lo = 0
        hi = len(unique_dists) - 1
        ans = 0
        # Also consider possibility that answer could be larger than any existing distance? Actually if all pairs have distance >= some large value D, then G_d for d <= D has no edges, which is bipartite. So maximum possible answer could be infinity? But note partition factor is defined as minimum intra-group distance among all unordered pairs in same group. If there are no intra-group pairs (group size 1), it doesn't contribute. So if we put each point alone? Wait groups must be exactly two non-empty groups. So each group must have at least one point. If one group has size 1 and other has size n-1, then only the larger group contributes pairs. The partition factor is min over intra-group pairs of that larger group.
        # Our condition ensures that for candidate d, we can partition such that any pair within same group has distance >= d. So if such partition exists, then partition factor >= d (since actual min intra-group distance might be larger). We want max possible min intra-group distance.
        # Since distances are finite, answer cannot exceed max pairwise distance? Actually it could be larger than max pairwise distance? No because if you set d > max_pairwise_distance, then there exists no pair with distance >= d, meaning any two points have distance < d; then they cannot be in same group; but you have more than 2 points? For n>2 you cannot assign each point to different groups because only two groups; by pigeonhole principle at least one group will have at least two points which must have distance < d contradicting requirement. So answer cannot exceed max pairwise distance.
        # Hence binary search over sorted unique distances works.
 
        def check(d_thresh):
            # Build graph where edge exists if Manhattan distance < d_thresh
            adj = [[] for _ in range(n)]
            for i in range(n):
                for j in range(i+1, n):
                    dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                    if dist < d_thresh:
                        adj[i].append(j)
                        adj[j].append(i)
            color = [-1]*n  # -1 uncolored, 0 or 1 colors
            from collections import deque
            for start in range(n):
                if color[start]==-1:
                    q = deque([start])
                    color[start]=0
                    while q:
                        u = q.popleft()
                        for v in adj[u]:
                            if color[v]==-1:
                                color[v]=color[u]^1
                                q.append(v)
                            elif color[v]==color[u]:
                                return False
            return True
 
        # Binary search on answer among sorted unique distances plus maybe 0 and maybe beyond? We'll search over possible values of d.
        low_val = 0
        high_val = max(d for d,_ ,_ in distances) + 1  # exclusive upper bound
        ans = 0
        while low_val < high_val:
            mid = (low_val + high_val + 1)//2   # upper mid for maximizing
            if check(mid):
                ans = mid
                low_val = mid   # try larger
            else:
                high_val = mid - 1
        return ans