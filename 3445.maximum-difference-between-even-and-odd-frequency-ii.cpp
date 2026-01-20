#
# @lc app=leetcode id=3445 lang=cpp
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.length();
        int max_diff = -2e9; // Initialize with a very small number
        bool found = false;

        string chars = "01234";
        
        // Iterate over all permutations of pairs (a, b)
        for (char a : chars) {
            for (char b : chars) {
                if (a == b) continue;
                
                // min_vals[parity_a][parity_b]
                // Stores the minimum prefix_diff encountered so far for a specific parity combination
                int min_vals[2][2];
                for(int i=0; i<2; ++i) 
                    for(int j=0; j<2; ++j) 
                        min_vals[i][j] = 1e9;
                        
                // History stores the state at each prefix index 0..n
                struct State {
                    int diff;
                    int pa_parity;
                    int pb_parity;
                };
                vector<State> history(n + 1);
                history[0] = {0, 0, 0};
                
                int curr_diff = 0;
                int curr_pa = 0;
                int curr_pb = 0;
                int last_b_idx = -1; // Index in s (0-based) of the last 'b' seen
                int l_ptr = 0; // Pointer to the next prefix index to add to min_vals
                
                for (int i = 0; i < n; ++i) {
                    // Update state with character s[i]
                    if (s[i] == a) {
                        curr_diff++;
                        curr_pa++;
                    } else if (s[i] == b) {
                        curr_diff--;
                        curr_pb++;
                        last_b_idx = i;
                    }
                    
                    // Current prefix index corresponds to substring s[0...i], length i+1
                    // We store this state at history[i+1]
                    int R = i + 1;
                    history[R] = {curr_diff, curr_pa % 2, curr_pb % 2};
                    
                    // Determine the range of valid L indices.
                    // 1. Length constraint: R - L >= k  =>  L <= R - k
                    // 2. Count(b) > 0 constraint: Pb[R] - Pb[L] > 0.
                    //    Since Pb is non-decreasing, and only increases at indices where s[x] == b,
                    //    Pb[R] includes the count of s[last_b_idx].
                    //    We need L such that Pb[L] < Pb[R].
                    //    This is satisfied if L <= last_b_idx. (Prefix index L corresponds to sum before s[L])
                    //    Actually, prefix L sums s[0...L-1]. Prefix last_b_idx sums s[0...last_b_idx-1].
                    //    Prefix last_b_idx+1 sums s[0...last_b_idx].
                    //    Pb[last_b_idx+1] > Pb[last_b_idx].
                    //    Pb[R] >= Pb[last_b_idx+1].
                    //    We need Pb[L] < Pb[R].
                    //    If L <= last_b_idx, then Pb[L] <= Pb[last_b_idx] < Pb[last_b_idx+1] <= Pb[R].
                    //    So the condition is L <= last_b_idx.
                    
                    int limit = min(R - k, last_b_idx);
                    
                    // Update min_vals with all newly available valid L indices
                    while (l_ptr <= limit) {
                        int p_a = history[l_ptr].pa_parity;
                        int p_b = history[l_ptr].pb_parity;
                        int val = history[l_ptr].diff;
                        if (val < min_vals[p_a][p_b]) {
                            min_vals[p_a][p_b] = val;
                        }
                        l_ptr++;
                    }
                    
                    // Check if we can form a valid substring ending at R
                    // We need count(a) to be odd => parity diff != 0
                    int target_pa = 1 - (curr_pa % 2);
                    // We need count(b) to be even => parity diff == 0
                    int target_pb = curr_pb % 2;
                    
                    if (min_vals[target_pa][target_pb] != 1e9) {
                        int diff = curr_diff - min_vals[target_pa][target_pb];
                        if (!found || diff > max_diff) {
                            max_diff = diff;
                            found = true;
                        }
                    }
                }
            }
        }
        
        return found ? max_diff : -1;
    }
};
# @lc code=end