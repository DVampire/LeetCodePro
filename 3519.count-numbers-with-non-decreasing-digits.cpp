#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    int MOD = 1e9 + 7;
    int memo[405][11][2][2];

    vector<int> toBaseB(string n_str, int b) {
        vector<int> decimal;
        for (char c : n_str) decimal.push_back(c - '0');
        vector<int> res;
        while (!decimal.empty()) {
            long long rem = 0;
            vector<int> next_decimal;
            for (int d : decimal) {
                rem = rem * 10 + d;
                if (!next_decimal.empty() || rem / b > 0) {
                    next_decimal.push_back(rem / b);
                }
                rem %= b;
            }
            res.push_back((int)rem);
            decimal = next_decimal;
        }
        if (res.empty()) res.push_back(0);
        reverse(res.begin(), res.end());
        return res;
    }

    int solve(const vector<int>& digits, int idx, int last, bool tight, bool started, int b) {
        if (idx == digits.size()) return started ? 1 : 0;
        if (memo[idx][last][tight][started] != -1) return memo[idx][last][tight][started];

        long long ans = 0;
        int limit = tight ? digits[idx] : b - 1;

        if (!started) {
            ans = (ans + solve(digits, idx + 1, 0, tight && (0 == limit), false, b)) % MOD;
            for (int d = 1; d <= limit; ++d) {
                ans = (ans + solve(digits, idx + 1, d, tight && (d == limit), true, b)) % MOD;
            }
        } else {
            for (int d = last; d <= limit; ++d) {
                ans = (ans + solve(digits, idx + 1, d, tight && (d == limit), true, b)) % MOD;
            }
        }

        return memo[idx][last][tight][started] = (int)ans;
    }

    int countUpTo(string n_str, int b) {
        if (n_str == "-1") return 0;
        vector<int> digits = toBaseB(n_str, b);
        for (int i = 0; i < 405; ++i)
            for (int j = 0; j < 11; ++j)
                for (int k = 0; k < 2; ++k)
                    for (int l = 0; l < 2; ++l)
                        memo[i][j][k][l] = -1;
        return solve(digits, 0, 0, true, false, b);
    }

    string subtractOne(string n) {
        int i = n.size() - 1;
        while (i >= 0) {
            if (n[i] > '0') {
                n[i]--;
                break;
            } else {
                n[i] = '9';
                i--;
            }
        }
        size_t first = n.find_first_not_of('0');
        if (string::npos == first) return "0";
        return n.substr(first);
    }

public:
    int countNumbers(string l, string r, int b) {
        int countR = countUpTo(r, b);
        string lMinus1 = (l == "0") ? "-1" : subtractOne(l);
        int countL = (lMinus1 == "-1") ? 0 : countUpTo(lMinus1, b);
        return (countR - countL + MOD) % MOD;
    }
};