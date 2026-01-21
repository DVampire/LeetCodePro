#
# @lc app=leetcode id=3501 lang=cpp
#
# [3501] Maximize Active Section with Trade II
#
# @lc code=start
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> result;
        
        for (auto& query : queries) {
            int l = query[0], r = query[1];
            string sub = s.substr(l, r - l + 1);
            string t = "1" + sub + "1";
            int m = t.length();
            
            // Count '1's outside the substring
            int count_outside = 0;
            for (int i = 0; i < l; i++) {
                if (s[i] == '1') count_outside++;
            }
            for (int i = r + 1; i < n; i++) {
                if (s[i] == '1') count_outside++;
            }
            
            // Count '1's in the original substring
            int original_count = 0;
            for (char c : sub) {
                if (c == '1') original_count++;
            }
            int max_count = original_count;
            
            // Find all blocks of '1's surrounded by '0's and try removing each
            for (int i = 1; i < m - 1; ) {
                if (t[i] == '1') {
                    int j = i;
                    while (j < m - 1 && t[j] == '1') j++;
                    // Block of '1's from i to j-1
                    if (t[i-1] == '0' && t[j] == '0') {
                        // Surrounded by '0's, can remove
                        // Extend to find the maximal block of '0's to fill
                        int fill_start = i;
                        while (fill_start > 0 && t[fill_start - 1] == '0') fill_start--;
                        int fill_end = j;
                        while (fill_end < m && t[fill_end] == '0') fill_end++;
                        // Count '1's after trade
                        int count = original_count - (j - i) + (fill_end - fill_start);
                        max_count = max(max_count, count);
                    }
                    i = j;
                } else {
                    i++;
                }
            }
            
            result.push_back(max_count + count_outside);
        }
        
        return result;
    }
};
# @lc code=end