#
# @lc app=leetcode id=3548 lang=cpp
#
# [3548] Equal Sum Grid Partition II
#
# @lc code=start
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        for (int i = 0; i < m - 1; i++) {
            if (checkHorizontalCut(grid, i)) return true;
        }
        
        for (int j = 0; j < n - 1; j++) {
            if (checkVerticalCut(grid, j)) return true;
        }
        
        return false;
    }
    
private:
    bool checkHorizontalCut(vector<vector<int>>& grid, int cutRow) {
        int m = grid.size(), n = grid[0].size();
        long long topSum = 0, bottomSum = 0;
        
        for (int i = 0; i <= cutRow; i++)
            for (int j = 0; j < n; j++)
                topSum += grid[i][j];
        
        for (int i = cutRow + 1; i < m; i++)
            for (int j = 0; j < n; j++)
                bottomSum += grid[i][j];
        
        if (topSum == bottomSum) return true;
        
        if (topSum > bottomSum) {
            long long diff = topSum - bottomSum;
            for (int i = 0; i <= cutRow; i++)
                for (int j = 0; j < n; j++)
                    if (grid[i][j] == diff && isConnected(grid, 0, cutRow, 0, n - 1, i, j))
                        return true;
        }
        
        if (bottomSum > topSum) {
            long long diff = bottomSum - topSum;
            for (int i = cutRow + 1; i < m; i++)
                for (int j = 0; j < n; j++)
                    if (grid[i][j] == diff && isConnected(grid, cutRow + 1, m - 1, 0, n - 1, i, j))
                        return true;
        }
        
        return false;
    }
    
    bool checkVerticalCut(vector<vector<int>>& grid, int cutCol) {
        int m = grid.size(), n = grid[0].size();
        long long leftSum = 0, rightSum = 0;
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j <= cutCol; j++)
                leftSum += grid[i][j];
        
        for (int i = 0; i < m; i++)
            for (int j = cutCol + 1; j < n; j++)
                rightSum += grid[i][j];
        
        if (leftSum == rightSum) return true;
        
        if (leftSum > rightSum) {
            long long diff = leftSum - rightSum;
            for (int i = 0; i < m; i++)
                for (int j = 0; j <= cutCol; j++)
                    if (grid[i][j] == diff && isConnected(grid, 0, m - 1, 0, cutCol, i, j))
                        return true;
        }
        
        if (rightSum > leftSum) {
            long long diff = rightSum - leftSum;
            for (int i = 0; i < m; i++)
                for (int j = cutCol + 1; j < n; j++)
                    if (grid[i][j] == diff && isConnected(grid, 0, m - 1, cutCol + 1, n - 1, i, j))
                        return true;
        }
        
        return false;
    }
    
    bool isConnected(vector<vector<int>>& grid, int r1, int r2, int c1, int c2, int skipR, int skipC) {
        int totalCells = (r2 - r1 + 1) * (c2 - c1 + 1) - 1;
        if (totalCells <= 0) return false;
        
        int startR = -1, startC = -1;
        for (int i = r1; i <= r2 && startR == -1; i++)
            for (int j = c1; j <= c2; j++)
                if (i != skipR || j != skipC) {
                    startR = i; startC = j; break;
                }
        
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        queue<pair<int, int>> q;
        q.push({startR, startC});
        visited[startR][startC] = true;
        int count = 1;
        
        int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= r1 && nx <= r2 && ny >= c1 && ny <= c2 && 
                    !visited[nx][ny] && (nx != skipR || ny != skipC)) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                    count++;
                }
            }
        }
        
        return count == totalCells;
    }
};
# @lc code=end