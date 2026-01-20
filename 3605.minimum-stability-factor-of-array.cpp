#
# @lc app=leetcode id=3605 lang=cpp
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
    struct Segment {
        int l, r;
        bool operator<(const Segment& other) const {
            if (l != other.l) return l < other.l;
            return r > other.r;
        }
    };

public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        vector<int> primes;
        vector<bool> is_prime(31623, true);
        for (int p = 2; p <= 31622; ++p) {
            if (is_prime[p]) {
                primes.push_back(p);
                for (long long i = (long long)p * p; i <= 31622; i += p)
                    is_prime[i] = false;
            }
        }

        map<int, vector<int>> prime_to_indices;
        for (int i = 0; i < n; ++i) {
            int val = nums[i];
            if (val < 2) continue;
            for (int p : primes) {
                if (p * p > val) break;
                if (val % p == 0) {
                    prime_to_indices[p].push_back(i);
                    while (val % p == 0) val /= p;
                }
            }
            if (val > 1) prime_to_indices[val].push_back(i);
        }

        vector<Segment> all_segments;
        for (auto const& [p, indices] : prime_to_indices) {
            int start = indices[0];
            for (int i = 1; i < indices.size(); ++i) {
                if (indices[i] != indices[i - 1] + 1) {
                    all_segments.push_back({start, indices[i - 1]});
                    start = indices[i];
                }
            }
            all_segments.push_back({start, indices.back()});
        }

        sort(all_segments.begin(), all_segments.end());
        vector<Segment> filtered;
        int max_r = -1;
        for (auto& seg : all_segments) {
            if (seg.r > max_r) {
                filtered.push_back(seg);
                max_r = seg.r;
            }
        }

        auto check = [&](int L) {
            if (L >= n) return true;
            long long count = 0;
            int curr_reach = -1;
            int active_s = -1, active_e = -1;

            for (auto& seg : filtered) {
                if (seg.r - seg.l + 1 > L) {
                    int s = seg.l;
                    int e = seg.r - L;
                    if (active_s == -1) {
                        active_s = s;
                        active_e = e;
                    } else if (s <= active_e) {
                        active_e = max(active_e, e);
                    } else {
                        int start = max(active_s, curr_reach);
                        if (start <= active_e) {
                            int num = (active_e - start) / (L + 1) + 1;
                            count += num;
                            curr_reach = start + num * (L + 1);
                        }
                        active_s = s;
                        active_e = e;
                    }
                }
            }
            if (active_s != -1) {
                int start = max(active_s, curr_reach);
                if (start <= active_e) {
                    count += (active_e - start) / (L + 1) + 1;
                }
            }
            return count <= maxC;
        };

        int left = 0, right = n, ans = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
# @lc code=end