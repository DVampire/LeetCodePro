#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Specialized check for k = 1.
     * For k = 1, the string must be perfectly alternating (0101... or 1010...).
     */
    bool check1(const string& s, int numOps) {
        int n = s.length();
        int ops0 = 0; // flips needed to make s match "010101..."
        for (int i = 0; i < n; ++i) {
            char expected = (i % 2 == 0) ? '0' : '1';
            if (s[i] != expected) ops0++;
        }
        // flips needed for "101010..." is simply n - ops0
        return min(ops0, n - ops0) <= numOps;
    }

    /**
     * Greedy check for k >= 2.
     * For each block of identical characters of length L, we need floor(L / (k+1)) flips.
     */
    bool checkK(const string& s, int k, int numOps) {
        int totalOps = 0;
        int n = s.length();
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && s[i] == s[i - 1]) {
                count++;
            } else {
                totalOps += count / (k + 1);
                count = 1;
            }
        }
        totalOps += count / (k + 1);
        return totalOps <= numOps;
    }

    int minLength(string s, int numOps) {
        int n = s.length();
        int l = 1, r = n, ans = n;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            bool possible = false;
            
            if (mid == 1) {
                possible = check1(s, numOps);
            } else {
                possible = checkK(s, mid, numOps);
            }

            if (possible) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return ans;
    }
};
# @lc code=end