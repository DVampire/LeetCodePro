#
# @lc app=leetcode id=3458 lang=cpp
#
# [3458] Select K Disjoint Special Substrings
#
# @lc code=start
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.length();
        if (k == 0) return true;
        
        vector<int> first(26, n), last(26, -1);
        
        // Find first and last occurrence of each character
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = max(last[c], i);
        }
        
        vector<pair<int, int>> specials;
        
        // Find all minimal special substrings
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            // Can only start where a character first appears
            if (first[c] != i) continue;
            
            int j = last[c];
            bool valid = true;
            
            // Expand j to include all occurrences of characters in range [i, j]
            for (int p = i; p <= j && valid; p++) {
                int d = s[p] - 'a';
                if (first[d] < i) {
                    // Character appears before i, invalid starting position
                    valid = false;
                } else {
                    j = max(j, last[d]);
                }
            }
            
            // Check if valid and not the entire string
            if (valid && !(i == 0 && j == n - 1)) {
                specials.push_back({i, j});
            }
        }
        
        // Activity selection: sort by end time
        sort(specials.begin(), specials.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
        
        // Greedily select non-overlapping intervals
        int count = 0;
        int lastEnd = -1;
        for (const auto& interval : specials) {
            if (interval.first > lastEnd) {
                count++;
                lastEnd = interval.second;
            }
        }
        
        return count >= k;
    }
};
# @lc code=end