#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
    long long memo[20][2][2][2];
    vector<int> digits;
    int L;

    long long solve(int idx, int carry, bool a_active, bool b_active) {
        if (idx == L) {
            // Both numbers must have finished their non-zero digits and no carry remains.
            return (carry == 0 && !a_active && !b_active) ? 1 : 0;
        }
        if (memo[idx][carry][a_active][b_active] != -1) {
            return memo[idx][carry][a_active][b_active];
        }

        long long count = 0;
        // Possible digits for a and b at the current index
        vector<int> a_choices = a_active ? vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9} : vector<int>{0};
        vector<int> b_choices = b_active ? vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9} : vector<int>{0};

        for (int ai : a_choices) {
            for (int bi : b_choices) {
                int sum = ai + bi + carry;
                if (sum % 10 == digits[idx]) {
                    int next_carry = sum / 10;
                    
                    // For the next position, each active number can stay active or end.
                    // If a number is already inactive, it must stay inactive.
                    for (int next_a = 0; next_a <= (a_active ? 1 : 0); ++next_a) {
                        for (int next_b = 0; next_b <= (b_active ? 1 : 0); ++next_b) {
                            count += solve(idx + 1, next_carry, next_a == 1, next_b == 1);
                        }
                    }
                }
            }
        }

        return memo[idx][carry][a_active][b_active] = count;
    }

public:
    long long countNoZeroPairs(long long n) {
        string s = to_string(n);
        digits.clear();
        for (int i = s.length() - 1; i >= 0; --i) {
            digits.push_back(s[i] - '0');
        }
        L = digits.size();
        memset(memo, -1, sizeof(memo));

        // Both a and b must be positive, no-zero integers.
        // This means at index 0, they MUST provide a digit from 1-9.
        return solve(0, 0, true, true);
    }
};