//
// @lc app=leetcode id=3448 lang=cpp
//
// [3448] Count Substrings Divisible By Last Digit
//
// @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.size();
        long long ans = 0;
        
        // For d = 7: Precompute suffix mod 7
        vector<int> suffixMod7(n + 1, 0);
        int pow10 = 1;
        for (int i = n - 1; i >= 0; i--) {
            suffixMod7[i] = (suffixMod7[i + 1] + (s[i] - '0') * pow10) % 7;
            pow10 = (pow10 * 10) % 7;
        }
        
        // Count arrays
        vector<int> cnt3(3, 0), cnt9(9, 0), cnt7(7, 0);
        cnt3[0] = 1;
        cnt9[0] = 1;
        cnt7[suffixMod7[0]] = 1;
        
        int prefixSum = 0;
        
        for (int j = 0; j < n; j++) {
            int d = s[j] - '0';
            
            if (d == 1 || d == 2 || d == 5) {
                ans += j + 1;
            } else if (d == 3 || d == 6) {
                ans += cnt3[prefixSum % 3];
            } else if (d == 9) {
                ans += cnt9[prefixSum];
            } else if (d == 4) {
                ans += 1;
                if (j >= 1) {
                    int lastTwo = (s[j-1] - '0') * 10 + 4;
                    if (lastTwo % 4 == 0) {
                        ans += j;
                    }
                }
            } else if (d == 8) {
                ans += 1;
                if (j >= 1) {
                    int lastTwo = (s[j-1] - '0') * 10 + 8;
                    if (lastTwo % 8 == 0) {
                        ans += 1;
                    }
                }
                if (j >= 2) {
                    int lastThree = (s[j-2] - '0') * 100 + (s[j-1] - '0') * 10 + 8;
                    if (lastThree % 8 == 0) {
                        ans += j - 1;
                    }
                }
            } else if (d == 7) {
                ans += cnt7[suffixMod7[j + 1]];
            }
            // d == 0 case: skip counting
            
            // Update prefix sum and counts
            prefixSum = (prefixSum + d) % 9;
            cnt3[prefixSum % 3]++;
            cnt9[prefixSum]++;
            cnt7[suffixMod7[j + 1]]++;
        }
        
        return ans;
    }
};
// @lc code=end