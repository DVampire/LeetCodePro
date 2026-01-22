//
// @lc app=leetcode id=3785 lang=cpp
//
// [3785] Minimum Swaps to Avoid Forbidden Values
//
// @lc code=start
class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        
        vector<int> badIndices;
        for (int i = 0; i < n; i++) {
            if (nums[i] == forbidden[i]) {
                badIndices.push_back(i);
            }
        }
        
        int m = badIndices.size();
        if (m == 0) return 0;
        
        // Build frequency map for feasibility check
        map<int, int> valueCount;
        for (int v : nums) {
            valueCount[v]++;
        }
        
        // Feasibility check: for each bad index, must exist some value != forbidden[i]
        for (int idx : badIndices) {
            int forbiddenVal = forbidden[idx];
            if (valueCount.count(forbiddenVal) && valueCount[forbiddenVal] == n) {
                return -1;
            }
        }
        
        // Build bipartite graph for matching among bad indices
        // Edge from i to j means value at badIndices[j] can go to position badIndices[i]
        vector<vector<int>> adj(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i != j && nums[badIndices[j]] != forbidden[badIndices[i]]) {
                    adj[i].push_back(j);
                }
            }
        }
        
        // Maximum bipartite matching using Hungarian algorithm
        vector<int> matchRight(m, -1);
        int matched = 0;
        for (int i = 0; i < m; i++) {
            vector<bool> visited(m, false);
            if (augment(i, adj, matchRight, visited)) {
                matched++;
            }
        }
        
        if (matched == m) {
            // Perfect matching exists - build permutation and count cycles
            vector<int> perm(m);
            for (int j = 0; j < m; j++) {
                if (matchRight[j] != -1) {
                    perm[matchRight[j]] = j;
                }
            }
            
            int cycles = 0;
            vector<bool> visited(m, false);
            for (int i = 0; i < m; i++) {
                if (!visited[i]) {
                    cycles++;
                    int curr = i;
                    while (!visited[curr]) {
                        visited[curr] = true;
                        curr = perm[curr];
                    }
                }
            }
            return m - cycles;
        }
        
        // Not all bad indices can be matched among themselves
        // Each bad index needs at least 1 swap
        return m;
    }
    
private:
    bool augment(int u, vector<vector<int>>& adj, vector<int>& matchRight, vector<bool>& visited) {
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                if (matchRight[v] == -1 || augment(matchRight[v], adj, matchRight, visited)) {
                    matchRight[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end