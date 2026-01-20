#
# @lc app=leetcode id=3704 lang=cpp
#
# [3704] Count No-Zero Pairs That Sum to N
#
# @lc code=start
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    string S;
    long long memo[17][2][4];
    
    long long dp(int idx, int carry, int mask) {
        // mask: bit 0 -> A active, bit 1 -> B active
        if (idx == S.length()) {
            return (carry == 0 && mask == 0) ? 1 : 0;
        }
        if (memo[idx][carry][mask] != -1) {
            return memo[idx][carry][mask];
        }

        long long ans = 0;
        int digit = S[idx] - '0';

        // Determine ranges for da and db based on mask
        int min_a = (mask & 1) ? 1 : 0;
        int max_a = (mask & 1) ? 9 : 0;
        int min_b = (mask & 2) ? 1 : 0;
        int max_b = (mask & 2) ? 9 : 0;

        // We need (da + db + carry) % 10 == digit
        // So da + db = digit + 10*nc - carry
        // Since da+db is at most 18, nc can be 0 or 1.
        
        for (int nc = 0; nc <= 1; ++nc) {
            int target_sum = digit + 10 * nc - carry;
            
            // Count pairs (da, db) such that da + db == target_sum
            // subject to range constraints.
            // We iterate da, check if valid db exists.
            long long pairs = 0;
            int start_da = max(min_a, target_sum - max_b);
            int end_da = min(max_a, target_sum - min_b);
            
            if (start_da <= end_da) {
                pairs = (end_da - start_da + 1);
            }

            if (pairs > 0) {
                // For each valid pair, we can transition to various next_masks
                // Transitions:
                // A active (1) -> A active (1) or A inactive (0)
                // A inactive (0) -> A inactive (0)
                // Same for B.
                
                long long ways_next = 0;
                
                // Possible next masks
                for (int next_mask = 0; next_mask < 4; ++next_mask) {
                    bool possible = true;
                    
                    // Check A transition
                    if ((mask & 1) == 0 && (next_mask & 1) == 1) possible = false; // 0 -> 1 impossible
                    
                    // Check B transition
                    if ((mask & 2) == 0 && (next_mask & 2) == 2) possible = false; // 0 -> 1 impossible
                    
                    if (possible) {
                        ways_next += dp(idx + 1, nc, next_mask);
                    }
                }
                ans += pairs * ways_next;
            }
        }

        return memo[idx][carry][mask] = ans;
    }

public:
    long long countNoZeroPairs(long long n) {
        S = to_string(n);
        reverse(S.begin(), S.end()); // Process from LSB
        memset(memo, -1, sizeof(memo));
        // Start at idx 0, carry 0, both active (mask 3)
        return dp(0, 0, 3);
    }
};
# @lc code=end