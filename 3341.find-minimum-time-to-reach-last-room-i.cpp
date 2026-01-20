#
# @lc app=leetcode id=3341 lang=cpp
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        
        // Priority queue to store {time, row, col}, min-heap based on time
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        
        // Distance matrix to keep track of minimum time to reach each cell
        // Initialize with a large value
        vector<vector<int>> dist(n, vector<int>(m, 2e9));
        
        // Start at (0, 0) at time 0
        dist[0][0] = 0;
        pq.push({0, 0, 0});
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!pq.empty()) {
            auto [currTime, r, c] = pq.top();
            pq.pop();
            
            // If we reached the destination
            if (r == n - 1 && c == m - 1) {
                return currTime;
            }
            
            // If we found a shorter path to this cell already, skip
            if (currTime > dist[r][c]) {
                continue;
            }
            
            // Explore neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    // Calculate arrival time at neighbor
                    // We can leave current cell at 'currTime'.
                    // We arrive at neighbor 1 second later.
                    // However, we must wait until 'moveTime[nr][nc]' before we can enter.
                    // Actually, the logic is: we can leave (r,c) immediately upon arrival? 
                    // No, the problem says moveTime[i][j] is when the room *opens*.
                    // So we can only enter (nr, nc) at time `t` such that `t > moveTime[nr][nc]` is NOT the constraint.
                    // The constraint is: we can enter at time T if T >= moveTime[nr][nc] AND we came from adjacent.
                    // But travel takes 1 second.
                    // So if we are at (r,c) at currTime, we can start moving to (nr,nc).
                    // We arrive at (nr,nc) at currTime + 1.
                    // BUT we can only enter if currTime >= moveTime[nr][nc]??
                    // Let's re-read carefully: "moveTime[i][j] represents the minimum time... after which the room opens and can be moved to."
                    // This usually implies we can enter at max(currTime, moveTime[nr][nc]) + 1.
                    // Wait, if moveTime is 4, we can enter at t=4? No, "after which". Usually implies >=.
                    // Example 1: (0,0)->(1,0). moveTime[1][0]=4. 
                    // Current at (0,0) t=0. moveTime[0][0]=0.
                    // We move to (1,0). It takes 1 sec. Arrival candidate: 1.
                    // But (1,0) opens at 4. So we must wait at (0,0) until we can arrive at (1,0) >= 4?
                    // Actually, the standard interpretation for grid problems like this (like "Swim in Rising Water") is:
                    // To enter node `v` from `u`, time must be at least `moveTime[v]`.
                    // Since it takes 1 sec to travel, the earliest we can arrive is `max(currTime, moveTime[nr][nc]) + 1`.
                    
                    int waitTime = max(currTime, moveTime[nr][nc]);
                    int newTime = waitTime + 1;
                    
                    if (newTime < dist[nr][nc]) {
                        dist[nr][nc] = newTime;
                        pq.push({newTime, nr, nc});
                    }
                }
            }
        }
        
        return -1; // Should not reach here
    }
};
# @lc code=end