#
# @lc app=leetcode id=3777 lang=cpp
#
# [3777] Minimum Deletions to Make Alternating Substring
#
# @lc code=start
class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        vector<int> answer;
        
        for (auto& query : queries) {
            if (query[0] == 1) {
                // Flip character at index j
                int j = query[1];
                s[j] = (s[j] == 'A') ? 'B' : 'A';
            } else {
                // Compute minimum deletions for substring s[l..r]
                int l = query[1];
                int r = query[2];
                int len = r - l + 1;
                
                // Try pattern starting with 'A'
                int kept0 = 0;
                char expected = 'A';
                for (int i = l; i <= r; i++) {
                    if (s[i] == expected) {
                        kept0++;
                        expected = (expected == 'A') ? 'B' : 'A';
                    }
                }
                
                // Try pattern starting with 'B'
                int kept1 = 0;
                expected = 'B';
                for (int i = l; i <= r; i++) {
                    if (s[i] == expected) {
                        kept1++;
                        expected = (expected == 'A') ? 'B' : 'A';
                    }
                }
                
                int maxKept = max(kept0, kept1);
                answer.push_back(len - maxKept);
            }
        }
        
        return answer;
    }
};
# @lc code=end