#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    bool canAchieve(string s, int maxLen, int numOps) {
        int n = s.length();
        
        if (maxLen == 1) {
            // Special case: alternating pattern
            int flips1 = 0, flips2 = 0;
            for (int i = 0; i < n; i++) {
                if (s[i] != ('0' + i % 2)) flips1++;
                if (s[i] != ('1' - i % 2)) flips2++;
            }
            return min(flips1, flips2) <= numOps;
        }
        
        // General case: count flips needed for each run
        int flipsNeeded = 0;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            int runLength = j - i;
            flipsNeeded += runLength / (maxLen + 1);
            if (flipsNeeded > numOps) return false;
            i = j;
        }
        return true;
    }
    
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Find the maximum run length in the original string
        int maxRun = 1;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            maxRun = max(maxRun, j - i);
            i = j;
        }
        
        // Binary search on the answer
        int left = 1, right = maxRun;
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, mid, numOps)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
};
# @lc code=end