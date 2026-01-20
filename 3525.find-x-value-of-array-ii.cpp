#
# @lc app=leetcode id=3525 lang=cpp
#
# [3525] Find X Value of Array II
#

# @lc code=start
#include <vector>

using namespace std;

class Solution {
    struct Node {
        int count[6]; // k <= 5
        int total_prod;
        
        Node() {
            for(int i=0; i<6; ++i) count[i] = 0;
            total_prod = 1;
        }
    };
    
    vector<Node> tree;
    int n;
    int K;
    
    Node merge(const Node& l, const Node& r) {
        Node res;
        // Initialize with L counts (prefixes entirely within the left child)
        for(int i=0; i<K; ++i) {
            res.count[i] = l.count[i];
        }
        // Add R counts adjusted by L product (prefixes extending into the right child)
        for(int i=0; i<K; ++i) {
            if (r.count[i] > 0) {
                int val = (l.total_prod * i) % K;
                res.count[val] += r.count[i];
            }
        }
        res.total_prod = (l.total_prod * r.total_prod) % K;
        return res;
    }
    
    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            int val = nums[start] % K;
            tree[node].total_prod = val;
            for(int i=0; i<K; ++i) tree[node].count[i] = 0;
            tree[node].count[val] = 1;
        } else {
            int mid = (start + end) / 2;
            build(nums, 2*node, start, mid);
            build(nums, 2*node+1, mid+1, end);
            tree[node] = merge(tree[2*node], tree[2*node+1]);
        }
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            int v = val % K;
            tree[node].total_prod = v;
            for(int i=0; i<K; ++i) tree[node].count[i] = 0;
            tree[node].count[v] = 1;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = merge(tree[2*node], tree[2*node+1]);
        }
    }
    
    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            Node identity;
            identity.total_prod = 1;
            for(int i=0; i<K; ++i) identity.count[i] = 0;
            return identity;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        Node p1 = query(2*node, start, mid, l, r);
        Node p2 = query(2*node+1, mid+1, end, l, r);
        return merge(p1, p2);
    }
    
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        n = nums.size();
        K = k;
        tree.resize(4 * n);
        
        build(nums, 1, 0, n-1);
        
        vector<int> results;
        results.reserve(queries.size());
        
        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];
            
            update(1, 0, n-1, index, value);
            
            // We need the result for the subarray nums[start...n-1]
            // We query the segment tree for range [start, n-1]
            Node res = query(1, 0, n-1, start, n-1);
            results.push_back(res.count[x]);
        }
        return results;
    }
};
# @lc code=end