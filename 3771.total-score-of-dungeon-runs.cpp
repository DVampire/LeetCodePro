#
# @lc app=leetcode id=3771 lang=cpp
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    // Fenwick Tree (Binary Indexed Tree) implementation
    struct FenwickTree {
        int size;
        vector<int> tree;

        FenwickTree(int n) : size(n), tree(n + 1, 0) {}

        void add(int index, int delta) {
            for (; index <= size; index += index & -index) {
                tree[index] += delta;
            }
        }

        int query(int index) {
            int sum = 0;
            for (; index > 0; index -= index & -index) {
                sum += tree[index];
            }
            return sum;
        }
    };

    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size();
        
        // S[i] is the prefix sum of damages up to index i-1 (0-based)
        // S[0] = 0
        // S[1] = damage[0]
        // ...
        // S[i] = damage[0] + ... + damage[i-1]
        vector<long long> S(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            S[i + 1] = S[i] + damage[i];
        }

        // We need to count for each k (0 to n-1), how many j <= k satisfy:
        // S[j] >= requirement[k] - hp + S[k+1]
        // Let's call the RHS target_val[k]
        
        vector<long long> target_val(n);
        for (int k = 0; k < n; ++k) {
            target_val[k] = (long long)requirement[k] - hp + S[k + 1];
        }

        // Coordinate Compression
        // We need to discretize values from S (0 to n-1, note S[n] is never a start point's prefix) 
        // and target_val.
        // Actually, we insert S[0], then query target_val[0].
        // Then insert S[1], query target_val[1], etc.
        // So we need to discretize S[0...n-1] and all target_val.

        vector<long long> values;
        values.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            values.push_back(S[i]);
            values.push_back(target_val[i]);
        }

        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        auto get_rank = [&](long long val) -> int {
            return lower_bound(values.begin(), values.end(), val) - values.begin() + 1;
        };

        int m = values.size();
        FenwickTree ft(m);
        long long total_score = 0;
        int count_inserted = 0;

        for (int k = 0; k < n; ++k) {
            // Insert S[k] (representing starting just before room k+1, i.e., start index j=k+1 in 1-based)
            // Wait, let's trace indices carefully.
            // Outer loop sum k=1 to n (rooms). Inner sum j=1 to k (start rooms).
            // Condition: S[j-1] >= requirement[k-1] - hp + S[k]
            // My code k goes 0 to n-1. Corresponds to room k+1.
            // Inner j goes 0 to k. Corresponds to start room j+1.
            // Insert S[k] means we add the possibility of starting at room k+1.
            // Query is for room k+1. We need to check all start points 1..k+1.
            // So we insert S[k] *before* querying for room k.
            
            // Step 1: Add S[k] to the pool of start damage offsets.
            int rank_s = get_rank(S[k]);
            ft.add(rank_s, 1);
            count_inserted++;

            // Step 2: Query how many satisfy condition for current room k.
            int rank_t = get_rank(target_val[k]);
            // We want count of values >= target_val[k]
            // This is total_inserted - count(< target_val[k])
            // count(< target_val[k]) is query(rank_t - 1)
            int valid_starts = count_inserted - ft.query(rank_t - 1);
            total_score += valid_starts;
        }

        return total_score;
    }
};
# @lc code=end