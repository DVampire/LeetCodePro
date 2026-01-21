//
// @lc app=leetcode id=3399 lang=cpp
//
// [3399] Smallest Substring With Identical Characters II
//

// @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Compute runs
        vector<int> runs;
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i-1]) {
                count++;
            } else {
                runs.push_back(count);
                count = 1;
            }
        }
        runs.push_back(count);
        
        // Check if max run ≤ L is achievable with given ops
        auto check = [&](int L) -> int {
            if (L == 1) {
                // Count mismatches for two alternating patterns
                int mismatch0 = 0, mismatch1 = 0;
                for (int i = 0; i < n; i++) {
                    int expected0 = i % 2; // "010101..."
                    int expected1 = 1 - i % 2; // "101010..."
                    int actual = s[i] - '0';
                    if (actual != expected0) mismatch0++;
                    if (actual != expected1) mismatch1++;
                }
                return min(mismatch0, mismatch1);
            } else {
                // Sum of (run_length / (L + 1)) for each run
                int ops = 0;
                for (int len : runs) {
                    ops += len / (L + 1);
                }
                return ops;
            }
        };
        
        // Binary search on L
        int maxRun = *max_element(runs.begin(), runs.end());
        int lo = 1, hi = maxRun;
        int ans = hi;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (check(mid) <= numOps) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};
// @lc code=end