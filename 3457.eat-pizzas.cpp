#
# @lc app=leetcode id=3457 lang=cpp
#
# [3457] Eat Pizzas!
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        long long n = pizzas.size();
        long long days = n / 4;
        long long odd_days = (days + 1) / 2;
        long long even_days = days / 2;

        sort(pizzas.begin(), pizzas.end());

        long long totalWeight = 0;
        int index = n - 1;

        // For odd days, we gain weight Z (the largest in the group).
        // We greedily take the largest available pizzas.
        for (int i = 0; i < odd_days; ++i) {
            totalWeight += pizzas[index];
            index--;
        }

        // For even days, we gain weight Y (the second largest in the group).
        // We need pairs of large pizzas. The larger of the pair serves as Z (wasted),
        // the smaller serves as Y (gained).
        for (int i = 0; i < even_days; ++i) {
            index--; // Skip the largest remaining (acts as Z)
            totalWeight += pizzas[index]; // Take the next largest (acts as Y)
            index--;
        }

        return totalWeight;
    }
};
# @lc code=end