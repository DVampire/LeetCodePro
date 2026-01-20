#
# @lc app=leetcode id=3455 lang=cpp
#
# [3455] Shortest Matching Substring
#

# @lc code=start
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    // KMP Algorithm to find all occurrences of pattern pat in text txt
    vector<int> kmpSearch(const string& txt, const string& pat) {
        vector<int> result;
        if (pat.empty()) return result;
        
        int n = txt.length();
        int m = pat.length();
        if (m > n) return result;

        // Compute LPS array
        vector<int> lps(m);
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // Search
        int j = 0; // index for pat
        i = 0; // index for txt
        while (i < n) {
            if (pat[j] == txt[i]) {
                j++;
                i++;
            }
            if (j == m) {
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pat[j] != txt[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
        return result;
    }

    int shortestMatchingSubstring(string s, string p) {
        // Split p by '*'
        vector<string> parts;
        string temp = "";
        for (char c : p) {
            if (c == '*') {
                parts.push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        parts.push_back(temp);

        // parts[0] is s1, parts[1] is s2, parts[2] is s3
        string s1 = parts[0];
        string s2 = parts[1];
        string s3 = parts[2];

        vector<int> p1 = kmpSearch(s, s1);
        vector<int> p2 = kmpSearch(s, s2);
        vector<int> p3 = kmpSearch(s, s3);

        // If any non-empty part is not found, return -1
        if (!s1.empty() && p1.empty()) return -1;
        if (!s2.empty() && p2.empty()) return -1;
        if (!s3.empty() && p3.empty()) return -1;

        int minLen = 2e9;
        bool found = false;

        if (s2.empty()) {
            // Pattern is s1**s3 -> s1*s3
            if (s1.empty() && s3.empty()) return 0;
            if (s1.empty()) return s3.length();
            if (s3.empty()) return s1.length();

            // Both s1 and s3 non-empty
            for (int k : p3) {
                // Find largest i in p1 such that i + s1.len <= k
                // We want to maximize i to minimize length (k + s3.len) - i
                // upper_bound returns first element > value. 
                // We want element <= value. So prev(upper_bound)
                int target = k - (int)s1.length();
                auto it = upper_bound(p1.begin(), p1.end(), target);
                if (it != p1.begin()) {
                    int i = *prev(it);
                    int currentLen = (k + (int)s3.length()) - i;
                    if (currentLen < minLen) {
                        minLen = currentLen;
                        found = true;
                    }
                }
            }
        } else {
            // s2 is not empty. Pattern is s1*s2*s3
            // We iterate over occurrences of s2
            for (int j : p2) {
                // 1. Find best start for s1
                int i = -1;
                if (s1.empty()) {
                    i = j;
                } else {
                    int target = j - (int)s1.length();
                    auto it = upper_bound(p1.begin(), p1.end(), target);
                    if (it != p1.begin()) {
                        i = *prev(it);
                    }
                }

                if (i == -1) continue; // No valid s1 found for this s2

                // 2. Find best end for s3
                int k = -1;
                if (s3.empty()) {
                    k = j + (int)s2.length();
                } else {
                    int target = j + (int)s2.length();
                    auto it = lower_bound(p3.begin(), p3.end(), target);
                    if (it != p3.end()) {
                        k = *it;
                    }
                }

                if (k == -1) continue; // No valid s3 found for this s2

                int currentLen = (k + (int)s3.length()) - i;
                if (currentLen < minLen) {
                    minLen = currentLen;
                    found = true;
                }
            }
        }

        return found ? minLen : -1;
    }
};
# @lc code=end