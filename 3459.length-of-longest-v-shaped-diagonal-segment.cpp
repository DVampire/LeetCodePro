#
# @lc app=leetcode id=3459 lang=cpp
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#
# @lc code=start
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxLen = 0;
        
        // Four diagonal directions: (dr, dc)
        int dr[] = {1, 1, -1, -1};
        int dc[] = {1, -1, -1, 1};
        
        // Clockwise 90-degree turn
        int clockwise[] = {1, 2, 3, 0};
        
        auto expectedValue = [](int i) {
            if (i == 0) return 1;
            return (i % 2 == 1) ? 2 : 0;
        };
        
        // Function to extend in a direction from a given position
        auto extend = [&](int r, int c, int dir, int startPos) {
            int count = 0;
            int pos = startPos;
            while (r >= 0 && r < n && c >= 0 && c < m && grid[r][c] == expectedValue(pos)) {
                count++;
                pos++;
                r += dr[dir];
                c += dc[dir];
            }
            return count;
        };
        
        // Try starting from each cell with value 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;
                
                // Try each starting direction
                for (int dir = 0; dir < 4; dir++) {
                    // First, try without turning
                    int len1 = extend(i, j, dir, 0);
                    maxLen = max(maxLen, len1);
                    
                    // Now try turning at each position along the path
                    int r = i, c = j, pos = 0;
                    while (r >= 0 && r < n && c >= 0 && c < m && grid[r][c] == expectedValue(pos)) {
                        // Current path length up to here (inclusive)
                        int currentLen = pos + 1;
                        
                        // Try making a clockwise turn from here
                        int newDir = clockwise[dir];
                        int nr = r + dr[newDir];
                        int nc = c + dc[newDir];
                        int len2 = extend(nr, nc, newDir, pos + 1);
                        maxLen = max(maxLen, currentLen + len2);
                        
                        // Move to next position
                        pos++;
                        r += dr[dir];
                        c += dc[dir];
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end