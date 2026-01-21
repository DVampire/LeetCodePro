#
# @lc app=leetcode id=3419 lang=cpp
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        vector<int> weights;
        for (auto& e : edges) {
            weights.push_back(e[2]);
        }
        sort(weights.begin(), weights.end());
        weights.erase(unique(weights.begin(), weights.end()), weights.end());
        
        int m = weights.size();
        int left = 0, right = m - 1;
        int ans = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (canReach(n, edges, weights[mid])) {
                ans = weights[mid];
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }
    
private:
    bool canReach(int n, vector<vector<int>>& edges, int maxWeight) {
        // Build reversed graph with edges of weight <= maxWeight
        vector<vector<int>> revAdj(n);
        for (auto& e : edges) {
            if (e[2] <= maxWeight) {
                // Original: e[0] -> e[1], Reversed: e[1] -> e[0]
                revAdj[e[1]].push_back(e[0]);
            }
        }
        
        // BFS from node 0 in reversed graph
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int count = 1;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : revAdj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    count++;
                    q.push(neighbor);
                }
            }
        }
        
        return count == n;
    }
};
# @lc code=end