#
# @lc app=leetcode id=3382 lang=cpp
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        
        // Compress y-coordinates
        vector<int> sortedY = yCoord;
        sort(sortedY.begin(), sortedY.end());
        sortedY.erase(unique(sortedY.begin(), sortedY.end()), sortedY.end());
        int m = sortedY.size();
        
        auto compressY = [&](int y) -> int {
            return lower_bound(sortedY.begin(), sortedY.end(), y) - sortedY.begin();
        };
        
        // Group points by x-coordinate
        map<int, vector<int>> pointsByX;
        for (int i = 0; i < n; i++) {
            pointsByX[xCoord[i]].push_back(compressY(yCoord[i]));
        }
        
        // Segment tree for range max query
        vector<int> tree(4 * m + 4, -1);
        
        function<void(int, int, int, int, int)> update = [&](int node, int start, int end, int idx, int val) {
            if (start == end) {
                tree[node] = val;
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid) update(2*node, start, mid, idx, val);
            else update(2*node+1, mid+1, end, idx, val);
            tree[node] = max(tree[2*node], tree[2*node+1]);
        };
        
        function<int(int, int, int, int, int)> query = [&](int node, int start, int end, int l, int r) -> int {
            if (l > r || r < start || end < l) return -1;
            if (l <= start && end <= r) return tree[node];
            int mid = (start + end) / 2;
            return max(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
        };
        
        long long maxArea = -1;
        
        for (auto& [x, ys] : pointsByX) {
            sort(ys.begin(), ys.end());
            
            // Check all adjacent pairs
            for (int i = 0; i + 1 < (int)ys.size(); i++) {
                int y1 = ys[i], y2 = ys[i + 1];
                int lastX1 = query(1, 0, m - 1, y1, y1);
                int lastX2 = query(1, 0, m - 1, y2, y2);
                
                if (lastX1 >= 0 && lastX1 == lastX2) {
                    int maxBetween = query(1, 0, m - 1, y1 + 1, y2 - 1);
                    if (maxBetween < lastX1) {
                        long long area = (long long)(x - lastX1) * (sortedY[y2] - sortedY[y1]);
                        maxArea = max(maxArea, area);
                    }
                }
            }
            
            // Update segment tree
            for (int y : ys) {
                update(1, 0, m - 1, y, x);
            }
        }
        
        return maxArea;
    }
};
# @lc code=end