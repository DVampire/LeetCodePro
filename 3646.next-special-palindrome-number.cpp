#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    struct SetInfo {
        vector<int> digits;
        int oddDigit; // -1 if L is even
    };

    vector<SetInfo> validSets[46];

public:
    Solution() {
        for (int i = 1; i < (1 << 9); ++i) {
            int L = 0;
            int oddCount = 0;
            int oddDigit = -1;
            vector<int> digits;
            for (int j = 0; j < 9; ++j) {
                if ((i >> j) & 1) {
                    int d = j + 1;
                    L += d;
                    digits.push_back(d);
                    if (d % 2 != 0) {
                        oddCount++;
                        oddDigit = d;
                    }
                }
            }
            if (L % 2 == 0 && oddCount == 0) {
                validSets[L].push_back({digits, -1});
            } else if (L % 2 != 0 && oddCount == 1) {
                validSets[L].push_back({digits, oddDigit});
            }
        }
    }

    long long solveForSet(int L, const SetInfo& info, long long n) {
        string s_n = to_string(n);
        int H = L / 2;
        vector<int> counts(10, 0);
        for (int d : info.digits) {
            if (d == info.oddDigit) counts[d] = (d - 1) / 2;
            else counts[d] = d / 2;
        }

        if (L > s_n.length()) {
            string res = "";
            for (int d = 1; d <= 9; ++d) {
                for (int i = 0; i < counts[d]; ++i) res += (char)(d + '0');
            }
            string full = res;
            if (info.oddDigit != -1) full += (char)(info.oddDigit + '0');
            for (int i = H - 1; i >= 0; --i) full += res[i];
            if (full.length() > 19) return -1;
            try {
                unsigned long long val = stoull(full);
                return (val > (unsigned long long)LLONG_MAX) ? -1 : (long long)val;
            } catch (...) { return -1; }
        } else {
            long long minVal = -1;
            string current = "";
            auto backtrack = [&](auto self, int idx, bool isGreater) -> void {
                if (minVal != -1 && isGreater) return;
                if (idx == H) {
                    string full = current;
                    if (info.oddDigit != -1) full += (char)(info.oddDigit + '0');
                    for (int i = H - 1; i >= 0; --i) full += current[i];
                    unsigned long long val = stoull(full);
                    if (val > (unsigned long long)n) {
                        if (minVal == -1 || (long long)val < minVal) minVal = (long long)val;
                    }
                    return;
                }
                int start = isGreater ? 0 : (s_n[idx] - '0');
                for (int d = max(start, (idx == 0 ? 1 : 0)); d <= 9; ++d) {
                    if (counts[d] > 0) {
                        counts[d]--;
                        current.push_back(d + '0');
                        self(self, idx + 1, isGreater || (d > start));
                        current.pop_back();
                        counts[d]++;
                        if (minVal != -1 && (isGreater || d > start)) break;
                    }
                }
            };
            backtrack(backtrack, 0, false);
            return minVal;
        }
    }

    long long specialPalindrome(long long n) {
        string s_n = to_string(n);
        for (int L = s_n.length(); L <= 45; ++L) {
            long long minL = -1;
            for (const auto& info : validSets[L]) {
                long long val = solveForSet(L, info, n);
                if (val != -1) {
                    if (minL == -1 || val < minL) minL = val;
                }
            }
            if (minL != -1) return minL;
        }
        return -1;
    }
};