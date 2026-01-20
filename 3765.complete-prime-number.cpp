#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#

# @lc code=start
#include <string>
#include <cmath>

class Solution {
public:
    /**
     * Helper function to check if a number is prime.
     * Time complexity: O(sqrt(n))
     */
    bool isPrime(long long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (long long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    /**
     * Main function to determine if num is a Complete Prime Number.
     * Every prefix and suffix must be prime.
     */
    bool completePrime(int num) {
        std::string s = std::to_string(num);
        int len = s.length();

        // Check all prefixes
        // A prefix of length i is formed by the first i digits.
        for (int i = 1; i <= len; ++i) {
            long long prefixVal = std::stoll(s.substr(0, i));
            if (!isPrime(prefixVal)) {
                return false;
            }
        }

        // Check all suffixes
        // A suffix of length i is formed by the last i digits.
        for (int i = 1; i <= len; ++i) {
            long long suffixVal = std::stoll(s.substr(len - i));
            if (!isPrime(suffixVal)) {
                return false;
            }
        }

        return true;
    }
};
# @lc code=end