#
# @lc app=leetcode id=3604 lang=cpp
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<vector<vector<int>>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], s = edge[2], e = edge[3];
            adj[u].push_back({v, s, e});
        }
        const long long INF = 1LL << 60;
        vector<long long> dist(n, INF);
        dist[0] = 0;
        using T = pair<long long, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            T front = pq.top(); pq.pop();
            long long time = front.first;
            int u = front.second;
            if (time > dist[u]) continue;
            for (auto& ed : adj[u]) {
                int v = ed[0];
                int s = ed[1], ee = ed[2];
                long long dep = max(time, (long long)s);
                if (dep <= ee) {
                    long long arrv = dep + 1;
                    if (arrv < dist[v]) {
                        dist[v] = arrv;
                        pq.push({arrv, v});
                    }
                }
            }
        }
        long long ans = dist[n - 1];
        return ans >= INF ? -1 : (int)ans;
    }
};
# @lc code=end