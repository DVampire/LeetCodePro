#
# @lc app=leetcode id=3448 lang=cpp
#
# [3448] Count Substrings Divisible By Last Digit
#
# @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.size();
        long long ans = 0;
        
        // Precompute prefix digit sums
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + (s[i] - '0');
        }
        
        // For d = 7: precompute suffix values mod 7
        vector<int> suffix7(n + 1, 0);
        int power10 = 1;
        for (int i = n - 1; i >= 0; i--) {
            suffix7[i] = (suffix7[i + 1] + (s[i] - '0') * power10) % 7;
            power10 = (power10 * 10) % 7;
        }
        
        // Counters
        vector<int> count3(3, 0), count9(9, 0), count7(7, 0);
        count3[0] = 1;
        count9[0] = 1;
        count7[suffix7[0]]++;
        
        for (int j = 0; j < n; j++) {
            int d = s[j] - '0';
            
            if (d == 1 || d == 2 || d == 5) {
                ans += (j + 1);
            } else if (d == 3) {
                ans += count3[prefixSum[j + 1] % 3];
            } else if (d == 4) {
                ans += 1;
                if (j >= 1) {
                    int lastTwo = (s[j - 1] - '0') * 10 + d;
                    if (lastTwo % 4 == 0) {
                        ans += j;
                    }
                }
            } else if (d == 6) {
                ans += count3[prefixSum[j + 1] % 3];
            } else if (d == 7) {
                ans += count7[suffix7[j + 1]];
            } else if (d == 8) {
                ans += 1;
                if (j >= 1) {
                    int lastTwo = (s[j - 1] - '0') * 10 + d;
                    if (lastTwo % 8 == 0) {
                        ans += 1;
                    }
                }
                if (j >= 2) {
                    int lastThree = (s[j - 2] - '0') * 100 + (s[j - 1] - '0') * 10 + d;
                    if (lastThree % 8 == 0) {
                        ans += (j - 1);
                    }
                }
            } else if (d == 9) {
                ans += count9[prefixSum[j + 1] % 9];
            }
            
            // Update counts for next iteration
            count3[prefixSum[j + 1] % 3]++;
            count9[prefixSum[j + 1] % 9]++;
            count7[suffix7[j + 1]]++;
        }
        
        return ans;
    }
};
# @lc code=end