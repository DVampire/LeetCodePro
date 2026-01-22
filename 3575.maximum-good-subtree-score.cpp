#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    static constexpr long long MOD = 1000000007LL;
    long long answer;

    vector<long long> dfs(int u,
                         const vector<int>& vals,
                         const vector<vector<int>>& adj) {
        const int FULL_MASK = (1 << 10) - 1;
        vector<long long> dp(1024, LLONG_MIN);
        dp[0] = 0;

        bool valid_node = true;
        int num = vals[u];
        bool seen[10] = {false};
        int mask_u = 0;
        while (num > 0) {
            int d = num % 10;
            if (seen[d]) {
                valid_node = false;
                break;
            }
            seen[d] = true;
            mask_u |= (1 << d);
            num /= 10;
        }

        if (valid_node)
            dp[mask_u] = max(dp[mask_u], static_cast<long long>(vals[u]));

        for (int v : adj[u]) {
            auto child_dp = dfs(v, vals, adj);
            vector<long long> new_dp(1024, LLONG_MIN);

            vector<int> active_parent;
            for (int m = 0; m < 1024; ++m)
                if (dp[m] != LLONG_MIN)
                    active_parent.push_back(m);

            const int FULL = FULL_MASK;
            for (int m_parent : active_parent) {
                long long sparent = dp[m_parent];
                int complement = (~m_parent) & FULL;
                int submask = complement;
                while (true) {
                    long long schild = child_dp[submask];
                    if (schild != LLONG_MIN) {
                        long long total = sparent + schild;
                        int new_mask = m_parent | submask;
                        if (total > new_dp[new_mask])
                            new_dp[new_mask] = total;
                    }
                    if (submask == 0)
                        break;
                    submask = (submask - 1) & complement;
                }
            }
            dp.swap(new_dp);
        }

        long long best_sum_subtree = *max_element(dp.begin(), dp.end());
        answer += best_sum_subtree % MOD;
        answer %= MOD;

        return dp;
    }

    int goodSubtreeSum(vector<int>& vals_vec,
                       vector<int>& par_vec) {
        answer = 0LL;
        int n = vals_vec.size();
        vector<vector<int>> adj(n);
        
        for(int i = 0;i < n;i++) {
            int p = par_vec[i];
            if(p != -1)
                adj[p].push_back(i);
        }

        dfs(0,
             vals_vec,
             adj);

        return answer % MOD;
    }
};