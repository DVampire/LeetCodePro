#
# @lc app=leetcode id=3562 lang=cpp
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
class Solution {
public:
    map<tuple<int, int, int>, int> memo;
    vector<vector<int>> graph;
    vector<int> present, future;
    
    int maxProfit(int n, vector<int>& present, vector<int>& future, 
                  vector<vector<int>>& hierarchy, int budget) {
        this->present = present;
        this->future = future;
        graph.resize(n + 1);
        
        for (auto& edge : hierarchy) {
            graph[edge[0]].push_back(edge[1]);
        }
        
        return dp(1, budget, 0);
    }
    
    int dp(int u, int budget, int parent_bought) {
        if (budget < 0) return -1e9;
        
        auto key = make_tuple(u, budget, parent_bought);
        if (memo.count(key)) return memo[key];
        
        int cost = parent_bought ? present[u - 1] / 2 : present[u - 1];
        int own_profit = future[u - 1] - cost;
        
        int result = 0;
        
        // Option 1: Don't buy stock for employee u
        if (!graph[u].empty()) {
            result = distributeChildren(u, budget, 0);
        }
        
        // Option 2: Buy stock for employee u
        if (budget >= cost) {
            int val = own_profit;
            if (!graph[u].empty()) {
                val += distributeChildren(u, budget - cost, 1);
            }
            result = max(result, val);
        }
        
        return memo[key] = result;
    }
    
    int distributeChildren(int u, int budget, int u_bought) {
        vector<int> dpk(budget + 1, 0);
        
        for (int child : graph[u]) {
            vector<int> new_dpk(budget + 1, 0);
            for (int b = 0; b <= budget; b++) {
                new_dpk[b] = dpk[b];
                for (int cb = 0; cb <= b; cb++) {
                    int child_val = dp(child, cb, u_bought);
                    new_dpk[b] = max(new_dpk[b], dpk[b - cb] + child_val);
                }
            }
            dpk = new_dpk;
        }
        
        return dpk[budget];
    }
};
# @lc code=end