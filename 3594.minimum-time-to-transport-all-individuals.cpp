//
// @lc app=leetcode id=3594 lang=cpp
//
// [3594] Minimum Time to Transport All Individuals
//

// @lc code=start
class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        if (n > 1 && k == 1) return -1.0;
        
        int full_mask = (1 << n) - 1;
        
        // Precompute max time for each subset
        vector<int> max_time(1 << n, 0);
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    max_time[mask] = max(max_time[mask], time[i]);
                }
            }
        }
        
        // Precompute valid subsets (size 1 to k)
        vector<int> valid_subsets;
        for (int mask = 1; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) <= k) {
                valid_subsets.push_back(mask);
            }
        }
        
        auto idx = [&](int mask, int stage, int boat_pos) {
            return mask * m * 2 + stage * 2 + boat_pos;
        };
        
        vector<double> dist((1 << n) * m * 2, 1e18);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        
        dist[idx(0, 0, 0)] = 0;
        pq.push({0.0, idx(0, 0, 0)});
        
        while (!pq.empty()) {
            auto [d, state] = pq.top();
            pq.pop();
            
            if (d > dist[state]) continue;
            
            int mask = state / (m * 2);
            int stage = (state / 2) % m;
            int boat_pos = state % 2;
            
            if (mask == full_mask && boat_pos == 1) {
                return d;
            }
            
            if (boat_pos == 0) {
                // Boat at base camp - send people to destination
                int at_base = full_mask ^ mask;
                for (int subset : valid_subsets) {
                    if ((subset & at_base) == subset) {
                        double crossing_time = max_time[subset] * mul[stage];
                        int advance = (int)floor(crossing_time) % m;
                        int new_stage = (stage + advance) % m;
                        int new_mask = mask | subset;
                        int new_state = idx(new_mask, new_stage, 1);
                        double new_dist = d + crossing_time;
                        if (new_dist < dist[new_state]) {
                            dist[new_state] = new_dist;
                            pq.push({new_dist, new_state});
                        }
                    }
                }
            } else {
                // Boat at destination - send one person back
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        double return_time = time[i] * mul[stage];
                        int advance = (int)floor(return_time) % m;
                        int new_stage = (stage + advance) % m;
                        int new_mask = mask ^ (1 << i);
                        int new_state = idx(new_mask, new_stage, 0);
                        double new_dist = d + return_time;
                        if (new_dist < dist[new_state]) {
                            dist[new_state] = new_dist;
                            pq.push({new_dist, new_state});
                        }
                    }
                }
            }
        }
        
        return -1.0;
    }
};
// @lc code=end