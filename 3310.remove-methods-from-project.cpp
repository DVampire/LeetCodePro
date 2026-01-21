#
# @lc app=leetcode id=3310 lang=cpp
#
# [3310] Remove Methods From Project
#
# @lc code=start
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
        }
        
        // Find all suspicious methods using BFS from k
        unordered_set<int> suspicious;
        queue<int> q;
        q.push(k);
        suspicious.insert(k);
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            for (int next : graph[curr]) {
                if (suspicious.find(next) == suspicious.end()) {
                    suspicious.insert(next);
                    q.push(next);
                }
            }
        }
        
        // Check if any non-suspicious method invokes a suspicious method
        bool canRemove = true;
        for (auto& inv : invocations) {
            int from = inv[0];
            int to = inv[1];
            if (suspicious.find(from) == suspicious.end() && suspicious.find(to) != suspicious.end()) {
                canRemove = false;
                break;
            }
        }
        
        // Build result
        vector<int> result;
        if (canRemove) {
            for (int i = 0; i < n; i++) {
                if (suspicious.find(i) == suspicious.end()) {
                    result.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};
# @lc code=end