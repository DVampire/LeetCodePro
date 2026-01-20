#
# @lc app=leetcode id=3458 lang=cpp
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        if (k == 0) return true;
        
        int n = s.length();
        vector<int> first(26, -1);
        vector<int> last(26, -1);
        
        for (int i = 0; i < n; ++i) {
            int charIdx = s[i] - 'a';
            if (first[charIdx] == -1) {
                first[charIdx] = i;
            }
            last[charIdx] = i;
        }
        
        vector<pair<int, int>> intervals;
        
        // Try to form a valid special substring starting with the first occurrence of each character
        for (int charIdx = 0; charIdx < 26; ++charIdx) {
            if (first[charIdx] == -1) continue;
            
            int start = first[charIdx];
            int end = last[charIdx];
            bool valid = true;
            
            // We iterate through the current range [start, end]
            // If we find a character whose range extends beyond current end, we extend end.
            // If we find a character whose range starts before current start, this start is invalid.
            for (int i = start; i <= end; ++i) {
                int currentCharField = s[i] - 'a';
                if (first[currentCharField] < start) {
                    valid = false;
                    break;
                }
                end = max(end, last[currentCharField]);
            }
            
            if (valid) {
                // Constraint: The substring is not the entire string s.
                if (end - start + 1 < n) {
                    intervals.push_back({start, end});
                }
            }
        }
        
        // Greedy Interval Scheduling
        // Sort by end time
        sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });
        
        int count = 0;
        int lastEnd = -1;
        
        for (const auto& interval : intervals) {
            if (interval.first > lastEnd) {
                count++;
                lastEnd = interval.second;
            }
        }
        
        return count >= k;
    }
};
# @lc code=end