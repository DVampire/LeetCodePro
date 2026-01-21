#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#
# @lc code=start
class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        set<pair<int, int>> pointSet;
        
        for (int i = 0; i < n; i++) {
            pointSet.insert({xCoord[i], yCoord[i]});
        }
        
        long long maxArea = -1;
        
        // Try all pairs of points as potential diagonal corners
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = xCoord[i], y1 = yCoord[i];
                int x2 = xCoord[j], y2 = yCoord[j];
                
                // Must have different x and y to be diagonal
                if (x1 == x2 || y1 == y2) continue;
                
                int minX = min(x1, x2), maxX = max(x1, x2);
                int minY = min(y1, y2), maxY = max(y1, y2);
                
                // Check if other two corners exist
                if (pointSet.find({minX, maxY}) == pointSet.end() ||
                    pointSet.find({maxX, minY}) == pointSet.end()) {
                    continue;
                }
                
                // Check if any other point is inside or on boundary
                bool valid = true;
                for (int k = 0; k < n; k++) {
                    int x = xCoord[k], y = yCoord[k];
                    
                    // Skip the four corners
                    if ((x == minX && y == minY) || (x == minX && y == maxY) ||
                        (x == maxX && y == minY) || (x == maxX && y == maxY)) {
                        continue;
                    }
                    
                    // Check if inside or on boundary
                    if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    long long area = (long long)(maxX - minX) * (maxY - minY);
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
};
# @lc code=end