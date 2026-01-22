//
// @lc app=leetcode id=3621 lang=cpp
//
// [3621] Number of Integers With Popcount-Depth Equal to K I
//

// @lc code=start
class Solution {
public:
    long long C[51][51];
    int dep[51];
    
    long long popcountDepth(long long n, int k) {
        memset(C, 0, sizeof(C));
        memset(dep, 0, sizeof(dep));
        
        // Precompute binomial coefficients
        for (int i = 0; i <= 50; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
            }
        }
        
        // Precompute depths for values 1 to 50 (max possible popcount)
        dep[1] = 0;
        for (int i = 2; i <= 50; i++) {
            dep[i] = 1 + dep[__builtin_popcount(i)];
        }
        
        if (k == 0) {
            return n >= 1 ? 1 : 0;
        }
        
        // Count numbers in [0, num] with exactly c set bits
        auto countBits = [&](long long num, int c) -> long long {
            if (num < 0 || c < 0 || c > 50) return 0;
            if (c == 0) return 1;
            
            vector<int> bits;
            long long temp = num;
            while (temp > 0) {
                bits.push_back(temp & 1);
                temp >>= 1;
            }
            reverse(bits.begin(), bits.end());
            
            int m = bits.size();
            if (c > m) return 0;
            
            long long result = 0;
            int usedBits = 0;
            
            for (int i = 0; i < m; i++) {
                if (bits[i] == 1) {
                    int remaining = m - i - 1;
                    int need = c - usedBits;
                    if (need >= 0 && need <= remaining) {
                        result += C[remaining][need];
                    }
                    usedBits++;
                }
            }
            
            if (usedBits == c) result++;
            
            return result;
        };
        
        long long result = 0;
        for (int c = 1; c <= 50; c++) {
            if (dep[c] == k - 1) {
                result += countBits(n, c);
            }
        }
        
        // For k=1, we counted x=1 (popcount 1 has depth 0), but x=1 has depth 0, not 1
        if (k == 1) {
            result -= 1;
        }
        
        return result;
    }
};
// @lc code=end