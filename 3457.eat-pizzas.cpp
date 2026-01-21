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
        
        int d = n / 4;
        int num_odd = (d + 1) / 2;
        int num_even = d / 2;
        
        long long sum = 0;
        
        // Add odd day Z values (largest pizzas)
        for (int i = 0; i < num_odd; i++) {
            sum += pizzas[i];
        }
        
        // Add even day Y values (second in each pair from remaining)
        for (int i = 0; i < num_even; i++) {
            sum += pizzas[num_odd + 1 + 2 * i];
        }
        
        return sum;
    }
};
# @lc code=end