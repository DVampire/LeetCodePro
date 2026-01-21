#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#
# @lc code=start
class Solution {
public:
    long long popcountDepth(long long n, int k) {
        // Compute depth for each popcount value
        vector<int> depth(65, -1);
        depth[1] = 0;
        
        function<int(int)> getDepth = [&](int pc) -> int {
            if (depth[pc] != -1) return depth[pc];
            int bits = __builtin_popcount(pc);
            depth[pc] = 1 + getDepth(bits);
            return depth[pc];
        };
        
        // Precompute depths for all relevant popcount values
        for (int pc = 1; pc <= 60; pc++) {
            getDepth(pc);
        }
        
        // Special case: k = 0 means only x = 1
        if (k == 0) {
            return n >= 1 ? 1 : 0;
        }
        
        // For k > 0, find all popcount values with depth k-1
        vector<int> target_popcounts;
        for (int pc = 1; pc <= 60; pc++) {
            if (depth[pc] == k - 1) {
                target_popcounts.push_back(pc);
            }
        }
        
        // Count numbers in [1, n] with each target popcount
        long long result = 0;
        for (int pc : target_popcounts) {
            long long count = countWithPopcount(n, pc);
            // Exclude x = 1 if pc = 1 (since 1 has depth 0, not depth k)
            if (pc == 1 && n >= 1) {
                count--;
            }
            result += count;
        }
        
        return result;
    }
    
private:
    long long countWithPopcount(long long n, int pc) {
        if (n < 1 || pc == 0) return 0;
        
        // Convert n to binary
        vector<int> binary;
        long long temp = n;
        while (temp > 0) {
            binary.push_back(temp & 1);
            temp >>= 1;
        }
        reverse(binary.begin(), binary.end());
        
        int len = binary.size();
        
        // dp[pos][bits_used][tight]
        vector<vector<vector<long long>>> dp(len + 1, vector<vector<long long>>(pc + 2, vector<long long>(2, -1)));
        
        function<long long(int, int, bool)> solve = [&](int pos, int bits_used, bool tight) -> long long {
            if (bits_used > pc) return 0;
            if (pos == len) {
                return bits_used == pc ? 1 : 0;
            }
            
            if (dp[pos][bits_used][tight ? 1 : 0] != -1) {
                return dp[pos][bits_used][tight ? 1 : 0];
            }
            
            int limit = tight ? binary[pos] : 1;
            long long res = 0;
            
            for (int digit = 0; digit <= limit; digit++) {
                res += solve(pos + 1, bits_used + digit, tight && (digit == limit));
            }
            
            return dp[pos][bits_used][tight ? 1 : 0] = res;
        };
        
        return solve(0, 0, true);
    }
};
# @lc code=end