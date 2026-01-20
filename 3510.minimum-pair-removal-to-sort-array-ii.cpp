#
# @lc app=leetcode id=3510 lang=cpp
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
#include <vector>
#include <queue>

using namespace std;

struct Pair {
    long long sum;
    int l, r;

    bool operator>(const Pair& other) const {
        if (sum != other.sum) return sum > other.sum;
        return l > other.l;
    }
};

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        vector<long long> val(n);
        vector<int> L(n, -1), R(n, -1);
        vector<bool> deleted(n, false);
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        for (int i = 0; i < n; ++i) {
            val[i] = nums[i];
            if (i > 0) L[i] = i - 1;
            if (i < n - 1) R[i] = i + 1;
        }

        auto check_v = [&](int left, int right) {
            if (left == -1 || right == -1) return 0;
            return val[left] > val[right] ? 1 : 0;
        };

        int violations = 0;
        for (int i = 0; i < n - 1; ++i) {
            violations += check_v(i, i + 1);
            pq.push({val[i] + val[i + 1], i, i + 1});
        }

        int ops = 0;
        while (violations > 0 && !pq.empty()) {
            Pair top = pq.top();
            pq.pop();

            int i = top.l;
            int j = top.r;

            // Validity check: nodes must exist, be adjacent, and sum must match
            if (deleted[i] || deleted[j] || R[i] != j || (val[i] + val[j] != top.sum)) {
                continue;
            }

            // Merge pair (i, j) into node i
            int prev = L[i];
            int next = R[j];

            violations -= check_v(prev, i);
            violations -= check_v(i, j);
            violations -= check_v(j, next);

            val[i] += val[j];
            deleted[j] = true;
            R[i] = next;
            if (next != -1) L[next] = i;

            violations += check_v(prev, i);
            violations += check_v(i, next);

            if (prev != -1) {
                pq.push({val[prev] + val[i], prev, i});
            }
            if (next != -1) {
                pq.push({val[i] + val[next], i, next});
            }

            ops++;
        }

        return ops;
    }
};
# @lc code=end