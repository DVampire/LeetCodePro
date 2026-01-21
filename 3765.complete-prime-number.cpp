#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#
# @lc code=start
class Solution {
public:
    bool isPrime(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    bool completePrime(int num) {
        string s = to_string(num);
        int n = s.length();
        
        // Check all prefixes
        for (int i = 1; i <= n; i++) {
            string prefix = s.substr(0, i);
            int prefixNum = stoi(prefix);
            if (!isPrime(prefixNum)) {
                return false;
            }
        }
        
        // Check all suffixes
        for (int i = 1; i <= n; i++) {
            string suffix = s.substr(n - i, i);
            int suffixNum = stoi(suffix);
            if (!isPrime(suffixNum)) {
                return false;
            }
        }
        
        return true;
    }
};
# @lc code=end