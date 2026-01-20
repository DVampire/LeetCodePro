#
# @lc app=leetcode id=3449 lang=cpp
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
class Solution {
public:
    bool check(long long target, const vector<int>& points, int m) {
        long long moves = 0;
        long long cur = 0;
        int n = points.size();
        
        // We iterate up to n-2. The last element n-1 is handled specially
        // or as a consequence of n-2.
        for (int i = 0; i < n - 1; ++i) {
            if (i == 0) {
                moves++; // Move -1 -> 0
                cur = 1;
            }
            
            long long req = (target + points[i] - 1) / points[i];
            long long needed = 0;
            if (cur < req) {
                needed = req - cur;
                moves += needed * 2;
            }
            
            if (moves > m) return false;
            
            // needed loops of i -> i+1 -> i contribute 'needed' visits to i+1
            long long visits_next = needed;
            
            // Strategy check: can we stop at i (after the loops) without moving to i+1?
            // This is only valid if i+1 is the last element (n-1) and it is already satisfied.
            if (i == n - 2) {
                long long req_last = (target + points[n-1] - 1) / points[n-1];
                if (visits_next >= req_last) {
                    return true;
                }
            }
            
            // Proceed to i+1
            moves++;
            cur = visits_next + 1; // visits from loops + the arrival move
            
            if (moves > m) return false;
        }
        
        // At this point, we are at n-1. 'cur' tracks visits to n-1.
        // We might need more visits for n-1. The only way is to oscillate (n-1) -> (n-2) -> (n-1).
        long long req = (target + points[n-1] - 1) / points[n-1];
        if (cur < req) {
            moves += (req - cur) * 2;
        }
        
        return moves <= m;
    }

    long long maxScore(vector<int>& points, int m) {
        long long low = 0, high = 200000000000000LL; // 2e14, safe upper bound
        long long ans = 0;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid, points, m)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
# @lc code=end