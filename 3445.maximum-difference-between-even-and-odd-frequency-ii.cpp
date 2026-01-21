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
                
                vector<int> cnt_a(n + 1, 0), cnt_b(n + 1, 0);
                for (int i = 0; i < n; i++) {
                    cnt_a[i + 1] = cnt_a[i] + (s[i] == a);
                    cnt_b[i + 1] = cnt_b[i] + (s[i] == b);
                }
                
                int treeSize = n + 1;
                vector<vector<int>> minTree(4, vector<int>(2 * treeSize, INT_MAX));
                
                auto update = [&](int state, int pos, int val) {
                    pos += treeSize;
                    minTree[state][pos] = min(minTree[state][pos], val);
                    while (pos > 1) {
                        pos /= 2;
                        minTree[state][pos] = min(minTree[state][2 * pos], minTree[state][2 * pos + 1]);
                    }
                };
                
                auto query = [&](int state, int left, int right) -> int {
                    int res = INT_MAX;
                    left += treeSize;
                    right += treeSize;
                    while (left < right) {
                        if (left & 1) res = min(res, minTree[state][left++]);
                        if (right & 1) res = min(res, minTree[state][--right]);
                        left >>= 1;
                        right >>= 1;
                    }
                    return res;
                };
                
                for (int R = k; R <= n; R++) {
                    int L = R - k;
                    int diff_L = cnt_a[L] - cnt_b[L];
                    int state_L = (cnt_a[L] & 1) * 2 + (cnt_b[L] & 1);
                    update(state_L, cnt_b[L], diff_L);
                    
                    int parity_a_R = cnt_a[R] & 1;
                    int parity_b_R = cnt_b[R] & 1;
                    int needed_state = (1 - parity_a_R) * 2 + parity_b_R;
                    
                    if (cnt_b[R] > 0) {
                        int minDiff = query(needed_state, 0, cnt_b[R]);
                        if (minDiff != INT_MAX) {
                            int diff_R = cnt_a[R] - cnt_b[R];
                            ans = max(ans, diff_R - minDiff);
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};
# @lc code=end