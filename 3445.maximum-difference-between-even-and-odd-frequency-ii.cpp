#
# @lc app=leetcode id=3445 lang=cpp
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#
# @lc code=start
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.length();
        int maxDiff = INT_MIN;
        
        for (int i = 0; i < n; i++) {
            int freq[5] = {0}; // Only '0' to '4'
            for (int j = i; j < n; j++) {
                freq[s[j] - '0']++;
                
                if (j - i + 1 >= k) {
                    // Find max odd frequency and min even frequency
                    int maxOdd = INT_MIN;
                    int minEven = INT_MAX;
                    
                    for (int c = 0; c < 5; c++) {
                        if (freq[c] % 2 == 1) {
                            maxOdd = max(maxOdd, freq[c]);
                        } else if (freq[c] > 0) {
                            minEven = min(minEven, freq[c]);
                        }
                    }
                    
                    if (maxOdd != INT_MIN && minEven != INT_MAX) {
                        maxDiff = max(maxDiff, maxOdd - minEven);
                    }
                }
            }
        }
        
        return maxDiff;
    }
};
# @lc code=end