#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        
        vector<int> rem(n), quo(n);
        for (int i = 0; i < n; i++) {
            rem[i] = nums[i] % k;
            quo[i] = nums[i] / k;
        }
        
        vector<int> sortedQuo = quo;
        sort(sortedQuo.begin(), sortedQuo.end());
        sortedQuo.erase(unique(sortedQuo.begin(), sortedQuo.end()), sortedQuo.end());
        int m = sortedQuo.size();
        
        auto getIdx = [&](int v) -> int {
            return lower_bound(sortedQuo.begin(), sortedQuo.end(), v) - sortedQuo.begin() + 1;
        };
        
        vector<long long> countBIT(m + 2, 0), sumBIT(m + 2, 0);
        
        auto updateBIT = [&](vector<long long>& bit, int i, long long delta) {
            for (; i <= m + 1; i += i & (-i))
                bit[i] += delta;
        };
        
        auto queryBIT = [&](vector<long long>& bit, int i) -> long long {
            long long result = 0;
            for (; i > 0; i -= i & (-i))
                result += bit[i];
            return result;
        };
        
        int block = max(1, (int)sqrt(n));
        vector<int> order(q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            int ba = queries[a][0] / block, bb = queries[b][0] / block;
            if (ba != bb) return ba < bb;
            return (ba & 1) ? queries[a][1] > queries[b][1] : queries[a][1] < queries[b][1];
        });
        
        unordered_map<int, int> remCount;
        int numDistinctRem = 0;
        int curSize = 0;
        
        auto add = [&](int i) {
            if (remCount[rem[i]]++ == 0) numDistinctRem++;
            int idx = getIdx(quo[i]);
            updateBIT(countBIT, idx, 1);
            updateBIT(sumBIT, idx, quo[i]);
            curSize++;
        };
        
        auto removeFn = [&](int i) {
            if (--remCount[rem[i]] == 0) numDistinctRem--;
            int idx = getIdx(quo[i]);
            updateBIT(countBIT, idx, -1);
            updateBIT(sumBIT, idx, -quo[i]);
            curSize--;
        };
        
        auto getMedian = [&]() -> int {
            int target = (curSize + 1) / 2;
            int lo = 1, hi = m;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (queryBIT(countBIT, mid) >= target) hi = mid;
                else lo = mid + 1;
            }
            return sortedQuo[lo - 1];
        };
        
        auto computeOps = [&]() -> long long {
            if (numDistinctRem > 1) return -1;
            if (curSize <= 1) return 0;
            
            int median = getMedian();
            int medianIdx = getIdx(median);
            
            long long countLess = queryBIT(countBIT, medianIdx - 1);
            long long sumLess = queryBIT(sumBIT, medianIdx - 1);
            
            long long totalSum = queryBIT(sumBIT, m);
            long long countLessEq = queryBIT(countBIT, medianIdx);
            long long sumLessEq = queryBIT(sumBIT, medianIdx);
            
            long long countGreater = curSize - countLessEq;
            long long sumGreater = totalSum - sumLessEq;
            
            long long ops = (long long)median * countLess - sumLess + sumGreater - (long long)median * countGreater;
            
            return ops;
        };
        
        vector<long long> ans(q);
        int curL = 0, curR = -1;
        
        for (int i : order) {
            int l = queries[i][0], r = queries[i][1];
            
            while (curR < r) add(++curR);
            while (curL > l) add(--curL);
            while (curR > r) removeFn(curR--);
            while (curL < l) removeFn(curL++);
            
            ans[i] = computeOps();
        }
        
        return ans;
    }
};
# @lc code=end