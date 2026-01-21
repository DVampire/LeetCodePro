#
# @lc app=leetcode id=3445 lang=cpp
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#
# @lc code=start
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        int ans = INT_MIN;
        
        for (char a = '0'; a <= '4'; a++) {
            for (char b = '0'; b <= '4'; b++) {
                if (a == b) continue;
                
                // Compute prefix sums
                vector<int> prefix_a(n + 1, 0), prefix_b(n + 1, 0);
                for (int i = 0; i < n; i++) {
                    prefix_a[i + 1] = prefix_a[i] + (s[i] == a ? 1 : 0);
                    prefix_b[i + 1] = prefix_b[i] + (s[i] == b ? 1 : 0);
                }
                
                // min_diff[pa][pb] = minimum (prefix_a - prefix_b) for valid positions
                vector<vector<int>> min_diff(2, vector<int>(2, INT_MAX));
                vector<tuple<int, int, int>> pending; // waiting for a 'b' to appear
                
                for (int r = k; r <= n; r++) {
                    // Flush pending if we just saw a 'b'
                    if (s[r - 1] == b) {
                        for (auto& [d, pa, pb] : pending) {
                            min_diff[pa][pb] = min(min_diff[pa][pb], d);
                        }
                        pending.clear();
                    }
                    
                    // Add l = r - k
                    int l = r - k;
                    int diff_l = prefix_a[l] - prefix_b[l];
                    int pa_l = prefix_a[l] % 2;
                    int pb_l = prefix_b[l] % 2;
                    
                    if (prefix_b[r] > prefix_b[l]) {
                        // Already have a 'b' between l and r, add directly
                        min_diff[pa_l][pb_l] = min(min_diff[pa_l][pb_l], diff_l);
                    } else {
                        // Wait for a 'b' to appear
                        pending.push_back({diff_l, pa_l, pb_l});
                    }
                    
                    // Query for current r
                    int diff_r = prefix_a[r] - prefix_b[r];
                    int pa_r = prefix_a[r] % 2;
                    int pb_r = prefix_b[r] % 2;
                    int target_pa = 1 - pa_r;  // opposite parity for odd freq_a
                    int target_pb = pb_r;      // same parity for even freq_b
                    
                    if (min_diff[target_pa][target_pb] != INT_MAX) {
                        ans = max(ans, diff_r - min_diff[target_pa][target_pb]);
                    }
                }
            }
        }
        
        return ans;
    }
};
# @lc code=end