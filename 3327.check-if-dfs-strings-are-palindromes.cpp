#
# @lc app=leetcode id=3327 lang=cpp
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution {
public:
    vector<int> tin, tout;
    string dfsStr;
    int timer;
    vector<vector<int>> adj;

    // Hashing parameters
    using ll = long long;
    const ll M1 = 1e9 + 7;
    const ll B1 = 31;
    const ll M2 = 1e9 + 9;
    const ll B2 = 37;

    vector<ll> pow1, pow2;
    vector<ll> h1, h2;       // Forward hashes
    vector<ll> rh1, rh2;     // Reverse hashes

    void dfs(int u, const string& s) {
        tin[u] = timer;
        for (int v : adj[u]) {
            dfs(v, s);
        }
        dfsStr += s[u];
        tout[u] = timer;
        timer++;
    }

    void buildHashes(int n) {
        pow1.resize(n + 1);
        pow2.resize(n + 1);
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        rh1.resize(n + 1, 0);
        rh2.resize(n + 1, 0);

        pow1[0] = 1; pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow1[i] = (pow1[i - 1] * B1) % M1;
            pow2[i] = (pow2[i - 1] * B2) % M2;
        }

        // Forward hash for dfsStr
        for (int i = 0; i < n; ++i) {
            h1[i + 1] = (h1[i] * B1 + (dfsStr[i] - 'a' + 1)) % M1;
            h2[i + 1] = (h2[i] * B2 + (dfsStr[i] - 'a' + 1)) % M2;
        }

        // Reverse hash for dfsStr (effectively hashing reversed string)
        // We can compute hash of reverse(dfsStr) or just compute hashes from right to left
        // Let's compute prefix hashes of the reversed string `revStr`
        string revStr = dfsStr;
        reverse(revStr.begin(), revStr.end());
        
        for (int i = 0; i < n; ++i) {
            rh1[i + 1] = (rh1[i] * B1 + (revStr[i] - 'a' + 1)) % M1;
            rh2[i + 1] = (rh2[i] * B2 + (revStr[i] - 'a' + 1)) % M2;
        }
    }

    // Get hash of substring dfsStr[L...R] (0-indexed, inclusive)
    pair<ll, ll> getHash(int L, int R) {
        // Length is R - L + 1
        // Hash is h[R+1] - h[L] * B^(len)
        ll len = R - L + 1;
        ll v1 = (h1[R + 1] - h1[L] * pow1[len]) % M1;
        if (v1 < 0) v1 += M1;
        ll v2 = (h2[R + 1] - h2[L] * pow2[len]) % M2;
        if (v2 < 0) v2 += M2;
        return {v1, v2};
    }

    // Get hash of substring revStr[L...R]
    pair<ll, ll> getRevHash(int L, int R) {
        ll len = R - L + 1;
        ll v1 = (rh1[R + 1] - rh1[L] * pow1[len]) % M1;
        if (v1 < 0) v1 += M1;
        ll v2 = (rh2[R + 1] - rh2[L] * pow2[len]) % M2;
        if (v2 < 0) v2 += M2;
        return {v1, v2};
    }

    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        adj.resize(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        // Children must be visited in increasing order
        // Since we iterate 1 to n-1 and push, and indices are increasing, 
        // usually adjacency lists might not be sorted if input order varies, 
        // but here i is increasing. However, parent[i] is arbitrary.
        // We need to sort children for each node.
        for(int i=0; i<n; ++i) {
            sort(adj[i].begin(), adj[i].end());
        }

        tin.resize(n);
        tout.resize(n);
        timer = 0;
        dfsStr.reserve(n);
        
        dfs(0, s);

        buildHashes(n);

        vector<bool> ans(n);
        for (int i = 0; i < n; ++i) {
            // The substring corresponding to node i in dfsStr is from index tin[i] to tout[i]
            int L = tin[i];
            int R = tout[i];
            
            // We need to check if dfsStr[L...R] is a palindrome.
            // This is equivalent to checking if hash(dfsStr[L...R]) == hash(reverse(dfsStr[L...R]))
            // reverse(dfsStr[L...R]) corresponds to a substring in revStr.
            // dfsStr index i maps to revStr index n - 1 - i.
            // So dfsStr[L...R] reversed maps to revStr[n - 1 - R ... n - 1 - L].
            
            int rL = n - 1 - R;
            int rR = n - 1 - L;
            
            if (getHash(L, R) == getRevHash(rL, rR)) {
                ans[i] = true;
            } else {
                ans[i] = false;
            }
        }
        
        return ans;
    }
};
# @lc code=end