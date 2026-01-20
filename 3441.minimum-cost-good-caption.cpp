#
# @lc app=leetcode id=3441 lang=cpp
#
# [3441] Minimum Cost Good Caption
#
# @lc code=start
class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.length();
        if (n < 3) return "";

        // dp[i] stores the minimum cost to make caption[i...n-1] a good caption.
        vector<int> dp(n + 1, 2e9);
        // next_char[i] stores the character chosen for the block starting at i in the optimal solution.
        vector<int> next_char(n + 1, -1);
        dp[n] = 0;

        // Fill DP table from right to left
        for (int i = n - 1; i >= 0; --i) {
            for (int c = 0; c < 26; ++c) {
                char current_char = 'a' + c;
                int current_cost = 0;
                
                // Try block lengths of 3, 4, and 5
                for (int len = 1; len <= 5; ++len) {
                    if (i + len > n) break;
                    
                    // Incremental cost calculation
                    current_cost += abs(caption[i + len - 1] - current_char);
                    
                    if (len >= 3) {
                        if (dp[i + len] != 2e9) {
                            int total_cost = current_cost + dp[i + len];
                            // If we found a smaller cost, update.
                            // Since we iterate c from 0 to 25, the first time we find the min cost,
                            // it corresponds to the lexicographically smallest character for this block.
                            if (total_cost < dp[i]) {
                                dp[i] = total_cost;
                                next_char[i] = c;
                            }
                        }
                    }
                }
            }
        }

        // If impossible to form a good caption
        if (dp[0] == 2e9) return "";

        string result = "";
        int i = 0;
        while (i < n) {
            int c = next_char[i];
            char char_c = 'a' + c;
            
            // We need to determine the best length for the current block of character 'c'.
            // We re-calculate costs to identify which lengths (3, 4, 5) result in the optimal dp[i].
            vector<int> valid_lens;
            int current_cost = 0;
            
            // Pre-calculate cost for first 2 chars
            for(int k=0; k<2 && i+k<n; ++k) current_cost += abs(caption[i+k] - char_c);
            
            // Check lengths 3, 4, 5
            for (int len = 3; len <= 5; ++len) {
                if (i + len > n) break;
                current_cost += abs(caption[i + len - 1] - char_c);
                
                if (dp[i + len] != 2e9 && current_cost + dp[i + len] == dp[i]) {
                    valid_lens.push_back(len);
                }
            }
            
            // Tie-breaking logic for length:
            // We prefer the length that results in a lexicographically smaller suffix.
            // Compare valid lengths pairwise. Start with the smallest valid length.
            int best_len = valid_lens[0];
            
            for (size_t k = 1; k < valid_lens.size(); ++k) {
                int len = valid_lens[k];
                // Imagine we picked 'best_len'. The next block would start at i + best_len.
                // The first character of that next block is next_char[i + best_len].
                // If i + best_len == n, it's the end of string (conceptually smaller than any char).
                int next_c_val = (i + best_len == n) ? -1 : next_char[i + best_len];
                
                // If the next character after the shorter block (best_len) is larger than 'c',
                // it means the shorter block exposes a "bad" character. 
                // Extending 'c' (choosing the longer 'len') covers it with 'c', which is smaller.
                // So we switch to the longer length.
                if (next_c_val > c) {
                    best_len = len;
                }
                // If next_c_val <= c, the shorter block transitions to something smaller or equal,
                // so we prefer the shorter block (or it doesn't matter if equal, shorter is fine).
            }
            
            for (int k = 0; k < best_len; ++k) result += char_c;
            i += best_len;
        }
        return result;
    }
};
# @lc code=end