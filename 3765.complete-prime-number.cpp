#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    bool completePrime(int num) {
        // Check prefixes
        int temp = num;
        while (temp > 0) {
            if (!isPrime(temp)) {
                return false;
            }
            temp /= 10;
        }

        // Check suffixes
        // We need to check num % 10, num % 100, num % 1000 ... until the suffix is the number itself
        long long mod = 10;
        while (true) {
            int suffix = num % mod;
            if (!isPrime(suffix)) {
                return false;
            }
            // If the suffix is the number itself, we are done checking suffixes
            if (suffix == num) break;
            mod *= 10;
        }

        return true;
    }
};
# @lc code=end