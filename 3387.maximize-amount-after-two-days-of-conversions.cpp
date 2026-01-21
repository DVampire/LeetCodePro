#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, 
                     vector<vector<string>>& pairs2, vector<double>& rates2) {
        // Build graph for day 1
        unordered_map<string, vector<pair<string, double>>> graph1;
        for (size_t i = 0; i < pairs1.size(); i++) {
            const string& from = pairs1[i][0];
            const string& to = pairs1[i][1];
            double rate = rates1[i];
            graph1[from].push_back({to, rate});
            graph1[to].push_back({from, 1.0 / rate});
        }
        
        // Find max amount for each currency on day 1
        unordered_map<string, double> maxDay1;
        maxDay1[initialCurrency] = 1.0;
        
        bool updated = true;
        while (updated) {
            updated = false;
            for (const auto& [from, neighbors] : graph1) {
                if (maxDay1.find(from) == maxDay1.end()) continue;
                for (const auto& [to, rate] : neighbors) {
                    double newAmount = maxDay1[from] * rate;
                    if (maxDay1.find(to) == maxDay1.end() || newAmount > maxDay1[to]) {
                        maxDay1[to] = newAmount;
                        updated = true;
                    }
                }
            }
        }
        
        // Build graph for day 2
        unordered_map<string, vector<pair<string, double>>> graph2;
        for (size_t i = 0; i < pairs2.size(); i++) {
            const string& from = pairs2[i][0];
            const string& to = pairs2[i][1];
            double rate = rates2[i];
            graph2[from].push_back({to, rate});
            graph2[to].push_back({from, 1.0 / rate});
        }
        
        // For day 2, start with all currencies and amounts from day 1
        unordered_map<string, double> maxDay2 = maxDay1;
        
        updated = true;
        while (updated) {
            updated = false;
            for (const auto& [from, neighbors] : graph2) {
                if (maxDay2.find(from) == maxDay2.end()) continue;
                for (const auto& [to, rate] : neighbors) {
                    double newAmount = maxDay2[from] * rate;
                    if (maxDay2.find(to) == maxDay2.end() || newAmount > maxDay2[to]) {
                        maxDay2[to] = newAmount;
                        updated = true;
                    }
                }
            }
        }
        
        // Return the max amount of initialCurrency after day 2
        return maxDay2[initialCurrency];
    }
};
# @lc code=end