//
// @lc app=leetcode id=3435 lang=cpp
//
// [3435] Frequencies of Shortest Supersequences
//

// @lc code=start
class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        set<int> charSet;
        for (const auto& w : words) {
            charSet.insert(w[0] - 'a');
            charSet.insert(w[1] - 'a');
        }
        
        map<int, int> compress;
        vector<int> decompress;
        for (int c : charSet) {
            compress[c] = decompress.size();
            decompress.push_back(c);
        }
        int n = decompress.size();
        
        int must_double = 0;
        vector<vector<bool>> edge(n, vector<bool>(n, false));
        
        for (const auto& w : words) {
            int u = compress[w[0] - 'a'];
            int v = compress[w[1] - 'a'];
            if (u == v) {
                must_double |= (1 << u);
            } else {
                edge[u][v] = true;
            }
        }
        
        auto isAcyclic = [&](int mask) -> bool {
            vector<int> inDegree(n, 0);
            int nodeCount = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;
                nodeCount++;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;
                    if (edge[j][i]) {
                        inDegree[i]++;
                    }
                }
            }
            
            queue<int> q;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;
                if (inDegree[i] == 0) {
                    q.push(i);
                }
            }
            
            int processed = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                processed++;
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    if (edge[u][v]) {
                        inDegree[v]--;
                        if (inDegree[v] == 0) {
                            q.push(v);
                        }
                    }
                }
            }
            
            return processed == nodeCount;
        };
        
        int minSize = n + 1;
        vector<int> validMasks;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & must_double) != must_double) continue;
            
            if (isAcyclic(mask)) {
                int sz = __builtin_popcount(mask);
                if (sz < minSize) {
                    minSize = sz;
                    validMasks.clear();
                    validMasks.push_back(mask);
                } else if (sz == minSize) {
                    validMasks.push_back(mask);
                }
            }
        }
        
        set<vector<int>> resultSet;
        for (int mask : validMasks) {
            vector<int> freq(26, 0);
            for (int i = 0; i < n; i++) {
                int c = decompress[i];
                freq[c] = (mask & (1 << i)) ? 2 : 1;
            }
            resultSet.insert(freq);
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
};
// @lc code=end