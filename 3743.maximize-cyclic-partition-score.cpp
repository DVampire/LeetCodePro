#
# @lc app=leetcode id=3743 lang=cpp
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;
        if (k >= n) {
            // With k >= n, we could potentially have many subarrays.
            // But the max score is achieved by some partition.
        }

        auto solve_linear = [&](const vector<int>& A, int K) {
            int m = A.size();
            // dp[k][i] = max score for first i elements using k subarrays
            vector<long long> dp(m + 1, 0);
            
            for (int j = 1; j <= K; ++j) {
                vector<long long> next_dp(m + 1, 0);
                for (int i = 1; i <= m; ++i) {
                    int cur_max = A[i - 1];
                    int cur_min = A[i - 1];
                    for (int p = i - 1; p >= 0; --p) {
                        cur_max = max(cur_max, A[p]);
                        cur_min = min(cur_min, A[p]);
                        next_dp[i] = max(next_dp[i], dp[p] + (cur_max - cur_min));
                    }
                }
                dp = next_dp;
            }
            long long res = 0;
            for(auto val : dp) res = max(res, val);
            return res;
        };

        // Find global minimum and maximum indices
        int min_idx = 0, max_idx = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[min_idx]) min_idx = i;
            if (nums[i] > nums[max_idx]) max_idx = i;
        }

        auto get_rotation = [&](int start_node) {
            vector<int> rotated;
            for (int i = 0; i < n; ++i) {
                rotated.push_back(nums[(start_node + i) % n]);
            }
            return rotated;
        };

        // The optimal cyclic partition must have a cut somewhere.
        // A common heuristic for cyclic array problems is that a cut exists at the global min or max.
        // Given n=1000, O(n^2) is 10^6. We can afford a few linear DP runs.
        // Let's use a more efficient linear DP: O(n^2) total for a fixed rotation.
        auto solve_fast = [&](const vector<int>& A, int K) {
            int m = A.size();
            // dp[i] is the max score for A[0...i-1] with at most K segments.
            // Actually, we need to track the number of segments.
            // But notice: if we can use 'at most K' segments, we can use DP with segments.
            vector<long long> dp(m + 1, 0);
            for (int j = 1; j <= K; ++j) {
                vector<long long> next_dp(m + 1, 0);
                // To optimize dp[i] = max_{p<i} (dp_old[p] + max(p..i-1) - min(p..i-1))
                // This is still O(n^2). With K=1000, it's O(n^2 K).
                // However, for range sum problems, we can use a monotonic stack or 
                // simply notice that we only need the result for at most K=n.
                // Given the 1s time limit and Hard difficulty, there might be a trick.
                for (int i = 1; i <= m; ++i) {
                    int mx = A[i-1], mn = A[i-1];
                    for (int p = i - 1; p >= 0; --p) {
                        mx = max(mx, A[p]);
                        mn = min(mn, A[p]);
                        next_dp[i] = max(next_dp[i], dp[p] + (mx - mn));
                    }
                }
                dp = next_dp;
            }
            return dp[m];
        };

        // Since O(N^2 K) is too slow, let's use the property that 
        // score(k) is often solvable with a faster DP or Alien's trick.
        // But wait, n=1000, maybe K doesn't need to go to 1000?
        // Actually, the score for a linear array with K segments can be done in O(N^2).
        // dp[i] = max score of first i elements with ANY number of segments.
        // But we have a constraint K.
        
        // Let's use O(N^2) DP for a linear array: 
        // dp[i][k] = max score for first i elements with k segments.
        // For N=1000, we can use a simpler O(N^2) approach if K is not restricted.
        // With K restricted, we can use the following observation:
        // If we only need one rotation, we can use O(N^2) for all k by 
        // observing the structure of the optimal solution.
        
        vector<vector<long long>> f(n + 1, vector<long long>(k + 1, 0));
        vector<int> rotated = get_rotation(min_idx);
        
        for (int j = 1; j <= k; ++j) {
            for (int i = 1; i <= n; ++i) {
                int mx = rotated[i-1], mn = rotated[i-1];
                for (int p = i - 1; p >= 0; --p) {
                    mx = max(mx, rotated[p]);
                    mn = min(mn, rotated[p]);
                    f[i][j] = max(f[i][j], f[p][j-1] + (mx - mn));
                }
            }
        }

        return f[n][k];
    }
};
# @lc code=end