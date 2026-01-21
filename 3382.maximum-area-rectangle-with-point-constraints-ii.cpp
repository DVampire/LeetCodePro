#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#
#include <bits/stdc++.h>
using namespace std;

# @lc code=start
class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;
        Fenwick(int n=0): n(n), bit(n+1, 0) {}
        void add(int i, int delta) {
            for (; i <= n; i += i & -i) bit[i] += delta;
        }
        int sumPrefix(int i) const {
            int s = 0;
            for (; i > 0; i -= i & -i) s += bit[i];
            return s;
        }
    };

    struct Rect {
        int x1, x2;
        int y1, y2;
    };

    struct Query {
        long long X;
        long long Y;
        int rid;
        int sign;
    };

public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = (int)xCoord.size();
        vector<pair<int,int>> pts;
        pts.reserve(n);
        for (int i = 0; i < n; i++) pts.push_back({xCoord[i], yCoord[i]});

        // Sort points by x then y for grouping by x.
        sort(pts.begin(), pts.end());

        // Compress y for Fenwick updates; queries will use upper_bound for <=Y.
        vector<int> allY;
        allY.reserve(n);
        for (auto &p : pts) allY.push_back(p.second);
        sort(allY.begin(), allY.end());
        allY.erase(unique(allY.begin(), allY.end()), allY.end());

        auto yIndexExact = [&](int y) -> int {
            return (int)(lower_bound(allY.begin(), allY.end(), y) - allY.begin()) + 1; // 1-based
        };
        auto yIndexLeq = [&](long long y) -> int {
            // number of compressed y values <= y
            return (int)(upper_bound(allY.begin(), allY.end(), y) - allY.begin());
        };

        // Step 1/2: Generate rectangle candidates via consecutive y-pairs in each x-column.
        unordered_map<long long, int> lastX;
        lastX.reserve((size_t)n * 2);
        lastX.max_load_factor(0.7f);

        vector<Rect> rects;
        rects.reserve(n);

        int i = 0;
        while (i < n) {
            int x = pts[i].first;
            int j = i;
            // Because pts is sorted by (x,y), y's in this group are already sorted.
            // We'll just iterate consecutive pairs directly.
            while (j < n && pts[j].first == x) j++;

            for (int k = i; k + 1 < j; k++) {
                int y1 = pts[k].second;
                int y2 = pts[k+1].second;
                // key: pack (y1,y2) into 64-bit
                long long key = ( (long long)y1 << 32 ) | (unsigned int)y2;
                auto it = lastX.find(key);
                if (it != lastX.end()) {
                    rects.push_back(Rect{it->second, x, y1, y2});
                    it->second = x;
                } else {
                    lastX.emplace(key, x);
                }
            }
            i = j;
        }

        if (rects.empty()) return -1;

        // Step 3: Offline rectangle counting via sweep on x + Fenwick on y.
        vector<Query> queries;
        queries.reserve(rects.size() * 4);
        for (int rid = 0; rid < (int)rects.size(); rid++) {
            const auto &r = rects[rid];
            long long x1m = (long long)r.x1 - 1;
            long long y1m = (long long)r.y1 - 1;
            queries.push_back(Query{(long long)r.x2, (long long)r.y2, rid, +1});
            queries.push_back(Query{x1m,            (long long)r.y2, rid, -1});
            queries.push_back(Query{(long long)r.x2, y1m,            rid, -1});
            queries.push_back(Query{x1m,            y1m,            rid, +1});
        }

        sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
            if (a.X != b.X) return a.X < b.X;
            return a.Y < b.Y;
        });

        Fenwick fw((int)allY.size());
        vector<int> rectCount(rects.size(), 0);

        int p = 0;
        for (const auto &q : queries) {
            while (p < n && (long long)pts[p].first <= q.X) {
                fw.add(yIndexExact(pts[p].second), 1);
                p++;
            }
            int yi = yIndexLeq(q.Y);
            int pref = (yi > 0) ? fw.sumPrefix(yi) : 0;
            rectCount[q.rid] += q.sign * pref;
        }

        // Step 4: Validate and maximize area.
        long long ans = -1;
        for (int rid = 0; rid < (int)rects.size(); rid++) {
            if (rectCount[rid] == 4) {
                const auto &r = rects[rid];
                long long area = (long long)(r.x2 - r.x1) * (long long)(r.y2 - r.y1);
                ans = max(ans, area);
            }
        }

        return ans;
    }
};
# @lc code=end
