#
# @lc app=leetcode id=3488 lang=cpp
#
# [3488] Closest Equal Element Queries
#
# @lc code=start
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        unordered_map<int, vector<int>> valueToIndices;
        
        // Group indices by their values
        for (int i = 0; i < n; i++) {
            valueToIndices[nums[i]].push_back(i);
        }
        
        // Precompute minimum distances for each index
        vector<int> minDist(n, -1);
        
        for (auto& [val, indices] : valueToIndices) {
            int k = indices.size();
            if (k == 1) continue; // Only one occurrence, no other index with same value
            
            // Indices are already sorted since we iterate from 0 to n-1
            for (int j = 0; j < k; j++) {
                int curr = indices[j];
                int prev = indices[(j - 1 + k) % k];
                int next = indices[(j + 1) % k];
                
                // Distance to previous neighbor (circular distance)
                int directPrev = abs(curr - prev);
                int distPrev = min(directPrev, n - directPrev);
                
                // Distance to next neighbor (circular distance)
                int directNext = abs(next - curr);
                int distNext = min(directNext, n - directNext);
                
                minDist[curr] = min(distPrev, distNext);
            }
        }
        
        // Answer queries
        vector<int> answer;
        answer.reserve(queries.size());
        for (int q : queries) {
            answer.push_back(minDist[q]);
        }
        
        return answer;
    }
};
# @lc code=end