#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Find all runs in the original string
        vector<int> runs;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            runs.push_back(j - i);
            i = j;
        }
        
        // If no operations, return the longest run
        if (numOps == 0) {
            return *max_element(runs.begin(), runs.end());
        }
        
        // Binary search on the answer
        int left = 1, right = *max_element(runs.begin(), runs.end());
        int answer = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, runs, mid, numOps)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return answer;
    }
    
    bool canAchieve(const string& s, const vector<int>& runs, int k, int numOps) {
        // Special case for k = 1: check alternating patterns
        if (k == 1) {
            int flips0 = 0, flips1 = 0;
            for (int i = 0; i < s.length(); i++) {
                if ((i % 2 == 0 && s[i] != '0') || (i % 2 == 1 && s[i] != '1')) {
                    flips0++;
                }
                if ((i % 2 == 0 && s[i] != '1') || (i % 2 == 1 && s[i] != '0')) {
                    flips1++;
                }
            }
            return min(flips0, flips1) <= numOps;
        }
        
        // For k >= 2, count flips needed for each run
        int totalFlips = 0;
        for (int len : runs) {
            if (len > k) {
                totalFlips += (len - 1) / k;
            }
        }
        
        return totalFlips <= numOps;
    }
};
# @lc code=end