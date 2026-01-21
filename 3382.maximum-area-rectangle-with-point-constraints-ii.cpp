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
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = xCoord[i], y1 = yCoord[i];
                int x2 = xCoord[j], y2 = yCoord[j];
                
                if (x1 == x2 || y1 == y2) continue;
                
                if (x1 > x2) swap(x1, x2);
                if (y1 > y2) swap(y1, y2);
                
                if (pointSet.find({x1, y2}) == pointSet.end() || 
                    pointSet.find({x2, y1}) == pointSet.end()) {
                    continue;
                }
                
                bool valid = true;
                for (int k = 0; k < n; k++) {
                    int x = xCoord[k], y = yCoord[k];
                    if ((x == x1 && y == y1) || (x == x1 && y == y2) ||
                        (x == x2 && y == y1) || (x == x2 && y == y2)) {
                        continue;
                    }
                    if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    long long area = (long long)(x2 - x1) * (y2 - y1);
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
};
# @lc code=end