#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    static constexpr int MOD = 1000000007;

    // Divide non-negative decimal string s by small int b.
    // Returns {quotient_string, remainder}
    pair<string,int> divmodDecString(const string& s, int b) {
        long long carry = 0;
        string q;
        q.reserve(s.size());
        for (char c : s) {
            carry = carry * 10 + (c - '0');
            int digit = (int)(carry / b);
            carry %= b;
            if (!q.empty() || digit != 0) q.push_back(char('0' + digit));
        }
        if (q.empty()) q = "0";
        return {q, (int)carry};
    }

    vector<int> toBaseB(string x, int b) {
        if (x == "0") return {0};
        vector<int> rev;
        while (x != "0") {
            auto [q, rem] = divmodDecString(x, b);
            rev.push_back(rem);
            x = q;
        }
        reverse(rev.begin(), rev.end());
        return rev;
    }

    string decMinusOne(string s) {
        if (s == "0") return "-1";
        int i = (int)s.size() - 1;
        while (i >= 0 && s[i] == '0') {
            s[i] = '9';
            --i;
        }
        if (i < 0) return "-1";
        s[i]--;
        int p = 0;
        while (p + 1 < (int)s.size() && s[p] == '0') ++p;
        s = s.substr(p);
        if (s.empty()) return "0";
        return s;
    }

    int countUpTo(const string& xDec, int b) {
        if (xDec == "-1") return 0;
        vector<int> dig = toBaseB(xDec, b);
        int n = (int)dig.size();

        // memo[pos][prev][started][tight]
        vector<vector<vector<vector<int>>>> memo(
            n + 1,
            vector<vector<vector<int>>>(b, vector<vector<int>>(2, vector<int>(2, -1)))
        );

        function<int(int,int,int,int)> dfs = [&](int pos, int prev, int started, int tight) -> int {
            if (pos == n) return 1; // one number formed
            int &res = memo[pos][prev][started][tight];
            if (res != -1) return res;

            long long ans = 0;
            int lim = tight ? dig[pos] : (b - 1);
            for (int d = 0; d <= lim; ++d) {
                int ntight = (tight && d == lim);
                if (!started) {
                    if (d == 0) {
                        ans += dfs(pos + 1, 0, 0, ntight);
                    } else {
                        ans += dfs(pos + 1, d, 1, ntight);
                    }
                } else {
                    if (d >= prev) {
                        ans += dfs(pos + 1, d, 1, ntight);
                    }
                }
                if (ans >= (1LL<<62)) ans %= MOD;
            }
            res = (int)(ans % MOD);
            return res;
        };

        return dfs(0, 0, 0, 1);
    }

    int countNumbers(string l, string r, int b) {
        int right = countUpTo(r, b);
        string lm1 = decMinusOne(l);
        int left = countUpTo(lm1, b);
        int ans = right - left;
        if (ans < 0) ans += MOD;
        return ans;
    }
};
// @lc code=end
