#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    struct Node {
        long long min_val;
        long long rate_right;
        long long lz_add;
        long long lz_set_rate;
        bool has_set_rate;
        long long lz_tick;
    };

    vector<Node> tree;
    int n;

    void push_tick(int node, long long tick) {
        tree[node].min_val += tree[node].rate_right * tick;
        tree[node].lz_tick += tick;
    }

    void push_set_rate(int node, long long rate) {
        // Before setting rate, we must ensure any pending ticks are processed by children
        // However, in our logic, we push ticks before setting rate in push()
        // So here we just set the rate.
        tree[node].rate_right = rate;
        tree[node].lz_set_rate = rate;
        tree[node].has_set_rate = true;
    }

    void push_add(int node, long long val) {
        tree[node].min_val += val;
        tree[node].lz_add += val;
    }

    void push(int node, int start, int end) {
        int mid = (start + end) / 2;
        int left = 2 * node;
        int right = 2 * node + 1;

        // 1. Push Set Rate
        if (tree[node].has_set_rate) {
            // If we are setting rate, previous ticks on children should be valid with OLD rate.
            // But wait, if we have pending ticks on current node, they happened *before* or *after* set rate?
            // In our loop: Set Rate -> Tick -> Add Val.
            // So Ticks accumulate AFTER Set Rate.
            // So if we have both Set Rate and Tick, Set Rate happened first.
            // So we apply Set Rate to children, THEN Tick.
            
            // Actually, if `lz_set_rate` is present, it overrides previous rates.
            // We must clear children's pending ticks? No.
            // Children's pending ticks occurred before this Set Rate? 
            // No, the lazy tags on `node` are ordered accumulation of operations.
            // Since we always do SetRate then Tick, `lz_set_rate` corresponds to an operation 
            // that happened before the `lz_tick` accumulation.
            // However, `lz_tick` applies to the NEW rate.
            // So we push `lz_set_rate` first, then `lz_tick`.
            
            // But wait, does `lz_set_rate` override children's `lz_set_rate`? Yes.
            // Does it affect children's `lz_tick`? 
            // The children might have `lz_tick` from previous steps. 
            // Those ticks used the OLD rate. 
            // We must `push` the children essentially? 
            // No, standard lazy prop: we assume children are clean relative to `node`'s new ops.
            // But children might have old tags. 
            // We need to apply `lz_set_rate` to children. 
            // If child has `lz_tick`, that tick used child's old rate. That is correct. 
            // We just update child's current rate for FUTURE ticks.
            
            push_set_rate(left, tree[node].lz_set_rate);
            push_set_rate(right, tree[node].lz_set_rate);
            tree[node].has_set_rate = false;
        }

        // 2. Push Tick
        if (tree[node].lz_tick > 0) {
            push_tick(left, tree[node].lz_tick);
            push_tick(right, tree[node].lz_tick);
            tree[node].lz_tick = 0;
        }

        // 3. Push Add
        if (tree[node].lz_add != 0) {
            push_add(left, tree[node].lz_add);
            push_add(right, tree[node].lz_add);
            tree[node].lz_add = 0;
        }
    }

    void update_set_rate(int node, int start, int end, int l, int r, long long val) {
        if (l > end || r < start) return;
        if (l <= start && end <= r) {
            // Important: If we have pending ticks, we must push them? 
            // No, we are setting rate now. Ticks accumulated on this node apply to the rate *after* this set?
            // Or *before*? 
            // In our global loop: Set Rate, THEN Tick.
            // So `lz_tick` on this node (if any) belongs to AFTER this Set Rate operation from previous steps? 
            // No, `lz_tick` is cleared at end of push.
            // If we visit this node, we pushed everything. `lz_tick` is 0.
            // So we can safely set rate.
            push_set_rate(node, val);
            return;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        update_set_rate(2 * node, start, mid, l, r, val);
        update_set_rate(2 * node + 1, mid + 1, end, l, r, val);
        // Pull up
        tree[node].min_val = tree[2 * node + 1].min_val; // Rightmost min
        tree[node].rate_right = tree[2 * node + 1].rate_right;
    }

    void update_tick(int node, int start, int end, int l, int r, long long val) {
        if (l > end || r < start) return;
        if (l <= start && end <= r) {
            push_tick(node, val);
            return;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        update_tick(2 * node, start, mid, l, r, val);
        update_tick(2 * node + 1, mid + 1, end, l, r, val);
        tree[node].min_val = tree[2 * node + 1].min_val;
        tree[node].rate_right = tree[2 * node + 1].rate_right;
    }

    void update_add(int node, int start, int end, int l, int r, long long val) {
        if (l > end || r < start) return;
        if (l <= start && end <= r) {
            push_add(node, val);
            return;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        update_add(2 * node, start, mid, l, r, val);
        update_add(2 * node + 1, mid + 1, end, l, r, val);
        tree[node].min_val = tree[2 * node + 1].min_val;
        tree[node].rate_right = tree[2 * node + 1].rate_right;
    }
    
    // Find first index i such that val[i] <= k
    // Since val is monotonic decreasing, we look for the first i.
    // If left child's min_val (which is val[mid]) <= k, then answer is in left or before.
    // Wait, val[0] > val[1] > ... > val[n]. 
    // min_val of left child is val[mid]. 
    // If val[mid] <= k, then mid is valid. Since it's decreasing, all i > mid are valid.
    // We want the *smallest* i. So if val[mid] <= k, we try left child.
    // If val[mid] > k, then mid is invalid. All i < mid are invalid (larger). We try right child.
    int find_first(int node, int start, int end, long long k) {
        if (start == end) {
            return (tree[node].min_val <= k) ? start : -1;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        // Check min_val of left child. 
        // In our definition, min_val is the value at the right end of the range.
        // So tree[2*node].min_val is val[mid].
        if (tree[2 * node].min_val <= k) {
            int res = find_first(2 * node, start, mid, k);
            return res != -1 ? res : -1; // Should be res, as mid is valid.
        } else {
            return find_first(2 * node + 1, mid + 1, end, k);
        }
    }

public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        n = nums.size();
        tree.resize(4 * n + 1, {0, 0, 0, 0, false, 0});
        
        vector<int> stack = {-1};
        long long ans = 0;

        for (int right = 0; right < n; ++right) {
            long long num = nums[right];
            
            // 1. Update rates based on stack
            while (stack.size() > 1 && nums[stack.back()] <= num) {
                int idx = stack.back();
                stack.pop_back();
                int prev = stack.back();
                // Range (prev + 1, idx] was dominated by nums[idx]
                // Now it is dominated by num. 
                // We update rate.
                update_set_rate(1, 0, n - 1, prev + 1, idx, num);
            }
            int prev = stack.back();
            update_set_rate(1, 0, n - 1, prev + 1, right, num);
            stack.push_back(right);

            // 2. Tick (Add rates)
            update_tick(1, 0, n - 1, 0, right, 1);

            // 3. Add -num
            update_add(1, 0, n - 1, 0, right, -num);

            // 4. Query
            int left = find_first(1, 0, n - 1, k);
            if (left != -1 && left <= right) {
                ans += (right - left + 1);
            }
        }

        return ans;
    }
};
