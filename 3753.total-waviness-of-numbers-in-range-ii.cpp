#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#
# @lc code=start
class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
    
private:
    map<tuple<int, int, int, int, int>, pair<long long, long long>> memo;
    string numStr;
    
    pair<long long, long long> dp(int pos, int tight, int prev, int prevprev, int actualLen) {
        if (pos == numStr.size()) {
            return make_pair(actualLen > 0 ? 1LL : 0LL, 0LL);
        }
        
        auto key = make_tuple(pos, tight, prev, prevprev, actualLen);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int limit = tight ? (numStr[pos] - '0') : 9;
        long long totalCount = 0;
        long long totalWaviness = 0;
        
        for (int digit = 0; digit <= limit; digit++) {
            int newActualLen = actualLen;
            if (actualLen > 0 || digit > 0) {
                newActualLen = actualLen + 1;
            }
            int newTight = tight && (digit == limit);
            
            pair<long long, long long> result = dp(pos + 1, newTight, digit, prev, newActualLen);
            long long count = result.first;
            long long waviness = result.second;
            
            totalCount += count;
            totalWaviness += waviness;
            
            if (actualLen >= 2 && prev != -1 && prevprev != -1) {
                if ((prev > prevprev && prev > digit) || (prev < prevprev && prev < digit)) {
                    totalWaviness += count;
                }
            }
        }
        
        memo[key] = make_pair(totalCount, totalWaviness);
        return make_pair(totalCount, totalWaviness);
    }
    
    long long solve(long long num) {
        if (num < 0) return 0;
        numStr = to_string(num);
        memo.clear();
        pair<long long, long long> result = dp(0, 1, -1, -1, 0);
        return result.second;
    }
};
# @lc code=end