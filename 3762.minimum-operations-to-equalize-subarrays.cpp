#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        vector<long long> result;
        
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            
            // Single element requires 0 operations
            if (l == r) {
                result.push_back(0);
                continue;
            }
            
            // Check if all elements have the same remainder mod k
            int remainder = nums[l] % k;
            bool possible = true;
            for (int i = l; i <= r; i++) {
                if (nums[i] % k != remainder) {
                    possible = false;
                    break;
                }
            }
            
            if (!possible) {
                result.push_back(-1);
                continue;
            }
            
            // Compute quotients
            vector<long long> quotients;
            for (int i = l; i <= r; i++) {
                quotients.push_back((long long)nums[i] / k);
            }
            
            // Find median using nth_element
            int n = quotients.size();
            int medianIdx = n / 2;
            nth_element(quotients.begin(), quotients.begin() + medianIdx, quotients.end());
            long long median = quotients[medianIdx];
            
            // Calculate minimum operations
            long long ops = 0;
            for (long long q : quotients) {
                ops += abs(q - median);
            }
            
            result.push_back(ops);
        }
        
        return result;
    }
};
# @lc code=end