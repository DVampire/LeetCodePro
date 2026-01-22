//
// @lc app=leetcode id=3765 lang=cpp
//
// [3765] Complete Prime Number
//

// @lc code=start
class Solution {
public:
    bool isPrime(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; (long long)i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    bool completePrime(int num) {
        string s = to_string(num);
        int len = s.length();
        
        // Check all prefixes
        for (int i = 1; i <= len; i++) {
            int prefix = stoi(s.substr(0, i));
            if (!isPrime(prefix)) return false;
        }
        
        // Check all suffixes
        for (int i = 1; i <= len; i++) {
            int suffix = stoi(s.substr(len - i, i));
            if (!isPrime(suffix)) return false;
        }
        
        return true;
    }
};
// @lc code=end