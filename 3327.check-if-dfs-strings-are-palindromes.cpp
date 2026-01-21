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
        
        // Sort children to visit in increasing order
        for (int i = 0; i < n; i++) {
            sort(children[i].begin(), children[i].end());
        }
        
        // Perform DFS from root to build global DFS string
        string dfsStr;
        vector<int> start(n), end(n);
        
        function<void(int)> dfs = [&](int x) {
            start[x] = dfsStr.size();
            for (int child : children[x]) {
                dfs(child);
            }
            dfsStr += s[x];
            end[x] = dfsStr.size();
        };
        
        dfs(0);
        
        // Polynomial hashing for palindrome checking
        int m = dfsStr.size();
        const long long MOD = 1e9 + 7;
        const long long BASE = 31;
        
        vector<long long> hashFwd(m + 1, 0);
        vector<long long> hashBwd(m + 1, 0);
        vector<long long> powBase(m + 1);
        powBase[0] = 1;
        
        for (int i = 0; i < m; i++) {
            powBase[i + 1] = (powBase[i] * BASE) % MOD;
            hashFwd[i + 1] = (hashFwd[i] * BASE + (dfsStr[i] - 'a' + 1)) % MOD;
        }
        
        for (int i = m - 1; i >= 0; i--) {
            hashBwd[i] = (hashBwd[i + 1] * BASE + (dfsStr[i] - 'a' + 1)) % MOD;
        }
        
        auto getHashFwd = [&](int l, int r) -> long long {
            long long h = (hashFwd[r] - hashFwd[l] * powBase[r - l]) % MOD;
            if (h < 0) h += MOD;
            return h;
        };
        
        auto getHashBwd = [&](int l, int r) -> long long {
            long long h = (hashBwd[l] - hashBwd[r] * powBase[r - l]) % MOD;
            if (h < 0) h += MOD;
            return h;
        };
        
        vector<bool> answer(n);
        for (int i = 0; i < n; i++) {
            answer[i] = (getHashFwd(start[i], end[i]) == getHashBwd(start[i], end[i]));
        }
        
        return answer;
    }
};
# @lc code=end