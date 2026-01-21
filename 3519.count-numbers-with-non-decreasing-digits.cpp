#
# @lc app=leetcode id=3519 lang=cpp
#
# [3519] Count Numbers with Non-Decreasing Digits
#
# @lc code=start
class Solution {
public:
    int countNumbers(string l, string r, int b) {
        const int MOD = 1e9 + 7;
        
        int countR = countUpTo(r, b, MOD);
        string l_minus_1 = subtract1(l);
        int countL = (l_minus_1.empty() || l_minus_1 == "0") ? 0 : countUpTo(l_minus_1, b, MOD);
        
        int result = (countR - countL + MOD) % MOD;
        return result;
    }
    
private:
    string subtract1(string s) {
        int n = s.length();
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] > '0') {
                s[i]--;
                break;
            } else {
                s[i] = '9';
            }
        }
        int i = 0;
        while (i < s.length() && s[i] == '0') i++;
        return i == s.length() ? "0" : s.substr(i);
    }
    
    vector<int> toBase(string s, int b) {
        vector<int> result;
        while (s != "0" && !s.empty()) {
            int remainder = 0;
            string next = "";
            for (char c : s) {
                int digit = c - '0';
                int curr = remainder * 10 + digit;
                if (!next.empty() || curr / b > 0) {
                    next += (char)('0' + curr / b);
                }
                remainder = curr % b;
            }
            result.push_back(remainder);
            s = next.empty() ? "0" : next;
        }
        reverse(result.begin(), result.end());
        return result;
    }
    
    int countUpTo(string s, int b, int MOD) {
        vector<int> digits = toBase(s, b);
        int n = digits.size();
        
        map<tuple<int, int, int, int>, int> memo;
        
        function<int(int, int, bool, bool)> dp = [&](int pos, int last_digit, bool tight, bool started) -> int {
            if (pos == n) {
                return started ? 1 : 0;
            }
            
            auto key = make_tuple(pos, last_digit, tight, started);
            if (memo.count(key)) {
                return memo[key];
            }
            
            int limit = tight ? digits[pos] : (b - 1);
            long long result = 0;
            
            for (int digit = 0; digit <= limit; digit++) {
                bool new_tight = tight && (digit == limit);
                
                if (!started) {
                    if (digit == 0) {
                        result = (result + dp(pos + 1, 0, new_tight, false)) % MOD;
                    } else {
                        result = (result + dp(pos + 1, digit, new_tight, true)) % MOD;
                    }
                } else {
                    if (digit >= last_digit) {
                        result = (result + dp(pos + 1, digit, new_tight, true)) % MOD;
                    }
                }
            }
            
            memo[key] = result;
            return result;
        };
        
        return dp(0, 0, true, false);
    }
};
# @lc code=end