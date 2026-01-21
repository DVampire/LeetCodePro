#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#
# @lc code=start
class Solution {
public:
    unordered_map<string, double> findMaxAmounts(const unordered_map<string, vector<pair<string, double>>>& graph, const string& start) {
        unordered_map<string, double> maxAmounts;
        priority_queue<pair<double, string>> pq;
        
        pq.push({1.0, start});
        maxAmounts[start] = 1.0;
        
        while (!pq.empty()) {
            auto [amount, curr] = pq.top();
            pq.pop();
            
            if (amount < maxAmounts[curr]) continue;
            
            if (graph.find(curr) == graph.end()) continue;
            
            for (const auto& [next, rate] : graph.at(curr)) {
                double newAmount = amount * rate;
                if (maxAmounts.find(next) == maxAmounts.end() || newAmount > maxAmounts[next]) {
                    maxAmounts[next] = newAmount;
                    pq.push({newAmount, next});
                }
            }
        }
        
        return maxAmounts;
    }
    
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string, vector<pair<string, double>>> graph1;
        for (size_t i = 0; i < pairs1.size(); i++) {
            const string& from = pairs1[i][0];
            const string& to = pairs1[i][1];
            double rate = rates1[i];
            graph1[from].push_back({to, rate});
            graph1[to].push_back({from, 1.0 / rate});
        }
        
        unordered_map<string, vector<pair<string, double>>> graph2;
        for (size_t i = 0; i < pairs2.size(); i++) {
            const string& from = pairs2[i][0];
            const string& to = pairs2[i][1];
            double rate = rates2[i];
            graph2[from].push_back({to, rate});
            graph2[to].push_back({from, 1.0 / rate});
        }
        
        unordered_map<string, double> day1Max = findMaxAmounts(graph1, initialCurrency);
        
        double result = day1Max[initialCurrency];
        
        for (const auto& [currency, day1Amount] : day1Max) {
            unordered_map<string, double> day2Max = findMaxAmounts(graph2, currency);
            if (day2Max.find(initialCurrency) != day2Max.end()) {
                result = max(result, day1Amount * day2Max[initialCurrency]);
            }
        }
        
        return result;
    }
};
# @lc code=end