//
// @lc app=leetcode id=3414 lang=cpp
//
// [3414] Maximum Score of Non-overlapping Intervals
//

// @lc code=start
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        
        // Create (end, start, weight, original_index) tuples and sort
        vector<tuple<int, int, int, int>> sorted_intervals;
        for (int i = 0; i < n; i++) {
            sorted_intervals.push_back({intervals[i][1], intervals[i][0], intervals[i][2], i});
        }
        sort(sorted_intervals.begin(), sorted_intervals.end());
        
        // Compare states: higher score is better, then lex smaller indices
        auto better = [](const pair<long long, vector<int>>& a, const pair<long long, vector<int>>& b) {
            if (a.first != b.first) return a.first > b.first;
            if (a.first < 0) return false;
            return a.second < b.second;
        };
        
        // dp[i][k] = (max_score, indices) for first i intervals, choosing exactly k
        vector<vector<pair<long long, vector<int>>>> dp(n + 1, vector<pair<long long, vector<int>>>(5, {-1, {}}));
        
        // Base case: choosing 0 intervals has score 0
        for (int i = 0; i <= n; i++) {
            dp[i][0] = {0, {}};
        }
        
        for (int i = 1; i <= n; i++) {
            auto [end_i, start_i, weight_i, orig_idx] = sorted_intervals[i - 1];
            
            // Binary search: find largest j where end[j] < start_i
            int lo = 0, hi = i - 2, j = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (get<0>(sorted_intervals[mid]) < start_i) {
                    j = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            
            for (int k = 1; k <= 4; k++) {
                // Option 1: Don't take interval i
                dp[i][k] = dp[i - 1][k];
                
                // Option 2: Take interval i
                auto& prev = (j >= 0) ? dp[j + 1][k - 1] : dp[0][k - 1];
                if (prev.first >= 0) {
                    long long new_score = prev.first + weight_i;
                    vector<int> new_indices = prev.second;
                    new_indices.push_back(orig_idx);
                    sort(new_indices.begin(), new_indices.end());
                    
                    pair<long long, vector<int>> new_state = {new_score, new_indices};
                    if (better(new_state, dp[i][k])) {
                        dp[i][k] = new_state;
                    }
                }
            }
        }
        
        // Find best result among all k from 1 to 4
        pair<long long, vector<int>> best = {-1, {}};
        for (int k = 1; k <= 4; k++) {
            if (better(dp[n][k], best)) {
                best = dp[n][k];
            }
        }
        
        return best.second;
    }
};
// @lc code=end