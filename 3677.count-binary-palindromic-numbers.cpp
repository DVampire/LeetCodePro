#
# @lc app=leetcode id=3677 lang=cpp
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        std::string S;
        long long temp = n;
        if (temp == 0) {
            S = "0";
        } else {
            while (temp > 0) {
                S = char('0' + (temp & 1)) + S;
                temp >>= 1;
            }
        }
        int Len = S.size();
        long long ans = 1;  // for 0
        for (int L = 1; L < Len; ++L) {
            int exp = (L - 1) / 2;
            ans += (1LL << exp);
        }
        // Now for length Len
        int half_len = (Len + 1) / 2;
        int free_bits = half_len - 1;
        long long num_masks = free_bits >= 0 ? (1LL << free_bits) : 0;
        for (long long mask = 0; mask < num_masks; ++mask) {
            long long num = 0;
            // Set s[0] = 1
            num |= (1LL << (Len - 1));
            // Set s[Len-1] = 1
            num |= 1LL;
            for (int j = 0; j < free_bits; ++j) {
                int bit = (mask >> j) & 1;
                int pos = j + 1;
                // Set s[pos]
                num |= ((long long)bit << (Len - 1 - pos));
                // Set mirror s[Len-1-pos]
                int mir_pos = Len - 1 - pos;
                num |= ((long long)bit << (Len - 1 - mir_pos));
            }
            if (num <= n) {
                ++ans;
            }
        }
        return static_cast<int>(ans);
    }
};
# @lc code=end