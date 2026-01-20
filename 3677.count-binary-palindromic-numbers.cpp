#
# @lc app=leetcode id=3677 lang=cpp
#
# [3677] Count Binary Palindromic Numbers
#
# @lc code=start
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;
        
        // Get bit length of n
        // Using 64 - __builtin_clzll(n) for positive n gives length.
        int len = 0;
        long long temp = n;
        while (temp > 0) {
            len++;
            temp >>= 1;
        }
        
        long long count = 1; // Start with 1 to count '0'
        
        // 1. Count palindromes with length < len
        for (int l = 1; l < len; ++l) {
            int halfLen = (l + 1) / 2;
            // The first bit is always 1. The remaining halfLen - 1 bits can be anything.
            // So there are 2^(halfLen - 1) palindromes.
            count += (1LL << (halfLen - 1));
        }
        
        // 2. Count palindromes with length == len
        int halfLen = (len + 1) / 2;
        
        // Extract the first halfLen bits of n
        long long prefixVal = n >> (len - halfLen);
        
        // The smallest possible value for the first halfLen bits (since MSB must be 1)
        long long minPrefixVal = 1LL << (halfLen - 1);
        
        // All prefixes strictly between minPrefixVal and prefixVal correspond to 
        // palindromes strictly smaller than n.
        if (prefixVal > minPrefixVal) {
            count += (prefixVal - minPrefixVal);
        }
        
        // Now check the palindrome formed by prefixVal itself
        long long palindrome = createPalindrome(prefixVal, len, halfLen);
        if (palindrome <= n) {
            count++;
        }
        
        return (int)count;
    }
    
private:
    // Creates a palindrome of total length 'len' using 'prefix' which has 'halfLen' bits
    long long createPalindrome(long long prefix, int len, int halfLen) {
        long long res = prefix;
        // If len is odd, the last bit of prefix is the middle element and shouldn't be mirrored.
        // If len is even, all bits are mirrored.
        long long toMirror = prefix;
        if (len % 2 != 0) {
            toMirror >>= 1;
        }
        
        for (int i = 0; i < len - halfLen; ++i) {
            res <<= 1;
            res |= (toMirror & 1);
            toMirror >>= 1;
        }
        return res;
    }
};
# @lc code=end