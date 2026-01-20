#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        unordered_map<int, int> maskToMax;
        for (int num : nums) {
            maskToMax[num] = max(maskToMax[num], num);
        }

        vector<pair<int, int>> uniquePairs;
        for (auto const& [mask, val] : maskToMax) {
            uniquePairs.push_back({mask, val});
        }

        long long max_prod = 0;
        int n = uniquePairs.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((uniquePairs[i].first & uniquePairs[j].first) == 0) {
                    max_prod = max(max_prod, (long long)uniquePairs[i].second * uniquePairs[j].second);
                }
            }
        }

        return max_prod;
    }
};
# @lc code=end