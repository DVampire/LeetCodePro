#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
    struct SegTreeMax {
        int n;
        vector<int> t;
        static constexpr int NEG = -1;
        SegTreeMax(int n=0){init(n);} 
        void init(int n_) {
            n = 1;
            while(n < n_) n <<= 1;
            t.assign(2*n, NEG);
        }
        void update(int pos, int val) {
            int p = pos + n;
            t[p] = val;
            for(p >>= 1; p; p >>= 1) t[p] = max(t[p<<1], t[p<<1|1]);
        }
        int query(int l, int r) { // inclusive
            if(l > r) return NEG;
            l += n; r += n;
            int res = NEG;
            while(l <= r) {
                if(l & 1) res = max(res, t[l++]);
                if(!(r & 1)) res = max(res, t[r--]);
                l >>= 1; r >>= 1;
            }
            return res;
        }
    };

public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int N = (int)xCoord.size();
        vector<int> ys = yCoord;
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int M = (int)ys.size();

        vector<pair<int,int>> pts;
        pts.reserve(N);
        for(int i = 0; i < N; i++) {
            int yi = (int)(lower_bound(ys.begin(), ys.end(), yCoord[i]) - ys.begin());
            pts.push_back({xCoord[i], yi});
        }
        sort(pts.begin(), pts.end(), [](const auto& a, const auto& b){
            if(a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });

        // lastSeen per compressed y
        vector<int> lastSeen(M, -1);
        SegTreeMax seg(M);

        // last x where an adjacent pair (y1,y2) appeared on the same column
        unordered_map<unsigned long long, int> lastPairX;
        lastPairX.reserve((size_t)N * 2);
        lastPairX.max_load_factor(0.7f);

        auto makeKey = [&](int yi, int yj) -> unsigned long long {
            uint32_t a = (uint32_t)ys[yi];
            uint32_t b = (uint32_t)ys[yj];
            return ( (unsigned long long)a << 32 ) | (unsigned long long)b;
        };

        long long ans = -1;
        int i = 0;
        while(i < N) {
            int x = pts[i].first;
            int j = i;
            vector<int> col;
            while(j < N && pts[j].first == x) {
                col.push_back(pts[j].second);
                j++;
            }

            // Evaluate candidates using state BEFORE updating this column into lastSeen/seg.
            for(int k = 0; k + 1 < (int)col.size(); k++) {
                int a = col[k];
                int b = col[k+1];
                if(a == b) continue;
                unsigned long long key = makeKey(a, b);

                auto it = lastPairX.find(key);
                if(it != lastPairX.end()) {
                    int x1 = it->second;
                    // Ensure no points on horizontal borders y=ys[a], ys[b] between x1 and x.
                    if(lastSeen[a] == x1 && lastSeen[b] == x1) {
                        int innerMax = seg.query(a+1, b-1);
                        if(innerMax <= x1) {
                            long long area = 1LL * (x - x1) * (ys[b] - ys[a]);
                            ans = max(ans, area);
                        }
                    }
                }
                // Update last occurrence of this adjacent pair to current x.
                lastPairX[key] = x;
            }

            // Now incorporate points at this x into lastSeen and seg.
            for(int yi : col) {
                lastSeen[yi] = x;
                seg.update(yi, x);
            }

            i = j;
        }

        return ans;
    }
};
// @lc code=end
