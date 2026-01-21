#
# @lc app=leetcode id=3327 lang=cpp
#
# [3327] Check if DFS Strings Are Palindromes
#
# @lc code=start
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        
        // Build adjacency list
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }
        
        // Sort children for each node
        for (auto& child_list : children) {
            sort(child_list.begin(), child_list.end());
        }
        
        // Build global DFS string and track positions
        string dfsStr;
        vector<int> start(n), end(n);
        
        function<void(int)> dfs = [&](int x) {
            start[x] = dfsStr.size();
            for (int child : children[x]) {
                dfs(child);
            }
            dfsStr += s[x];
            end[x] = dfsStr.size() - 1;
        };
        
        dfs(0);
        
        int m = dfsStr.size();
        
        // Use polynomial rolling hash with two modulos
        const long long MOD1 = 1e9 + 7;
        const long long MOD2 = 1e9 + 9;
        const long long BASE = 31;
        
        vector<long long> hash1(m + 1, 0), hash2(m + 1, 0);
        vector<long long> pow1(m + 1), pow2(m + 1);
        pow1[0] = pow2[0] = 1;
        
        // Build forward hash
        for (int i = 0; i < m; i++) {
            hash1[i + 1] = (hash1[i] * BASE + (dfsStr[i] - 'a' + 1)) % MOD1;
            hash2[i + 1] = (hash2[i] * BASE + (dfsStr[i] - 'a' + 1)) % MOD2;
            pow1[i + 1] = (pow1[i] * BASE) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE) % MOD2;
        }
        
        // Build reverse hash
        string revStr(dfsStr.rbegin(), dfsStr.rend());
        vector<long long> revHash1(m + 1, 0), revHash2(m + 1, 0);
        
        for (int i = 0; i < m; i++) {
            revHash1[i + 1] = (revHash1[i] * BASE + (revStr[i] - 'a' + 1)) % MOD1;
            revHash2[i + 1] = (revHash2[i] * BASE + (revStr[i] - 'a' + 1)) % MOD2;
        }
        
        vector<bool> answer(n);
        for (int i = 0; i < n; i++) {
            int left = start[i];
            int right = end[i];
            int len = right - left + 1;
            
            // Hash of substring [left, right]
            long long fHash1 = (hash1[right + 1] - (hash1[left] * pow1[len]) % MOD1 + MOD1) % MOD1;
            long long fHash2 = (hash2[right + 1] - (hash2[left] * pow2[len]) % MOD2 + MOD2) % MOD2;
            
            // Corresponding positions in reversed string
            int revLeft = m - 1 - right;
            int revRight = m - 1 - left;
            
            // Hash of reversed substring
            long long rHash1 = (revHash1[revRight + 1] - (revHash1[revLeft] * pow1[len]) % MOD1 + MOD1) % MOD1;
            long long rHash2 = (revHash2[revRight + 1] - (revHash2[revLeft] * pow2[len]) % MOD2 + MOD2) % MOD2;
            
            answer[i] = (fHash1 == rHash1 && fHash2 == rHash2);
        }
        
        return answer;
    }
};
# @lc code=end