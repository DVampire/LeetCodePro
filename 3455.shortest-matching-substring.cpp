//
// @lc app=leetcode id=3455 lang=cpp
//
// [3455] Shortest Matching Substring
//

// @lc code=start
class Solution {
public:
    vector<int> z_function(const string& s) {
        int n = s.size();
        vector<int> z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i < r) {
                z[i] = min(r - i, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }
    
    vector<int> findMatches(const string& pattern, const string& text) {
        int n = text.size();
        if (pattern.empty()) {
            vector<int> matches;
            for (int i = 0; i <= n; i++) {
                matches.push_back(i);
            }
            return matches;
        }
        string combined = pattern + "$" + text;
        vector<int> z = z_function(combined);
        vector<int> matches;
        int patLen = pattern.size();
        for (int i = patLen + 1; i < (int)combined.size(); i++) {
            if (z[i] >= patLen) {
                matches.push_back(i - patLen - 1);
            }
        }
        return matches;
    }
    
    int shortestMatchingSubstring(string s, string p) {
        int n = s.size();
        
        // Split p by '*'
        vector<string> parts;
        size_t start = 0;
        for (size_t i = 0; i <= p.size(); i++) {
            if (i == p.size() || p[i] == '*') {
                parts.push_back(p.substr(start, i - start));
                start = i + 1;
            }
        }
        
        string p1 = parts[0], p2 = parts[1], p3 = parts[2];
        int len1 = p1.size(), len2 = p2.size(), len3 = p3.size();
        
        // Find all matches for each part
        vector<int> match1 = findMatches(p1, s);
        vector<int> match2 = findMatches(p2, s);
        vector<int> match3 = findMatches(p3, s);
        
        if (match1.empty() || match2.empty() || match3.empty()) return -1;
        
        // Create indicator arrays
        vector<bool> hasMatch2(n + 2, false);
        vector<bool> hasMatch3(n + 2, false);
        
        for (int i : match2) if (i <= n) hasMatch2[i] = true;
        for (int i : match3) if (i <= n) hasMatch3[i] = true;
        
        // Compute next2 and next3
        vector<int> next2(n + 2, -1);
        vector<int> next3(n + 2, -1);
        
        int nextMatch = -1;
        for (int i = n; i >= 0; i--) {
            if (hasMatch2[i]) nextMatch = i;
            next2[i] = nextMatch;
        }
        
        nextMatch = -1;
        for (int i = n; i >= 0; i--) {
            if (hasMatch3[i]) nextMatch = i;
            next3[i] = nextMatch;
        }
        
        // For each match of p1, find the shortest matching substring
        int minLen = INT_MAX;
        
        for (int start1 : match1) {
            int end1 = start1 + len1;
            if (end1 > n) continue;
            
            if (next2[end1] == -1) continue;
            int start2 = next2[end1];
            int end2 = start2 + len2;
            if (end2 > n) continue;
            
            if (next3[end2] == -1) continue;
            int start3 = next3[end2];
            int end3 = start3 + len3;
            if (end3 > n) continue;
            
            int len = end3 - start1;
            minLen = min(minLen, len);
        }
        
        return minLen == INT_MAX ? -1 : minLen;
    }
};
// @lc code=end