#
# @lc app=leetcode id=3510 lang=cpp
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        using ll = long long;
        struct Node {
            ll val;
            int id;
            Node *prev, *next;
            bool active;
            Node(ll v, int i) : val(v), id(i), prev(nullptr), next(nullptr), active(true) {}
        };
        int n = nums.size();
        if (n <= 1) return 0;
        vector<Node> all_nodes;
        all_nodes.reserve(2 * n + 10);
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int i = 0; i < n; ++i) {
            all_nodes.emplace_back(nums[i], i);
            Node* nd = &all_nodes.back();
            if (tail) {
                tail->next = nd;
                nd->prev = tail;
            } else {
                head = nd;
            }
            tail = nd;
        }
        set<tuple<ll, int, Node*>> pq;
        Node* cur = head;
        while (cur && cur->next) {
            ll s = cur->val + cur->next->val;
            pq.insert({s, cur->id, cur});
            cur = cur->next;
        }
        int violations = 0;
        cur = head;
        while (cur && cur->next) {
            if (cur->val > cur->next->val) ++violations;
            cur = cur->next;
        }
        int ops = 0;
        while (violations > 0) {
            bool found = false;
            while (!pq.empty() && !found) {
                auto [s, idd, l] = *pq.begin();
                pq.erase(pq.begin());
                if (!l->active || l->next == nullptr || !l->next->active ||
                    l->val + l->next->val != s || l->id != idd) {
                    continue;
                }
                found = true;
                Node* r = l->next;
                Node* prevv = l->prev;
                Node* postt = r->next;
                bool hp = prevv != nullptr;
                bool hpo = postt != nullptr;
                int delta = 0;
                if (hp && prevv->val > l->val) --delta;
                if (l->val > r->val) --delta;
                if (hpo && r->val > postt->val) --delta;
                all_nodes.emplace_back(l->val + r->val, l->id);
                Node* newer = &all_nodes.back();
                newer->prev = prevv;
                newer->next = postt;
                if (prevv) prevv->next = newer;
                if (postt) postt->prev = newer;
                if (l == head) head = newer;
                l->active = false;
                r->active = false;
                if (hp && prevv->val > newer->val) ++delta;
                if (hpo && newer->val > postt->val) ++delta;
                violations += delta;
                if (hp) {
                    ll ns = prevv->val + newer->val;
                    pq.insert({ns, prevv->id, prevv});
                }
                if (hpo) {
                    ll ns = newer->val + postt->val;
                    pq.insert({ns, newer->id, newer});
                }
                ++ops;
            }
            if (!found) break;
        }
        return ops;
    }
};
# @lc code=end