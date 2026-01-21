#
# @lc app=leetcode id=3515 lang=cpp
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int,int>>> adj(n+1);
        for(auto& e : edges) {
            int a = e[0], b = e[1], c = e[2];
            adj[a].emplace_back(b, c);
            adj[b].emplace_back(a, c);
        }
        vector<int> tin(n+1), tout(n+1), dep(n+1), value(n+1, 0);
        int timee = 1;
        function<void(int,int,int,int)> dfs = [&](int u, int p, int d, int w) {
            dep[u] = d;
            value[u] = w;
            tin[u] = timee++;
            for(auto& pr : adj[u]) {
                int v = pr.first;
                int ww = pr.second;
                if(v != p) {
                    dfs(v, u, d+1, ww);
                }
            }
            tout[u] = timee++;
        };
        dfs(1, 0, 0, 0);
        int max_time = timee;
        vector<long long> ftree(max_time + 2, 0);
        auto update = [&](int idx, long long delta) {
            while(idx <= max_time) {
                ftree[idx] += delta;
                idx += idx & -idx;
            }
        };
        auto pref = [&](int idx) -> long long {
            long long sum = 0;
            while(idx > 0) {
                sum += ftree[idx];
                idx -= idx & -idx;
            }
            return sum;
        };
        for(int u = 1; u <= n; ++u) {
            update(tin[u], value[u]);
            update(tout[u], -value[u]);
        }
        vector<int> answer;
        for(auto& q : queries) {
            if(q[0] == 2) {
                int x = q[1];
                long long dist = pref(tin[x]);
                answer.push_back((int)dist);
            } else {
                int u = q[1], v = q[2], nw = q[3];
                int child = (dep[u] < dep[v] ? v : u);
                int oldw = value[child];
                long long delta = (long long)nw - oldw;
                value[child] = nw;
                update(tin[child], delta);
                update(tout[child], -delta);
            }
        }
        return answer;
    }
};
# @lc code=end