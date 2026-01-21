#
# @lc app=leetcode id=3486 lang=cpp
#
# [3486] Longest Special Path II
#
# @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> graph(n);
        
        for (auto& e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }
        
        vector<vector<pair<int, int>>> children(n);
        buildTree(0, -1, graph, children);
        
        int maxLength = 0;
        int minNodes = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            unordered_map<int, int> freq;
            explorePaths(i, children, nums, freq, 0, false, 1, maxLength, minNodes);
        }
        
        return {maxLength, minNodes};
    }
    
private:
    void buildTree(int node, int parent, 
                   vector<vector<pair<int, int>>>& graph,
                   vector<vector<pair<int, int>>>& children) {
        for (auto [neighbor, length] : graph[node]) {
            if (neighbor != parent) {
                children[node].push_back({neighbor, length});
                buildTree(neighbor, node, graph, children);
            }
        }
    }
    
    void explorePaths(int node, vector<vector<pair<int, int>>>& children,
                     vector<int>& nums, unordered_map<int, int>& freq,
                     int length, bool hasDup, int nodeCount,
                     int& maxLen, int& minNodes) {
        
        int val = nums[node];
        freq[val]++;
        
        bool newHasDup = hasDup;
        bool valid = true;
        
        if (freq[val] == 2) {
            if (hasDup) {
                valid = false;
            } else {
                newHasDup = true;
            }
        } else if (freq[val] > 2) {
            valid = false;
        }
        
        if (valid) {
            if (nodeCount >= 2) {
                if (length > maxLen) {
                    maxLen = length;
                    minNodes = nodeCount;
                } else if (length == maxLen) {
                    minNodes = min(minNodes, nodeCount);
                }
            }
            
            for (auto [child, edgeLen] : children[node]) {
                explorePaths(child, children, nums, freq, length + edgeLen,
                           newHasDup, nodeCount + 1, maxLen, minNodes);
            }
        }
        
        freq[val]--;
        if (freq[val] == 0) {
            freq.erase(val);
        }
    }
};
# @lc code=end