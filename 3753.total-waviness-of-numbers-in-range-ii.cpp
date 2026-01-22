#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#
# @lc code=start
class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        return f(num2) - f(num1 - 1);
    }
    
private:
    string digits;
    pair<long long, long long> memo[17][12][12][2];
    bool visited[17][12][12][2];
    
    long long f(long long n) {
        if (n < 0) return 0;
        digits = to_string(n);
        memset(visited, false, sizeof(visited));
        return dp(0, -1, -1, true).second;
    }
    
    // Returns (count, total_waviness)
    pair<long long, long long> dp(int pos, int prev, int prev2, bool tight) {
        if (pos == (int)digits.size()) {
            return {1, 0};
        }
        
        int p1 = prev + 1;
        int p2 = prev2 + 1;
        int t = tight ? 1 : 0;
        
        if (visited[pos][p1][p2][t]) {
            return memo[pos][p1][p2][t];
        }
        visited[pos][p1][p2][t] = true;
        
        int limit = tight ? (digits[pos] - '0') : 9;
        long long total_count = 0;
        long long total_waviness = 0;
        
        for (int d = 0; d <= limit; d++) {
            int new_prev, new_prev2;
            bool new_tight = tight && (d == limit);
            long long waviness_contribution = 0;
            
            if (prev == -1) {
                // Still in leading zeros
                if (d == 0) {
                    new_prev = -1;
                    new_prev2 = -1;
                } else {
                    new_prev = d;
                    new_prev2 = -1;
                }
            } else if (prev2 == -1) {
                // Exactly one digit placed
                new_prev2 = prev;
                new_prev = d;
            } else {
                // At least two digits placed, evaluate if prev is peak/valley
                if (prev > prev2 && prev > d) {
                    waviness_contribution = 1;  // prev is a peak
                } else if (prev < prev2 && prev < d) {
                    waviness_contribution = 1;  // prev is a valley
                }
                new_prev2 = prev;
                new_prev = d;
            }
            
            auto [cnt, wav] = dp(pos + 1, new_prev, new_prev2, new_tight);
            total_count += cnt;
            total_waviness += waviness_contribution * cnt + wav;
        }
        
        memo[pos][p1][p2][t] = {total_count, total_waviness};
        return memo[pos][p1][p2][t];
    }
};
# @lc code=end