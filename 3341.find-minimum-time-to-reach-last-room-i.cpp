#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

#
# @lc app=leetcode id=3341 lang=cpp
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        
        // dist[i][j] stores the minimum time to reach room (i, j)
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        
        // Min-heap for Dijkstra: {current_time, {row, col}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        
        // Starting at (0, 0) at t = 0
        dist[0][0] = 0;
        pq.push({0, {0, 0}});
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int r = pq.top().second.first;
            int c = pq.top().second.second;
            pq.pop();
            
            // If we already found a better path to this room, skip
            if (d > dist[r][c]) continue;
            
            // If we reached the target room, return the time
            if (r == n - 1 && c == m - 1) return d;
            
            // Explore adjacent rooms
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    // To move to room (nr, nc), we must wait until it opens at moveTime[nr][nc].
                    // The move itself takes 1 second.
                    int next_time = max(d, moveTime[nr][nc]) + 1;
                    
                    if (next_time < dist[nr][nc]) {
                        dist[nr][nc] = next_time;
                        pq.push({next_time, {nr, nc}});
                    }
                }
            }
        }
        
        return -1; // Should not be reached given constraints
    }
};
# @lc code=end