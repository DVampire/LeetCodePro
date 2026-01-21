#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution {
public:
    bool isPrime(long long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (long long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    bool completePrime(int num) {
        if (num <= 1) return false;
        string s = to_string(num);
        int n = s.length();

        // Check prefixes
        long long prefix = 0;
        for (int i = 0; i < n; i++) {
            prefix = prefix * 10 + (s[i] - '0');
            if (!isPrime(prefix)) return false;
        }

        // Check suffixes
        long long suffix = 0;
        long long power = 1;
        for (int i = n - 1; i >= 0; i--) {
            suffix += (s[i] - '0') * power;
            if (!isPrime(suffix)) return false;
            power *= 10;
        }

        return true;
    }
};
# @lc code=end