#
# @lc app=leetcode id=3710 lang=cpp
#
# [3710] Maximum Partition Factor
#
#include <bits/stdc++.h>
using namespace std;

# @lc code=start
class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = (int)points.size();
        if (n == 2) return 0; // per statement definition

        auto dist = [&](int i, int j) -> long long {
            return llabs((long long)points[i][0] - points[j][0]) +
                   llabs((long long)points[i][1] - points[j][1]);
        };

        long long maxD = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                maxD = max(maxD, dist(i, j));
            }
        }

        auto feasible = [&](long long D) -> bool {
            vector<vector<int>> adj(n);
            adj.assign(n, {});
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (dist(i, j) < D) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
            }

            vector<int> color(n, -1);
            queue<int> q;
            for (int i = 0; i < n; ++i) {
                if (color[i] != -1) continue;
                color[i] = 0;
                q.push(i);
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) {
                        if (color[v] == -1) {
                            color[v] = color[u] ^ 1;
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        };

        long long lo = 0, hi = maxD + 1; // hi is infeasible upper bound
        while (lo + 1 < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (feasible(mid)) lo = mid;
            else hi = mid;
        }
        return (int)lo;
    }
};
# @lc code=end
