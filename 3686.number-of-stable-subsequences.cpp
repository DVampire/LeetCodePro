#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        const int MOD = 1000000007;
        long long se = 0; // single even
        long long so = 0; // single odd
        long long dse = 0; // double same even
        long long dso = 0; // double same odd
        long long dde = 0; // double diff even
        long long ddo = 0; // double diff odd

        for(int num : nums){
            int p = num % 2;
            if(p == 0){ // even
                long long incSame = (se + dde) % MOD;
                long long incDiff = ((so + dso) % MOD + ddo) % MOD;
                se = (se + 1) % MOD;
                dse = (dse + incSame) % MOD;
                dde = (dde + incDiff) % MOD;
            }else{ // odd
                long long incSame = (so + ddo) % MOD;
                long long incDiff = ((se + dse) % MOD + dde) % MOD;
                so = (so + 1) % MOD;
                dso = (dso + incSame) % MOD;
                ddo = (ddo + incDiff) % MOD;
            }
        }
        int ans = ((((se + so) % MOD + (dse + dso) % MOD) % MOD) + (dde + ddo) % MOD) % MOD;
        return ans;
    }
};
# @lc code=end