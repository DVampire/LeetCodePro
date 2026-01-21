#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    long long popcountDepth(long long n, int k) {
        if (n <= 0) return 0;
        if (k == 0) return (n >= 1 ? 1LL : 0LL); // only x = 1

        const int MAXB = 64;

        // Binomial coefficients C[i][j] = i choose j
        vector<vector<long long>> C(MAXB + 1, vector<long long>(MAXB + 1, 0));
        for (int i = 0; i <= MAXB; i++) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }

        // Precompute depth for m up to MAXB
        vector<int> depth(MAXB + 1, -1);
        function<int(int)> getDepth = [&](int x) -> int {
            if (x <= 1) return 0;
            int &res = depth[x];
            if (res != -1) return res;
            int pc = __builtin_popcount((unsigned)x);
            res = 1 + getDepth(pc);
            return res;
        };
        depth[0] = 0; // not used for x>0, but keeps recursion safe
        depth[1] = 0;
        for (int m = 2; m <= MAXB; m++) getDepth(m);

        auto countLEQ = [&](long long limit, int ones) -> long long {
            if (limit < 0) return 0;
            if (limit == 0) return (ones == 0 ? 1LL : 0LL);
            if (ones < 0) return 0;

            int L = 0;
            while ((1LL << L) <= limit && L < 62) L++;
            // L is number of bits needed (positions 0..L-1)

            long long ans = 0;
            int used = 0;
            for (int pos = L - 1; pos >= 0; --pos) {
                if (limit & (1LL << pos)) {
                    int need = ones - used;
                    if (need >= 0 && need <= pos) ans += C[pos][need];
                    used++;
                    if (used > ones) break;
                }
            }
            if (used == ones) ans += 1; // include limit itself
            return ans;
        };

        long long ans = 0;
        for (int m = 1; m <= MAXB; m++) {
            if (depth[m] == k - 1) {
                ans += countLEQ(n, m);
            }
        }

        // Exclude x=1 when k=1 (it has depth 0, but popcount=1 would count it)
        if (k == 1 && n >= 1) ans -= 1;

        return ans;
    }
};
// @lc code=end
