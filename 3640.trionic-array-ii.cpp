#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        if (n < 4) return 0; 

        const long long INF = 4e18; 

        vector<long long> PS(n);
        PS[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            PS[i] = PS[i - 1] + nums[i];
        }

        vector<long long> L(n, -INF);
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                L[i] = (long long)nums[i] + max((long long)nums[i - 1], L[i - 1]);
            }
        }

        vector<long long> R(n, -INF);
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                R[i] = (long long)nums[i] + max((long long)nums[i + 1], R[i + 1]);
            }
        }

        long long ans = -INF;

        for (int i = 0; i < n - 1; ) {
            if (nums[i] > nums[i + 1]) {
                int a = i;
                while (i < n - 1 && nums[i] > nums[i + 1]) {
                    i++;
                }
                int b = i;

                // Process strictly decreasing segment [a, b]
                // Maximize (L[p] - PS[p]) + (R[q] + PS[q-1]) for a <= p < q <= b
                long long max_f = -INF;
                for (int q = a + 1; q <= b; ++q) {
                    int p = q - 1;
                    if (L[p] > -INF / 2) {
                        max_f = max(max_f, L[p] - PS[p]);
                    }
                    if (max_f > -INF / 2 && R[q] > -INF / 2) {
                        ans = max(ans, max_f + R[q] + PS[q - 1]);
                    }
                }
            } else {
                i++;
            }
        }

        return ans;
    }
};
# @lc code=end