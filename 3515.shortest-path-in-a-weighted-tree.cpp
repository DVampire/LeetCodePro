#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#
# @lc app=leetcode id=3515 lang=cpp
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution {
    vector<int> tin, tout;
    int timer;
    vector<vector<pair<int, int>>> adj;
    vector<long long> bit;
    int N;

    void update(int i, long long delta) {
        for (; i <= N; i += i & -i) bit[i] += delta;
    }

    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) sum += bit[i];
        return sum;
    }

    void dfs(int u, int p, long long d, vector<int>& parent_child_map) {
        tin[u] = ++timer;
        update(tin[u], d);
        update(tin[u] + 1, -d);
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (v != p) {
                dfs(v, u, (long long)w, parent_child_map);
            }
        }
        tout[u] = timer;
    }

public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        adj.assign(n + 1, vector<pair<int, int>>());
        map<pair<int, int>, int> edge_weights;
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
            edge_weights[{min(e[0], e[1]), max(e[0], e[1])}] = e[2];
        }

        tin.resize(n + 1);
        tout.resize(n + 1);
        bit.assign(n + 2, 0);
        N = n;
        timer = 0;

        // To identify which node is the child in an edge (u, v)
        vector<int> depth(n + 1, 0);
        vector<int> parent(n + 1, 0);
        auto build_tree = [&](auto self, int u, int p, int d) -> void {
            depth[u] = d;
            parent[u] = p;
            tin[u] = ++timer;
            for (auto& edge : adj[u]) {
                if (edge.first != p) self(self, edge.first, u, d + 1);
            }
            tout[u] = timer;
        };
        build_tree(build_tree, 1, 0, 0);

        // Reset BIT for initial distances
        fill(bit.begin(), bit.end(), 0);
        auto set_initial = [&](auto self, int u, int p, long long curr_dist) -> void {
            update(tin[u], curr_dist);
            update(tin[u] + 1, -curr_dist);
            for (auto& edge : adj[u]) {
                if (edge.first != p) self(self, edge.first, u, (long long)edge.second);
            }
        };
        set_initial(set_initial, 1, 0, 0);

        vector<int> ans;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2], w_new = q[3];
                int child = (depth[u] > depth[v]) ? u : v;
                int& w_old = edge_weights[{min(u, v), max(u, v)}];
                long long diff = (long long)w_new - w_old;
                update(tin[child], diff);
                update(tout[child] + 1, -diff);
                w_old = w_new;
            } else {
                ans.push_back((int)query(tin[q[1]]));
            }
        }

        return ans;
    }
};
# @lc code=end