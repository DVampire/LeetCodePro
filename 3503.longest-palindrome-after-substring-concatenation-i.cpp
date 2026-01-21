#
# @lc app=leetcode id=3503 lang=cpp
#
# [3503] Longest Palindrome After Substring Concatenation I
#
# @lc code=start
class Solution {
public:
    int longestPalindrome(string s, string t) {
        int maxLen = 0;
        int n = s.length();
        int m = t.length();
        
        // Try all possible substrings from s and t
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                for (int k = 0; k <= m; k++) {
                    for (int l = k; l <= m; l++) {
                        string sub1 = s.substr(i, j - i);
                        string sub2 = t.substr(k, l - k);
                        string combined = sub1 + sub2;
                        
                        if (isPalindrome(combined)) {
                            maxLen = max(maxLen, (int)combined.length());
                        }
                    }
                }
            }
        }
        
        return maxLen;
    }
    
private:
    bool isPalindrome(const string& str) {
        int left = 0;
        int right = str.length() - 1;
        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
# @lc code=end