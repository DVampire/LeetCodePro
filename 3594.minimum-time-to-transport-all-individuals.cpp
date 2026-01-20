#
# @lc app=leetcode id=3594 lang=cpp
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        // Sort time to allow greedy selection of "riders"
        sort(time.begin(), time.end());
        
        // dist[mask][stage][boat]
        // mask: bitmask representing people currently at the base camp
        // stage: current environmental stage index (0 to m-1)
        // boat: 0 if boat is at base camp, 1 if boat is at destination
        // Initialize with infinity
        vector<vector<vector<double>>> dist(1 << n, vector<vector<double>>(m, vector<double>(2, 1e18)));
        
        // Priority Queue stores: {current_time, mask, stage, boat}
        using State = tuple<double, int, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;
        
        int start_mask = (1 << n) - 1; // All n individuals are at base camp
        dist[start_mask][0][0] = 0;
        pq.push({0, start_mask, 0, 0});
        
        while (!pq.empty()) {
            auto [d, mask, stage, boat] = pq.top();
            pq.pop();
            
            // If we found a shorter path to this state already, skip
            if (d > dist[mask][stage][boat]) continue;
            
            // If mask is 0, everyone is at the destination. We are done.
            if (mask == 0) return d;
            
            if (boat == 0) { // Boat is at Base Camp
                // Identify indices of people currently at base
                vector<int> at_base;
                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1) at_base.push_back(i);
                }
                
                // Try every person at base as the "driver" (the one with max time in the group)
                // Since 'time' is sorted, indices in 'at_base' are also sorted by time.
                for (int i = 0; i < at_base.size(); ++i) {
                    int driver = at_base[i]; // The person determining the trip time
                    
                    // We can bring up to k-1 other people.
                    // To be optimal, we should bring the fastest available people to help with potential returns.
                    // The available people strictly faster than or equal to the driver are at_base[0]...at_base[i-1].
                    // We take min(k-1, i) of them.
                    int riders_count = min((int)k - 1, i);
                    
                    int next_mask = mask;
                    next_mask ^= (1 << driver); // Remove driver from base
                    for (int r = 0; r < riders_count; ++r) {
                        next_mask ^= (1 << at_base[r]); // Remove riders from base
                    }
                    
                    double trip_time = (double)time[driver] * mul[stage];
                    double next_time = d + trip_time;
                    int next_stage = (stage + (int)floor(trip_time)) % m;
                    
                    if (next_time < dist[next_mask][next_stage][1]) {
                        dist[next_mask][next_stage][1] = next_time;
                        pq.push({next_time, next_mask, next_stage, 1});
                    }
                }
            } else { // Boat is at Destination
                // We must return one person to base to bring the boat back.
                // People at destination are those NOT in mask.
                for (int i = 0; i < n; ++i) {
                    if (!((mask >> i) & 1)) { // Person i is at destination
                        double trip_time = (double)time[i] * mul[stage];
                        double next_time = d + trip_time;
                        int next_stage = (stage + (int)floor(trip_time)) % m;
                        int next_mask = mask | (1 << i); // Person i is back at base
                        
                        if (next_time < dist[next_mask][next_stage][0]) {
                            dist[next_mask][next_stage][0] = next_time;
                            pq.push({next_time, next_mask, next_stage, 0});
                        }
                    }
                }
            }
        }
        
        return -1.0;
    }
};
# @lc code=end