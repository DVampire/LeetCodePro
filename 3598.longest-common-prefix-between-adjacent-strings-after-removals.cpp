#
# @lc app=leetcode id=3598 lang=cpp
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#
# @lc code=start
class Solution {
public:
    int commonPrefixLength(const string& s1, const string& s2) {
        int len = 0;
        int minLen = min(s1.length(), s2.length());
        for (int i = 0; i < minLen; i++) {
            if (s1[i] == s2[i]) {
                len++;
            } else {
                break;
            }
        }
        return len;
    }
    
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        vector<int> answer(n, 0);
        
        if (n <= 1) {
            return answer;
        }
        
        // Pre-compute common prefix lengths for all adjacent pairs
        vector<int> prefixLens(n - 1);
        for (int i = 0; i < n - 1; i++) {
            prefixLens[i] = commonPrefixLength(words[i], words[i + 1]);
        }
        
        // prefixMax[i] = max of prefixLens[0...i]
        vector<int> prefixMax(n - 1);
        prefixMax[0] = prefixLens[0];
        for (int i = 1; i < n - 1; i++) {
            prefixMax[i] = max(prefixMax[i - 1], prefixLens[i]);
        }
        
        // suffixMax[i] = max of prefixLens[i...n-2]
        vector<int> suffixMax(n - 1);
        suffixMax[n - 2] = prefixLens[n - 2];
        for (int i = n - 3; i >= 0; i--) {
            suffixMax[i] = max(suffixMax[i + 1], prefixLens[i]);
        }
        
        for (int i = 0; i < n; i++) {
            int maxLen = 0;
            
            // Max from pairs before (i-1, i)
            if (i >= 2) {
                maxLen = max(maxLen, prefixMax[i - 2]);
            }
            
            // Max from pairs after (i, i+1)
            if (i <= n - 3) {
                maxLen = max(maxLen, suffixMax[i + 1]);
            }
            
            // New pair created by removing i
            if (i > 0 && i < n - 1) {
                int newPairLen = commonPrefixLength(words[i - 1], words[i + 1]);
                maxLen = max(maxLen, newPairLen);
            }
            
            answer[i] = maxLen;
        }
        
        return answer;
    }
};
# @lc code=end