#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution {
    long long memo_count[20][2][2][12][12];
    long long memo_sum[20][2][2][12][12];
    vector<int> digits;

    pair<long long, long long> solve(int idx, bool tight, bool isLeading, int prev, int prevPrev) {
        if (idx == digits.size()) {
            return {1, 0};
        }
        if (memo_count[idx][tight][isLeading][prev + 1][prevPrev + 1] != -1) {
            return {memo_count[idx][tight][isLeading][prev + 1][prevPrev + 1],
                    memo_sum[idx][tight][isLeading][prev + 1][prevPrev + 1]};
        }

        long long count = 0;
        long long sum = 0;
        int limit = tight ? digits[idx] : 9;

        for (int d = 0; d <= limit; ++d) {
            bool nextTight = tight && (d == limit);
            bool nextIsLeading = isLeading && (d == 0);
            
            int nextPrev, nextPrevPrev;
            if (nextIsLeading) {
                nextPrev = -1;
                nextPrevPrev = -1;
            } else {
                nextPrev = d;
                nextPrevPrev = prev;
            }

            pair<long long, long long> nextRes = solve(idx + 1, nextTight, nextIsLeading, nextPrev, nextPrevPrev);
            
            long long wavinessAdded = 0;
            if (!isLeading && prevPrev != -1) {
                // A peak/valley is defined by three digits: prevPrev (idx-2), prev (idx-1), and d (idx).
                if ((prev > prevPrev && prev > d) || (prev < prevPrev && prev < d)) {
                    wavinessAdded = 1;
                }
            }

            count += nextRes.first;
            sum += nextRes.second + wavinessAdded * nextRes.first;
        }

        memo_count[idx][tight][isLeading][prev + 1][prevPrev + 1] = count;
        memo_sum[idx][tight][isLeading][prev + 1][prevPrev + 1] = sum;
        return {count, sum};
    }

    long long countWaviness(long long n) {
        if (n < 100) return 0;
        string s = to_string(n);
        digits.clear();
        for (char c : s) digits.push_back(c - '0');
        
        memset(memo_count, -1, sizeof(memo_count));
        memset(memo_sum, -1, sizeof(memo_sum));
        
        return solve(0, true, true, -1, -1).sum;
    }

public:
    long long totalWaviness(long long num1, long long num2) {
        return countWaviness(num2) - countWaviness(num1 - 1);
    }
};
# @lc code=end