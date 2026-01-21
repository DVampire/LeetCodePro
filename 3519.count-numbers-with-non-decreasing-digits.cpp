#
# @lc app=leetcode id=3519 lang=cpp
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countNumbers(string l, string r, int b) {
        const long long MOD = 1000000007LL;
        auto decrement = [](string num) -> string {
            int n = num.size();
            string res = num;
            int i = n - 1;
            while (i >= 0) {
                if (res[i] > '0') {
                    res[i]--;
                    break;
                } else {
                    res[i] = '9';
                    i--;
                }
            }
            if (i < 0) return "0";
            size_t startpos = res.find_first_not_of('0');
            if (startpos == string::npos) return "0";
            return res.substr(startpos);
        };
        auto to_baseb = [b](string num) -> vector<int> {
            vector<int> digs;
            if (num == "0") return {0};
            while (num != "0") {
                int rem = 0;
                string nextn;
                for (char ch : num) {
                    int digi = ch - '0';
                    int temp = rem * 10 + digi;
                    int q = temp / b;
                    rem = temp % b;
                    if (!nextn.empty() || q != 0) {
                        nextn += ('0' + q);
                    }
                }
                if (nextn.empty()) nextn = "0";
                digs.push_back(rem);
                num = nextn;
            }
            reverse(digs.begin(), digs.end());
            return digs;
        };
        auto count_up_to = [&](const string& S) -> long long {
            if (S == "0") return 0LL;
            vector<int> digits = to_baseb(S);
            int len_ = digits.size();
            int m_ = b - 1;
            const int MAXN = 400;
            vector<vector<long long>> comb(MAXN + 1, vector<long long>(10, 0LL));
            for (int i = 0; i <= MAXN; ++i) {
                comb[i][0] = 1;
                for (int j = 1; j <= min(i, 9); ++j) {
                    comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
                }
            }
            long long small = 0;
            int L = len_ - 1;
            if (L >= 0) {
                small = (comb[L + m_][m_] + MOD - 1) % MOD;
            }
            vector<vector<vector<long long>>> mem(len_ + 1, vector<vector<long long>>(10, vector<long long>(2, -1LL)));
            auto dfs = [&](auto&& self, int pos, int prevv, int tig) -> long long {
                if (pos == len_) return 1LL;
                long long& ans = mem[pos][prevv][tig];
                if (ans != -1LL) return ans;
                ans = 0LL;
                int up = tig ? digits[pos] : b - 1;
                int lo = (pos == 0 ? 1 : prevv);
                for (int d = lo; d <= up; ++d) {
                    int ntig = tig && (d == up);
                    ans = (ans + self(self, pos + 1, d, ntig)) % MOD;
                }
                return ans;
            };
            long long same_len = dfs(dfs, 0, 0, 1);
            return (small + same_len) % MOD;
        };
        string l1 = decrement(l);
        long long ans = (count_up_to(r) - count_up_to(l1) + MOD) % MOD;
        if (l == "0") ans = (ans + 1) % MOD;
        return (int)ans;
    }
};
# @lc code=end