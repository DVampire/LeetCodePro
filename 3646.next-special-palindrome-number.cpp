#
# @lc app=leetcode id=3646 lang=cpp
#
# [3646] Next Special Palindrome Number
#
# @lc code=start
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    long long specialPalindrome(long long n) {
        vector<long long> specials;
        
        // Iterate through all subsets of digits {1, 2, ..., 9}
        // Represented by a bitmask from 1 to 2^9 - 1
        for (int mask = 1; mask < 512; ++mask) {
            vector<int> digits;
            int odd_digit = -1;
            int odd_count = 0;
            int length = 0;
            
            for (int i = 0; i < 9; ++i) {
                if ((mask >> i) & 1) {
                    int d = i + 1;
                    digits.push_back(d);
                    length += d;
                    if (d % 2 != 0) {
                        odd_count++;
                        odd_digit = d;
                    }
                }
            }
            
            // A palindrome can have at most one digit with an odd count.
            // Since digit d appears d times, we can have at most one odd digit in the set.
            if (odd_count > 1) continue;
            
            // Optimization: Since n <= 10^15, we only really care about numbers
            // with length up to ~16 or slightly more. 
            // Let's be generous and allow up to 20 to be safe, 
            // though the smallest answer > 10^15 will have length 16 or 17.
            // Actually, just generating all valid is fast enough given the constraints.
            // Max length with {2,4,6,8,9} is 29, which fits in string but not long long.
            // However, we need the smallest > n. If n is 10^15, we need something slightly larger.
            // long long max is ~9e18. Length 19 is the limit.
            if (length > 19) continue;
            
            string half_str = "";
            for (int d : digits) {
                int count_in_half = d / 2;
                for (int k = 0; k < count_in_half; ++k) {
                    half_str += to_string(d);
                }
            }
            
            sort(half_str.begin(), half_str.end());
            
            do {
                string full_str = half_str;
                string rev_half = half_str;
                reverse(rev_half.begin(), rev_half.end());
                
                if (odd_digit != -1) {
                    full_str += to_string(odd_digit);
                }
                full_str += rev_half;
                
                try {
                    // Only consider if it fits in long long and is valid
                    // stoll might throw out of range if length is too big, but we capped at 19
                    // actually long long max is 9223372036854775807 (19 digits).
                    // If length < 19, it fits. If length == 19, check overflow carefully or skip if clearly too large.
                    // Given n <= 10^15, we surely find an answer <= 10^17.
                    // So we can safely ignore anything >= 19 digits to avoid overflow headaches.
                    if (full_str.length() < 19) {
                        specials.push_back(stoll(full_str));
                    } else if (full_str.length() == 19) {
                         // Check if it exceeds LLONG_MAX, though for this problem n <= 10^15
                         // we don't strictly need 19 digit numbers.
                         // But let's be safe.
                         string llong_max_str = to_string(LLONG_MAX);
                         if (full_str.length() < llong_max_str.length() || 
                            (full_str.length() == llong_max_str.length() && full_str <= llong_max_str)) {
                             specials.push_back(stoll(full_str));
                         }
                    }
                } catch (...) {
                    // Ignore conversion errors
                }
                
            } while (next_permutation(half_str.begin(), half_str.end()));
        }
        
        sort(specials.begin(), specials.end());
        
        auto it = upper_bound(specials.begin(), specials.end(), n);
        if (it != specials.end()) {
            return *it;
        }
        
        return -1; // Should not reach here given constraints
    }
};
# @lc code=end