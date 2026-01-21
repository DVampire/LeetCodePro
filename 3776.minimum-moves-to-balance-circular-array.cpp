#
# @lc app=leetcode id=3776 lang=cpp
#
# [3776] Minimum Moves to Balance Circular Array
#
# @lc code=start
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        long long total = 0;
        int neg_idx = -1;
        long long deficit = 0;
        
        for (int i = 0; i < n; i++) {
            total += balance[i];
            if (balance[i] < 0) {
                neg_idx = i;
                deficit = -(long long)balance[i];
            }
        }
        
        if (total < 0) return -1;
        if (neg_idx == -1) return 0;
        
        long long cost = 0;
        vector<pair<int, long long>> sources;
        
        for (int i = 0; i < n; i++) {
            if (i != neg_idx && balance[i] > 0) {
                int clockwise = (neg_idx - i + n) % n;
                int counterclockwise = (i - neg_idx + n) % n;
                int dist = min(clockwise, counterclockwise);
                sources.push_back({dist, (long long)balance[i]});
            }
        }
        
        sort(sources.begin(), sources.end());
        
        for (const auto& p : sources) {
            int dist = p.first;
            long long value = p.second;
            long long units = min(value, deficit);
            cost += (long long)units * dist;
            deficit -= units;
            if (deficit == 0) break;
        }
        
        return cost;
    }
};
# @lc code=end