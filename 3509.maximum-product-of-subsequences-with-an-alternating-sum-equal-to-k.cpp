#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#
# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();
        map<tuple<int, int, int, bool>, long long> memo;
        
        function<long long(int, int, int, bool)> dp = [&](int idx, int sum, int parity, bool selected) -> long long {
            if (idx == n) {
                if (!selected || sum != k) return -1;
                return 1;
            }
            
            auto key = make_tuple(idx, sum, parity, selected);
            if (memo.count(key)) {
                return memo[key];
            }
            
            long long result = dp(idx + 1, sum, parity, selected);
            
            int new_sum = (parity == 0) ? sum + nums[idx] : sum - nums[idx];
            long long sub_prod = dp(idx + 1, new_sum, 1 - parity, true);
            
            if (sub_prod >= 0) {
                long long new_prod = sub_prod * nums[idx];
                if (new_prod <= limit) {
                    result = max(result, new_prod);
                }
            }
            
            return memo[key] = result;
        };
        
        long long ans = dp(0, 0, 0, false);
        return (ans < 0) ? -1 : (int)ans;
    }
};
# @lc code=end