#
# @lc app=leetcode id=3455 lang=cpp
#
# [3455] Shortest Matching Substring
#
# @lc code=start
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        int first_star = p.find('*');
        int second_star = p.find('*', first_star + 1);
        
        string prefix = p.substr(0, first_star);
        string middle = p.substr(first_star + 1, second_star - first_star - 1);
        string suffix = p.substr(second_star + 1);
        
        int n = s.length();
        
        if (prefix.empty() && middle.empty() && suffix.empty()) {
            return 0;
        }
        
        if (prefix.empty()) {
            if (middle.empty() && !suffix.empty()) {
                return s.find(suffix) != string::npos ? suffix.length() : -1;
            } else if (!middle.empty() && suffix.empty()) {
                return s.find(middle) != string::npos ? middle.length() : -1;
            } else {
                vector<int> middle_pos, suffix_pos;
                for (int i = 0; i <= n - (int)middle.length(); i++) {
                    if (s.compare(i, middle.length(), middle) == 0) {
                        middle_pos.push_back(i);
                    }
                }
                for (int i = 0; i <= n - (int)suffix.length(); i++) {
                    if (s.compare(i, suffix.length(), suffix) == 0) {
                        suffix_pos.push_back(i);
                    }
                }
                
                int min_length = INT_MAX;
                for (int m : middle_pos) {
                    for (int suf : suffix_pos) {
                        if (suf >= m + (int)middle.length()) {
                            min_length = min(min_length, suf + (int)suffix.length() - m);
                        }
                    }
                }
                return min_length == INT_MAX ? -1 : min_length;
            }
        }
        
        vector<int> prefix_pos, middle_pos, suffix_pos;
        
        for (int i = 0; i <= n - (int)prefix.length(); i++) {
            if (s.compare(i, prefix.length(), prefix) == 0) {
                prefix_pos.push_back(i);
            }
        }
        
        if (!middle.empty()) {
            for (int i = 0; i <= n - (int)middle.length(); i++) {
                if (s.compare(i, middle.length(), middle) == 0) {
                    middle_pos.push_back(i);
                }
            }
        }
        
        if (!suffix.empty()) {
            for (int i = 0; i <= n - (int)suffix.length(); i++) {
                if (s.compare(i, suffix.length(), suffix) == 0) {
                    suffix_pos.push_back(i);
                }
            }
        }
        
        int min_length = INT_MAX;
        
        for (int prefix_start : prefix_pos) {
            int min_suffix_start = prefix_start + prefix.length() + middle.length();
            
            if (suffix.empty()) {
                if (middle.empty()) {
                    min_length = min(min_length, (int)prefix.length());
                } else {
                    int min_middle_start = prefix_start + prefix.length();
                    auto it = lower_bound(middle_pos.begin(), middle_pos.end(), min_middle_start);
                    if (it != middle_pos.end()) {
                        min_length = min(min_length, *it + (int)middle.length() - prefix_start);
                    }
                }
            } else {
                for (int suffix_start : suffix_pos) {
                    if (suffix_start < min_suffix_start) continue;
                    
                    int length = suffix_start + suffix.length() - prefix_start;
                    
                    if (middle.empty()) {
                        min_length = min(min_length, length);
                    } else {
                        int min_middle_start = prefix_start + prefix.length();
                        int max_middle_start = suffix_start - middle.length();
                        
                        if (max_middle_start >= min_middle_start) {
                            auto it = lower_bound(middle_pos.begin(), middle_pos.end(), min_middle_start);
                            if (it != middle_pos.end() && *it <= max_middle_start) {
                                min_length = min(min_length, length);
                            }
                        }
                    }
                }
            }
        }
        
        return min_length == INT_MAX ? -1 : min_length;
    }
};
# @lc code=end