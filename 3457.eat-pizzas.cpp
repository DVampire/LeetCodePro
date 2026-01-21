#
# @lc app=leetcode id=3457 lang=cpp
#
# [3457] Eat Pizzas!
#
# @lc code=start
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        int n = pizzas.size();
        sort(pizzas.begin(), pizzas.end(), greater<int>());
        
        int total_days = n / 4;
        int odd_days = (total_days + 1) / 2;
        int even_days = total_days / 2;
        
        long long result = 0;
        
        // Sum top odd_days pizzas (gained on odd days)
        for (int i = 0; i < odd_days; i++) {
            result += pizzas[i];
        }
        
        // Sum every second pizza from the next 2*even_days pizzas
        // (second-max of each even-day group)
        for (int k = 1; k <= even_days; k++) {
            int idx = odd_days + 2 * k - 1;
            result += pizzas[idx];
        }
        
        return result;
    }
};
# @lc code=end