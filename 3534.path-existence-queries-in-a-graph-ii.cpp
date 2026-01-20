#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Step 1: Get sorted unique values
        vector<int> S = nums;
        sort(S.begin(), S.end());
        S.erase(unique(S.begin(), S.end()), S.end());
        int k = S.size();

        // Step 2: Identify components and build the first level of sparse table
        vector<int> comp(k, 0);
        vector<vector<int>> up(k, vector<int>(18));
        
        for (int i = 0; i < k; ++i) {
            if (i > 0) {
                comp[i] = (S[i] - S[i - 1] <= maxDiff) ? comp[i - 1] : comp[i - 1] + 1;
            }
            // up[i][0] is the index of the largest value S[j] such that S[j] <= S[i] + maxDiff
            auto it = upper_bound(S.begin(), S.end(), S[i] + maxDiff);
            up[i][0] = distance(S.begin(), it) - 1;
        }

        // Step 3: Build the rest of the sparse table (binary lifting)
        for (int j = 1; j < 18; ++j) {
            for (int i = 0; i < k; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        // Step 4: Process queries
        vector<int> results;
        results.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                results.push_back(0);
                continue;
            }
            if (nums[u] == nums[v]) {
                results.push_back(1);
                continue;
            }

            int val_u = nums[u], val_v = nums[v];
            int idx_u = lower_bound(S.begin(), S.end(), val_u) - S.begin();
            int idx_v = lower_bound(S.begin(), S.end(), val_v) - S.begin();

            if (idx_u > idx_v) swap(idx_u, idx_v);

            // Check if they are in the same component
            if (comp[idx_u] != comp[idx_v]) {
                results.push_back(-1);
            } else {
                // Use binary lifting to find the minimum steps
                int steps = 0;
                int curr = idx_u;
                for (int j = 17; j >= 0; --j) {
                    if (up[curr][j] < idx_v) {
                        curr = up[curr][j];
                        steps += (1 << j);
                    }
                }
                results.push_back(steps + 1);
            }
        }

        return results;
    }
};