#
# @lc app=leetcode id=3534 lang=cpp
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Step 1: Identify unique values and sort them to build the "value graph"
        vector<int> uniq = nums;
        sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
        
        int m = uniq.size();
        
        // Map original value to its index in the unique sorted array
        // Since values are up to 10^5, we can use a direct map or binary search.
        // Given constraints, binary search (lower_bound) is fine.
        
        // Step 2: Precompute connected components
        // If uniq[i+1] - uniq[i] > maxDiff, there is a break.
        vector<int> component(m);
        int compId = 0;
        component[0] = 0;
        for (int i = 0; i < m - 1; ++i) {
            if ((long long)uniq[i+1] - uniq[i] > maxDiff) {
                compId++;
            }
            component[i+1] = compId;
        }
        
        // Step 3: Build Binary Lifting Table
        // jump[k][i] stores the index of the value reachable from uniq[i] with 2^k greedy steps
        // A greedy step from i goes to the largest index j such that uniq[j] <= uniq[i] + maxDiff
        
        int LOG = 0;
        while ((1 << (LOG + 1)) <= m) LOG++;
        
        vector<vector<int>> jump(LOG + 1, vector<int>(m));
        
        // Fill level 0
        int right = 0;
        for (int i = 0; i < m; ++i) {
            // Find largest reachable j. Since i increases, right is non-decreasing.
            // We want uniq[right] <= uniq[i] + maxDiff
            while (right + 1 < m && (long long)uniq[right + 1] - uniq[i] <= maxDiff) {
                right++;
            }
            jump[0][i] = right;
        }
        
        // Fill other levels
        for (int k = 1; k <= LOG; ++k) {
            for (int i = 0; i < m; ++i) {
                jump[k][i] = jump[k-1][jump[k-1][i]];
            }
        }
        
        vector<int> results;
        results.reserve(queries.size());
        
        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];
            
            if (u == v) {
                results.push_back(0);
                continue;
            }
            
            int val_u = nums[u];
            int val_v = nums[v];
            
            if (val_u == val_v) {
                results.push_back(1);
                continue;
            }
            
            // Find indices in uniq array
            int idx_u = lower_bound(uniq.begin(), uniq.end(), val_u) - uniq.begin();
            int idx_v = lower_bound(uniq.begin(), uniq.end(), val_v) - uniq.begin();
            
            // Ensure we go from smaller to larger
            if (idx_u > idx_v) swap(idx_u, idx_v);
            
            // Check connectivity
            if (component[idx_u] != component[idx_v]) {
                results.push_back(-1);
                continue;
            }
            
            // Calculate distance using binary lifting
            int steps = 0;
            int curr = idx_u;
            
            // While we cannot reach idx_v in one step (checked implicitly by lifting logic)
            // Actually, standard logic: try to jump as far as possible without passing or reaching idx_v?
            // No, the greedy property is: jump to the furthest possible node.
            // If jump[k][curr] < idx_v, it means even with 2^k steps we haven't reached or passed idx_v.
            // Wait, if jump[k][curr] >= idx_v, it means we *can* reach idx_v (or beyond) within 2^k steps.
            // We want to find the largest steps such that we are still < idx_v, then add 1.
            // Correct logic: Accumulate steps. If jump[k][curr] < idx_v, then we can take these 2^k steps
            // and we are still strictly to the left of idx_v. So we take them.
            
            for (int k = LOG; k >= 0; --k) {
                if (jump[k][curr] < idx_v) {
                    curr = jump[k][curr];
                    steps += (1 << k);
                }
            }
            
            // After the loop, curr is the furthest node reachable < idx_v.
            // The next step must reach or pass idx_v.
            results.push_back(steps + 1);
        }
        
        return results;
    }
};
# @lc code=end