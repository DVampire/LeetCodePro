//
// @lc app=leetcode id=3563 lang=cpp
//
// [3563] Lexicographically Smallest String After Adjacent Removals
//

// @lc code=start
class Solution {
public:
    bool isAdjacent(char a, char b) {
        int diff = abs(a - b);
        return diff == 1 || diff == 25;
    }
    
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        if (n == 0) return "";
        
        // can[i][j] = true if s[i..j] can be completely removed
        vector<vector<bool>> can(n, vector<bool>(n, false));
        
        // Base case: length 2
        for (int i = 0; i + 1 < n; i++) {
            can[i][i+1] = isAdjacent(s[i], s[i+1]);
        }
        
        // Fill for increasing lengths (only even lengths >= 4 matter)
        for (int len = 4; len <= n; len += 2) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                // Option 1: s[i] pairs with s[j], and middle is removable
                if (isAdjacent(s[i], s[j]) && can[i+1][j-1]) {
                    can[i][j] = true;
                    continue;
                }
                // Option 2: split into two removable parts
                for (int k = i + 1; k < j; k += 2) {
                    if (can[i][k] && can[k+1][j]) {
                        can[i][j] = true;
                        break;
                    }
                }
            }
        }
        
        // dp[i] = lexicographically smallest string from s[i..n-1]
        vector<string> dp(n + 1);
        dp[n] = "";
        
        for (int i = n - 1; i >= 0; i--) {
            bool emptyPossible = (n - i) % 2 == 0 && can[i][n-1];
            
            if (emptyPossible) {
                dp[i] = "";
            } else {
                // Initialize with s[i] + dp[i+1]
                dp[i] = string(1, s[i]) + dp[i+1];
                
                // Try removing prefixes of even length
                for (int j = i + 2; j < n; j += 2) {
                    // Try to remove s[i..j-1] and start with s[j]
                    if (can[i][j-1]) {
                        string candidate = string(1, s[j]) + dp[j+1];
                        if (candidate < dp[i]) {
                            dp[i] = candidate;
                        }
                    }
                }
            }
        }
        
        return dp[0];
    }
};
// @lc code=end