#
# @lc app=leetcode id=3513 lang=cpp
#
# [3513] Number of Unique XOR Triplets I
#

# @lc code=start
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    /**
     * The set of possible values is T = {a ^ b ^ c | a, b, c in {1, ..., n}}.
     * For n=1, T = {1}, size 1.
     * For n=2, T = {1, 2}, size 2.
     * For n >= 3, T is the entire span of {1, ..., n}.
     * The span of {1, ..., n} is {0, 1, ..., 2^k - 1} where 2^k > n.
     */
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        
        // Find the smallest power of 2 strictly greater than n.
        // This defines the range [0, 2^k - 1].
        int k = 0;
        while ((1 << k) <= n) {
            k++;
        }
        return (1 << k);
    }
};
# @lc code=end