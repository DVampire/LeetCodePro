#
# @lc app=leetcode id=3420 lang=cpp
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#
# @lc code=start
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        reverse(nums.begin(), nums.end());
        
        long long ans = 0, cost = 0;
        // Deque stores (value, count) pairs in decreasing order from front to back
        deque<pair<long long, int>> dq;
        
        for (int i = 0, j = 0; i < n; i++) {
            // Add nums[i] to the window
            int cnt = 1;
            // Merge all smaller or equal elements from the back
            while (!dq.empty() && dq.back().first <= nums[i]) {
                auto [v, c] = dq.back();
                dq.pop_back();
                // These elements are now dominated by nums[i]
                cost += (long long)(nums[i] - v) * c;
                cnt += c;
            }
            dq.push_back({nums[i], cnt});
            
            // Shrink window from the left while cost exceeds k
            while (cost > k) {
                auto& [v, c] = dq.front();
                if (c == 1) {
                    dq.pop_front();
                    // Adjust cost: the second element was being dominated by v
                    if (!dq.empty()) {
                        cost -= dq.front().first - v;
                    }
                } else {
                    // Remove one element from the front block
                    c--;
                    // This element was dominated by the next block's value
                    if (dq.size() > 1) {
                        auto it = dq.begin();
                        ++it;
                        cost -= it->first - v;
                    }
                }
                j++;
            }
            
            ans += i - j + 1;
        }
        
        return ans;
    }
};
# @lc code=end