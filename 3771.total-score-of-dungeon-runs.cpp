#
# @lc app=leetcode id=3771 lang=cpp
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size();
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + damage[i];
        }

        long long total_score = 0;
        for (int k = 1; k <= n; ++k) {
            // Condition for a point in room k starting from room j:
            // hp - (pref[k] - pref[j-1]) >= requirement[k]
            // pref[j-1] >= pref[k] + requirement[k] - hp
            long long target = (long long)pref[k] + requirement[k - 1] - hp;
            
            if (target <= 0) {
                // All j from 1 to k satisfy pref[j-1] >= target since pref[j-1] >= 0
                total_score += k;
            } else {
                // Find the first j-1 in [0, k-1] such that pref[j-1] >= target
                // Using binary search on the prefix sum array up to index k-1
                auto it = lower_bound(pref.begin(), pref.begin() + k, target);
                int first_idx = distance(pref.begin(), it);
                
                if (first_idx < k) {
                    // Indices from first_idx up to k-1 are valid
                    total_score += (k - first_idx);
                }
            }
        }

        return total_score;
    }
};
# @lc code=end