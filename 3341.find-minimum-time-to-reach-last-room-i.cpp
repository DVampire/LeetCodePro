//
// @lc app=leetcode id=3341 lang=cpp
//
// [3341] Find Minimum Time to Reach Last Room I
//

// @lc code=start
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        
        dist[0][0] = 0;
        pq.push({0, 0, 0});
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        while (!pq.empty()) {
            auto [time, x, y] = pq.top();
            pq.pop();
            
            if (x == n - 1 && y == m - 1) {
                return time;
            }
            
            if (time > dist[x][y]) {
                continue;
            }
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int arrivalTime = max(time, moveTime[nx][ny]) + 1;
                    
                    if (arrivalTime < dist[nx][ny]) {
                        dist[nx][ny] = arrivalTime;
                        pq.push({arrivalTime, nx, ny});
                    }
                }
            }
        }
        
        return dist[n-1][m-1];
    }
};
// @lc code=end