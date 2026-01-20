#
# @lc app=leetcode id=3470 lang=cpp
#
# [3470] Permutations IV
#

# @lc code=start
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    long long cap = 2e15; // Slightly larger than max k

    long long safe_mul(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        if (a > cap / b) return cap;
        return a * b;
    }

    long long countWays(int co, int ce, int next_p, const vector<long long>& fact) {
        if (co == 0 && ce == 0) return 1;
        if (next_p == 1) { // Next must be odd
            if (co == ce || co == ce + 1) return safe_mul(fact[co], fact[ce]);
            return 0;
        } else { // Next must be even
            if (ce == co || ce == co + 1) return safe_mul(fact[ce], fact[co]);
            return 0;
        }
    }

public:
    vector<int> permute(int n, long long k) {
        vector<long long> fact(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = safe_mul(fact[i - 1], i);
        }

        vector<int> res;
        vector<bool> used(n + 1, false);
        int current_co = (n + 1) / 2;
        int current_ce = n / 2;
        int last_parity = -1;

        for (int i = 0; i < n; ++i) {
            bool found = false;
            for (int v = 1; v <= n; ++v) {
                if (used[v]) continue;
                int v_parity = v % 2; // 1 for odd, 0 for even
                if (last_parity != -1 && v_parity == last_parity) continue;

                int nco = current_co - (v_parity == 1 ? 1 : 0);
                int nce = current_ce - (v_parity == 0 ? 1 : 0);
                int next_p = 1 - v_parity;

                long long ways = countWays(nco, nce, next_p, fact);
                if (k <= ways) {
                    res.push_back(v);
                    used[v] = true;
                    last_parity = v_parity;
                    current_co = nco;
                    current_ce = nce;
                    found = true;
                    break;
                } else {
                    k -= ways;
                }
            }
            if (!found) return {};
        }

        return res;
    }
};
# @lc code=end