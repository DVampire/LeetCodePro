#
# @lc app=leetcode id=3598 lang=cpp
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates the length of the longest common prefix between two strings.
     */
    int getLCP(const string& s1, const string& s2) {
        int len = 0;
        int n1 = s1.length(), n2 = s2.length();
        int minLen = min(n1, n2);
        while (len < minLen && s1[len] == s2[len]) {
            len++;
        }
        return len;
    }

    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        if (n <= 1) return vector<int>(n, 0);
        
        // L[i] stores LCP(words[i], words[i+1])
        vector<int> L(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            L[i] = getLCP(words[i], words[i+1]);
        }
        
        // prefixMax[i] stores max(L[0]...L[i-1])
        vector<int> prefixMax(n + 1, 0);
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = max(prefixMax[i-1], L[i-1]);
        }
        
        // suffixMax[i] stores max(L[i]...L[n-2])
        vector<int> suffixMax(n + 1, 0);
        for (int i = n - 2; i >= 0; --i) {
            suffixMax[i] = max(suffixMax[i+1], L[i]);
        }
        
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                // Removing words[0] leaves pairs starting from (words[1], words[2])
                ans[i] = (n > 2) ? suffixMax[1] : 0;
            } else if (i == n - 1) {
                // Removing words[n-1] leaves pairs ending at (words[n-3], words[n-2])
                ans[i] = (n > 2) ? prefixMax[n - 2] : 0;
            } else {
                // Removing words[i] leaves original pairs on the left/right and creates a new pair (i-1, i+1)
                int Mi = getLCP(words[i-1], words[i+1]);
                int currentMax = Mi;
                currentMax = max(currentMax, prefixMax[i-1]);
                currentMax = max(currentMax, suffixMax[i+1]);
                ans[i] = currentMax;
            }
        }
        
        return ans;
    }
};
# @lc code=end