#
# @lc app=leetcode id=3441 lang=cpp
#
# [3441] Minimum Cost Good Caption
#
# @lc code=start
class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.size();
        if (n < 3) return "";
        
        vector<vector<long long>> prefix(n + 1, vector<long long>(26, 0));
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 26; c++) {
                prefix[i + 1][c] = prefix[i][c] + abs((caption[i] - 'a') - c);
            }
        }
        
        auto segmentCost = [&](int i, int j, int c) -> long long {
            return prefix[j][c] - prefix[i][c];
        };
        
        const long long INF = 1e18;
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int remaining = n - i;
            if (remaining < 3) continue;
            
            if (remaining <= 5) {
                for (int c = 0; c < 26; c++) {
                    dp[i] = min(dp[i], segmentCost(i, n, c));
                }
            } else {
                for (int L = 3; L <= 5; L++) {
                    for (int c = 0; c < 26; c++) {
                        dp[i] = min(dp[i], segmentCost(i, i + L, c) + dp[i + L]);
                    }
                }
            }
        }
        
        if (dp[0] == INF) return "";
        
        vector<int> first_char(n + 1, -1);
        vector<int> char_prefix_len(n + 1, 0);
        vector<pair<int, int>> choice(n + 1, {-1, -1});
        
        for (int i = n - 1; i >= 0; i--) {
            int remaining = n - i;
            if (remaining < 3 || dp[i] == INF) continue;
            
            int best_c = -1, best_L = -1, best_prefix_len = 0;
            
            vector<int> valid_L;
            if (remaining <= 5) {
                valid_L.push_back(remaining);
            } else {
                valid_L = {3, 4, 5};
            }
            
            for (int c = 0; c < 26; c++) {
                for (int L : valid_L) {
                    long long cost = segmentCost(i, i + L, c);
                    if (i + L < n) cost += dp[i + L];
                    if (cost != dp[i]) continue;
                    
                    int len_new = L;
                    if (i + L < n && first_char[i + L] == c) {
                        len_new += char_prefix_len[i + L];
                    }
                    
                    bool is_better = false;
                    if (best_c == -1) {
                        is_better = true;
                    } else if (c < best_c) {
                        is_better = true;
                    } else if (c == best_c) {
                        if (len_new < best_prefix_len) {
                            int pos = i + len_new;
                            if (pos == n || first_char[pos] < c) {
                                is_better = true;
                            }
                        } else if (len_new > best_prefix_len) {
                            int pos = i + best_prefix_len;
                            if (pos < n && c < first_char[pos]) {
                                is_better = true;
                            }
                        }
                    }
                    
                    if (is_better) {
                        best_c = c;
                        best_L = L;
                        best_prefix_len = len_new;
                    }
                }
            }
            
            first_char[i] = best_c;
            char_prefix_len[i] = best_prefix_len;
            choice[i] = {best_L, best_c};
        }
        
        string result;
        int pos = 0;
        while (pos < n) {
            int L = choice[pos].first;
            int c = choice[pos].second;
            result += string(L, 'a' + c);
            pos += L;
        }
        
        return result;
    }
};
# @lc code=end