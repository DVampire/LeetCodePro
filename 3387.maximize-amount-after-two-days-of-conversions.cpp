#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#
# @lc code=start
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        // Build graph for day 1
        unordered_map<string, vector<pair<string, double>>> graph1;
        for (int i = 0; i < pairs1.size(); i++) {
            graph1[pairs1[i][0]].push_back({pairs1[i][1], rates1[i]});
            graph1[pairs1[i][1]].push_back({pairs1[i][0], 1.0 / rates1[i]});
        }
        
        // BFS to find amounts after day 1
        unordered_map<string, double> day1Amounts;
        day1Amounts[initialCurrency] = 1.0;
        queue<string> q;
        q.push(initialCurrency);
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            for (auto& [next, rate] : graph1[curr]) {
                if (!day1Amounts.count(next)) {
                    day1Amounts[next] = day1Amounts[curr] * rate;
                    q.push(next);
                }
            }
        }
        
        // Build graph for day 2
        unordered_map<string, vector<pair<string, double>>> graph2;
        for (int i = 0; i < pairs2.size(); i++) {
            graph2[pairs2[i][0]].push_back({pairs2[i][1], rates2[i]});
            graph2[pairs2[i][1]].push_back({pairs2[i][0], 1.0 / rates2[i]});
        }
        
        // BFS to find conversion rates back to initialCurrency
        unordered_map<string, double> day2Rates;
        day2Rates[initialCurrency] = 1.0;
        queue<string> q2;
        q2.push(initialCurrency);
        
        while (!q2.empty()) {
            string curr = q2.front();
            q2.pop();
            for (auto& [next, rate] : graph2[curr]) {
                if (!day2Rates.count(next)) {
                    // 1 unit of next = (1/rate) units of curr
                    // (1/rate) units of curr = (1/rate) * day2Rates[curr] units of initialCurrency
                    day2Rates[next] = day2Rates[curr] / rate;
                    q2.push(next);
                }
            }
        }
        
        // Calculate maximum
        double result = 1.0;
        for (auto& [currency, amount] : day1Amounts) {
            if (day2Rates.count(currency)) {
                result = max(result, amount * day2Rates[currency]);
            }
        }
        
        return result;
    }
};
# @lc code=end