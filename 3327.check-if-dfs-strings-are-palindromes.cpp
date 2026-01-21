//
// @lc app=leetcode id=3327 lang=cpp
//
// [3327] Check if DFS Strings Are Palindromes
//
// @lc code=start
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }
        
        // Sort children for each node
        for (int i = 0; i < n; i++) {
            sort(children[i].begin(), children[i].end());
        }
        
        // Iterative DFS to build the string and record intervals
        string dfsStr;
        dfsStr.reserve(n);
        vector<int> startIdx(n, -1), endIdx(n);
        vector<int> childIdx(n, 0);
        stack<int> stk;
        stk.push(0);
        
        while (!stk.empty()) {
            int x = stk.top();
            
            if (startIdx[x] == -1) {
                startIdx[x] = dfsStr.size();
            }
            
            if (childIdx[x] < (int)children[x].size()) {
                int y = children[x][childIdx[x]++];
                stk.push(y);
            } else {
                dfsStr += s[x];
                endIdx[x] = dfsStr.size() - 1;
                stk.pop();
            }
        }
        
        // Manacher's algorithm
        string t = "#";
        for (char c : dfsStr) {
            t += c;
            t += '#';
        }
        
        int m = t.size();
        vector<int> p(m);
        int center = 0, right = 0;
        
        for (int i = 0; i < m; i++) {
            if (i < right) {
                p[i] = min(right - i, p[2 * center - i]);
            }
            while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m && t[i - p[i] - 1] == t[i + p[i] + 1]) {
                p[i]++;
            }
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        
        // Check each interval
        vector<bool> answer(n);
        for (int i = 0; i < n; i++) {
            int l = startIdx[i], r = endIdx[i];
            int centerInT = l + r + 1;
            answer[i] = (p[centerInT] >= r - l);
        }
        
        return answer;
    }
};
// @lc code=end