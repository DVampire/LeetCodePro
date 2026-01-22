#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#
# @lc code=start
class Solution {
public:
    static const int LOG = 17;
    vector<vector<pair<int, long long>>> adj;
    vector<int> depth;
    vector<long long> dist;
    vector<array<int, LOG>> up;
    
    void build(int root, int n) {
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(root);
        depth[root] = 0;
        dist[root] = 0;
        up[root][0] = -1;
        for (int i = 1; i < LOG; i++) up[root][i] = -1;
        visited[root] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (auto& p : adj[u]) {
                int v = p.first;
                long long w = p.second;
                if (!visited[v]) {
                    visited[v] = true;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + w;
                    up[v][0] = u;
                    for (int i = 1; i < LOG; i++) {
                        up[v][i] = (up[v][i-1] != -1) ? up[up[v][i-1]][i-1] : -1;
                    }
                    q.push(v);
                }
            }
        }
    }
    
    int kthAncestor(int node, int k) {
        for (int i = 0; i < LOG && node != -1; i++) {
            if (k & (1 << i)) {
                node = up[node][i];
            }
        }
        return node;
    }
    
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = kthAncestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
    
    int getNode(int u, int v, int lca, int k) {
        int dist_u_lca = depth[u] - depth[lca];
        if (k <= dist_u_lca) {
            return kthAncestor(u, k);
        } else {
            int steps_from_v = depth[v] - depth[lca] - (k - dist_u_lca);
            return kthAncestor(v, steps_from_v);
        }
    }
    
    long long getCumWeight(int u, int v, int lca, int k) {
        int dist_u_lca = depth[u] - depth[lca];
        if (k <= dist_u_lca) {
            int node = kthAncestor(u, k);
            return dist[u] - dist[node];
        } else {
            int steps_from_v = depth[v] - depth[lca] - (k - dist_u_lca);
            int node = kthAncestor(v, steps_from_v);
            return (dist[u] - dist[lca]) + (dist[node] - dist[lca]);
        }
    }
    
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        adj.resize(n);
        depth.resize(n);
        dist.resize(n);
        up.resize(n);
        
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            long long w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        build(0, n);
        
        vector<int> ans;
        for (auto& query : queries) {
            int u = query[0], v = query[1];
            int lca = getLCA(u, v);
            long long totalWeight = dist[u] + dist[v] - 2 * dist[lca];
            int pathLength = depth[u] + depth[v] - 2 * depth[lca] + 1;
            
            int lo = 0, hi = pathLength - 1;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                long long cumWeight = getCumWeight(u, v, lca, mid);
                if (cumWeight * 2 >= totalWeight) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            
            ans.push_back(getNode(u, v, lca, lo));
        }
        
        return ans;
    }
};
# @lc code=end