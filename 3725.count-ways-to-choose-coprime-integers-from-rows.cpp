#include <bits/stdc++.h>
using namespace std;

// @lc app=leetcode id=3725 lang=cpp
//
// [3725] Count Ways to Choose Coprime Integers from Rows
//

// @lc code=start
class Solution {
public:
    int countCoprime(vector<vector<int>>& mat) {
        static const int V = 150;
        static const int MOD = 1000000007;

        // Compute Mobius function mu[1..V] using linear sieve
        vector<int> mu(V + 1, 0), primes;
        vector<int> isComp(V + 1, 0);
        mu[1] = 1;
        for (int i = 2; i <= V; i++) {
            if (!isComp[i]) {
                primes.push_back(i);
                mu[i] = -1;
            }
            for (int p : primes) {
                long long x = 1LL * i * p;
                if (x > V) break;
                isComp[(int)x] = 1;
                if (i % p == 0) {
                    mu[(int)x] = 0;
                    break;
                } else {
                    mu[(int)x] = -mu[i];
                }
            }
        }

        // prod[d] = product over rows of count of elements divisible by d
        vector<long long> prod(V + 1, 1);

        vector<int> freq(V + 1);
        for (auto &row : mat) {
            fill(freq.begin(), freq.end(), 0);
            for (int x : row) freq[x]++;

            for (int d = 1; d <= V; d++) {
                int cnt = 0;
                for (int k = d; k <= V; k += d) cnt += freq[k];
                prod[d] = (prod[d] * cnt) % MOD;
            }
        }

        long long ans = 0;
        for (int d = 1; d <= V; d++) {
            if (mu[d] == 0) continue;
            ans = (ans + (long long)mu[d] * prod[d]) % MOD;
        }
        if (ans < 0) ans += MOD;
        return (int)ans;
    }
};
// @lc code=end
