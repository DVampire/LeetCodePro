#
# @lc app=leetcode id=3441 lang=cpp
#
# [3441] Minimum Cost Good Caption
#
# @lc code=start
class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.length();
        if (n < 3) return "";
        
        const int INF = 1e9;
        vector<pair<int, string>> dp(n + 1, {INF, ""});
        dp[0] = {0, ""};
        
        for (int i = 3; i <= n; i++) {
            for (int j = 0; j <= i - 3; j++) {
                if (dp[j].first == INF) continue;
                
                int len = i - j;
                vector<char> seg;
                for (int k = j; k < i; k++) {
                    seg.push_back(caption[k]);
                }
                sort(seg.begin(), seg.end());
                char ch = seg[(len - 1) / 2];
                
                int cost = 0;
                for (int k = j; k < i; k++) {
                    cost += abs(caption[k] - ch);
                }
                
                int newCost = dp[j].first + cost;
                string newStr = dp[j].second + string(len, ch);
                
                if (newCost < dp[i].first || 
                    (newCost == dp[i].first && newStr < dp[i].second)) {
                    dp[i] = {newCost, newStr};
                }
            }
        }
        
        return dp[n].first == INF ? "" : dp[n].second;
    }
};
# @lc code=end