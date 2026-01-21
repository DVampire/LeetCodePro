#include <bits/stdc++.h>
using namespace std;

# @lc code=start
class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        if (n > 1 && k == 1) return -1.0; // cannot make progress

        const int ALL = (1 << n) - 1;

        // Precompute all subsets with size 1..k
        vector<int> subsets;
        subsets.reserve(2000);
        for (int mask = 1; mask <= ALL; ++mask) {
            int pc = __builtin_popcount((unsigned)mask);
            if (pc >= 1 && pc <= k) subsets.push_back(mask);
        }

        // Precompute maxTime[mask]
        vector<int> maxTime(1 << n, 0);
        for (int mask = 1; mask <= ALL; ++mask) {
            int mx = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) mx = max(mx, time[i]);
            }
            maxTime[mask] = mx;
        }

        auto advanceStage = [&](long double dur) -> int {
            // small epsilon to avoid floating precision issues near integers
            long double fl = floorl(dur + 1e-12L);
            long long adv = (long long)fl;
            return (int)(adv % m);
        };

        auto idx = [&](int mask, int boat, int stage) -> int {
            return ((mask * 2 + boat) * m + stage);
        };

        int SZ = (1 << n) * 2 * m;
        const long double INF = 1e100L;
        vector<long double> dist(SZ, INF);

        struct Node {
            long double d;
            int id;
            bool operator>(const Node& other) const { return d > other.d; }
        };

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        int start = idx(0, 0, 0);
        dist[start] = 0;
        pq.push({0, start});

        long double ans = INF;

        while (!pq.empty()) {
            auto [d, idstate] = pq.top();
            pq.pop();
            if (d > dist[idstate] + 1e-12L) continue;
            if (d >= ans - 1e-12L) continue;

            int stage = idstate % m;
            int tmp = idstate / m;
            int boat = tmp % 2;
            int mask = tmp / 2;

            if (mask == ALL && boat == 1) {
                ans = min(ans, d);
                continue;
            }

            if (boat == 0) {
                int rem = ALL ^ mask;
                for (int sub : subsets) {
                    if ((sub & rem) != sub) continue;
                    long double dur = (long double)maxTime[sub] * (long double)mul[stage];
                    int ns = (stage + advanceStage(dur)) % m;
                    int nmask = mask | sub;
                    int nid = idx(nmask, 1, ns);
                    long double nd = d + dur;
                    if (nd + 1e-12L < dist[nid]) {
                        dist[nid] = nd;
                        pq.push({nd, nid});
                    }
                }
            } else {
                // boat at destination; if not all transported, someone must return
                if (mask == ALL) continue;
                for (int i = 0; i < n; ++i) {
                    if (!(mask & (1 << i))) continue;
                    long double dur = (long double)time[i] * (long double)mul[stage];
                    int ns = (stage + advanceStage(dur)) % m;
                    int nmask = mask ^ (1 << i);
                    int nid = idx(nmask, 0, ns);
                    long double nd = d + dur;
                    if (nd + 1e-12L < dist[nid]) {
                        dist[nid] = nd;
                        pq.push({nd, nid});
                    }
                }
            }
        }

        if (ans >= INF / 2) return -1.0;
        return (double)ans;
    }
};
# @lc code=end
