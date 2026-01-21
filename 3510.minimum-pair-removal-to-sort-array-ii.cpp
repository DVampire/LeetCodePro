#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=3510 lang=cpp
 *
 * [3510] Minimum Pair Removal to Sort Array II
 */

// @lc code=start
class Solution {
public:
    struct Node {
        long long val;
        int prev = -1, next = -1;
        int pos = 0;      // leftmost original index of this segment
        int ver = 0;      // increments when val changes
        bool alive = true;
    };

    struct Entry {
        long long sum;
        int pos;
        int left, lver;
        int right, rver;
    };

    struct Cmp {
        bool operator()(const Entry& a, const Entry& b) const {
            if (a.sum != b.sum) return a.sum > b.sum;   // min-heap by sum
            return a.pos > b.pos;                       // tie: leftmost
        }
    };

    int minimumPairRemoval(vector<int>& nums) {
        int n = (int)nums.size();
        if (n <= 1) return 0;

        vector<Node> nodes(n);
        for (int i = 0; i < n; i++) {
            nodes[i].val = (long long)nums[i];
            nodes[i].pos = i;
            nodes[i].prev = i - 1;
            nodes[i].next = (i + 1 < n ? i + 1 : -1);
        }

        long long inversions = 0;
        for (int i = 0; i + 1 < n; i++) {
            if ((long long)nums[i] > (long long)nums[i + 1]) inversions++;
        }
        if (inversions == 0) return 0;

        priority_queue<Entry, vector<Entry>, Cmp> pq;

        auto pushPair = [&](int left) {
            if (left == -1 || !nodes[left].alive) return;
            int right = nodes[left].next;
            if (right == -1 || !nodes[right].alive) return;
            pq.push(Entry{
                nodes[left].val + nodes[right].val,
                nodes[left].pos,
                left, nodes[left].ver,
                right, nodes[right].ver
            });
        };

        for (int i = 0; i + 1 < n; i++) pushPair(i);

        auto isInv = [&](int a, int b) -> bool {
            if (a == -1 || b == -1) return false;
            // a and b are expected alive when called
            return nodes[a].val > nodes[b].val;
        };

        int ops = 0;
        while (true) {
            // get valid minimum pair
            Entry e;
            while (true) {
                e = pq.top();
                pq.pop();
                int l = e.left, r = e.right;
                if (l == -1 || r == -1) continue;
                if (!nodes[l].alive || !nodes[r].alive) continue;
                if (nodes[l].ver != e.lver || nodes[r].ver != e.rver) continue;
                if (nodes[l].next != r) continue;
                // valid
                break;
            }

            int x = e.left;
            int y = e.right;           // y == nodes[x].next
            int p = nodes[x].prev;
            int nn = nodes[y].next;

            // remove old inversion contributions
            if (p != -1 && isInv(p, x)) inversions--;
            if (isInv(x, y)) inversions--;
            if (nn != -1 && isInv(y, nn)) inversions--;

            // merge y into x
            nodes[x].val += nodes[y].val;
            nodes[x].ver++;
            nodes[x].next = nn;
            if (nn != -1) nodes[nn].prev = x;

            nodes[y].alive = false;
            nodes[y].prev = nodes[y].next = -1;

            // add new inversion contributions
            if (p != -1 && isInv(p, x)) inversions++;
            if (nn != -1 && isInv(x, nn)) inversions++;

            // update affected pairs in heap
            if (p != -1) pushPair(p);
            pushPair(x);

            ops++;
            if (inversions == 0) return ops;
        }
    }
};
// @lc code=end
