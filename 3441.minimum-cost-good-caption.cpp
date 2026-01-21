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
        
        // Precompute prefix costs
        vector<vector<int>> prefix(n + 1, vector<int>(26, 0));
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 26; c++) {
                prefix[i + 1][c] = prefix[i][c] + abs(caption[i] - 'a' - c);
            }
        }
        
        auto getCost = [&](int start, int end, int c) {
            return prefix[end][c] - prefix[start][c];
        };
        
        const int INF = 1e9;
        
        // Backward DP: suffix[i] = min cost to make caption[i..n-1] a good caption
        vector<int> suffix(n + 1, INF);
        suffix[n] = 0;
        
        for (int i = n - 3; i >= 0; i--) {
            for (int len = 3; len <= 5 && i + len <= n; len++) {
                if (suffix[i + len] == INF) continue;
                for (int c = 0; c < 26; c++) {
                    suffix[i] = min(suffix[i], getCost(i, i + len, c) + suffix[i + len]);
                }
            }
        }
        
        if (suffix[0] == INF) return "";
        
        // Track best_c[i] and best_len[i] for lex smallest suffix
        vector<int> best_c(n + 1, -1), best_len(n + 1, 0);
        
        for (int i = n - 3; i >= 0; i--) {
            if (suffix[i] == INF) continue;
            
            // Find smallest valid character
            int min_c = -1;
            for (int c = 0; c < 26 && min_c == -1; c++) {
                for (int len = 3; len <= 5 && i + len <= n; len++) {
                    if (suffix[i + len] != INF && getCost(i, i + len, c) + suffix[i + len] == suffix[i]) {
                        min_c = c;
                        break;
                    }
                }
            }
            
            // Find valid lengths for this character
            vector<int> valid_lens;
            for (int len = 3; len <= 5 && i + len <= n; len++) {
                if (suffix[i + len] != INF && getCost(i, i + len, min_c) + suffix[i + len] == suffix[i]) {
                    valid_lens.push_back(len);
                }
            }
            
            // Find the length that gives lex smallest suffix
            int best = valid_lens[0];
            for (size_t k = 1; k < valid_lens.size(); k++) {
                if (compareSuffixes(i, min_c, best, min_c, valid_lens[k], best_c, best_len, n) > 0) {
                    best = valid_lens[k];
                }
            }
            
            best_c[i] = min_c;
            best_len[i] = best;
        }
        
        // Reconstruct the result
        string result;
        for (int pos = 0; pos < n; ) {
            result += string(best_len[pos], 'a' + best_c[pos]);
            pos += best_len[pos];
        }
        
        return result;
    }
    
private:
    int compareSuffixes(int i, int c_a, int len_a, int c_b, int len_b, 
                         vector<int>& best_c, vector<int>& best_len, int n) {
        int seg_start_a = i, seg_len_a = len_a, seg_char_a = c_a, seg_offset_a = 0;
        int seg_start_b = i, seg_len_b = len_b, seg_char_b = c_b, seg_offset_b = 0;
        
        while (true) {
            if (seg_char_a != seg_char_b) return (seg_char_a < seg_char_b) ? -1 : 1;
            
            int rem_a = seg_len_a - seg_offset_a;
            int rem_b = seg_len_b - seg_offset_b;
            int advance = min(rem_a, rem_b);
            seg_offset_a += advance;
            seg_offset_b += advance;
            
            if (seg_offset_a == seg_len_a) {
                int next_a = seg_start_a + seg_len_a;
                if (next_a >= n) {
                    if (seg_offset_b == seg_len_b && seg_start_b + seg_len_b >= n) return 0;
                    return -1;
                }
                seg_start_a = next_a;
                seg_len_a = best_len[seg_start_a];
                seg_char_a = best_c[seg_start_a];
                seg_offset_a = 0;
            }
            
            if (seg_offset_b == seg_len_b) {
                int next_b = seg_start_b + seg_len_b;
                if (next_b >= n) {
                    return 1;
                }
                seg_start_b = next_b;
                seg_len_b = best_len[seg_start_b];
                seg_char_b = best_c[seg_start_b];
                seg_offset_b = 0;
            }
        }
    }
};
# @lc code=end