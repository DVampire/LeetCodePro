#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        // Offset for bitset to handle negative alternating sums
        const int OFFSET = 1850;
        const int BITSET_SIZE = 3701;
        
        // dp[v][0]: sums with product v and even length
        // dp[v][1]: sums with product v and odd length
        vector<pair<bitset<BITSET_SIZE>, bitset<BITSET_SIZE>>> dp(limit + 1);
        
        // Base case: empty subsequence (product 1, sum 0, length 0)
        dp[1].first.set(OFFSET);

        for (int x : nums) {
            if (x > 0) {
                // Update positive products
                for (int v = limit; v >= 1; --v) {
                    if (v % x == 0) {
                        int prev_v = v / x;
                        // Use temporary copies to ensure each element is used once per product path
                        bitset<BITSET_SIZE> prev_0 = dp[prev_v].first;
                        bitset<BITSET_SIZE> prev_1 = dp[prev_v].second;
                        
                        // Adding x at an even index (0, 2, ...) makes length odd
                        dp[v].second |= (prev_0 << x);
                        // Adding x at an odd index (1, 3, ...) makes length even
                        dp[v].first |= (prev_1 >> x);
                    }
                }
                // Update product 0
                bitset<BITSET_SIZE> prev_00 = dp[0].first;
                bitset<BITSET_SIZE> prev_01 = dp[0].second;
                dp[0].second |= (prev_00 << x);
                dp[0].first |= (prev_01 >> x);
            } else { // x == 0
                bitset<BITSET_SIZE> next_00 = dp[0].first;
                bitset<BITSET_SIZE> next_01 = dp[0].second;
                
                // Case 1: Start new subsequence with [0] (sum 0, length 1)
                next_01.set(OFFSET);
                
                // Case 2: Add 0 to any existing non-zero product subsequence
                for (int v = 1; v <= limit; ++v) {
                    next_01 |= dp[v].first;  // even length + 0 at even index
                    next_00 |= dp[v].second; // odd length + 0 at odd index
                }
                
                // Case 3: Add 0 to any existing product-0 subsequence
                next_01 |= dp[0].first;
                next_00 |= dp[0].second;
                
                dp[0].first = next_00;
                dp[0].second = next_01;
            }
        }

        // Search for the maximum product within limit
        if (k + OFFSET >= 0 && k + OFFSET < BITSET_SIZE) {
            for (int v = limit; v >= 1; --v) {
                if (dp[v].first.test(k + OFFSET) || dp[v].second.test(k + OFFSET)) {
                    return v;
                }
            }
            // Check if product 0 is possible
            if (dp[0].first.test(k + OFFSET) || dp[0].second.test(k + OFFSET)) {
                return 0;
            }
        }

        return -1;
    }
};