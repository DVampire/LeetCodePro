#include <bits/stdc++.h>
using namespace std;

#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
class Skiplist {
    struct Node {
        int val;
        vector<Node*> next;
        Node(int v, int level) : val(v), next(level, nullptr) {}
    };

    static constexpr int MAX_LEVEL = 32;

    Node* head;
    int level; // current highest level count (1..MAX_LEVEL)

    mt19937 rng;
    bernoulli_distribution coin;

    int randomLevel() {
        int lvl = 1;
        while (lvl < MAX_LEVEL && coin(rng)) ++lvl;
        return lvl;
    }

public:
    Skiplist() : head(new Node(INT_MIN, MAX_LEVEL)), level(1), rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()), coin(0.5) {
    }

    bool search(int target) {
        Node* cur = head;
        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->val < target) {
                cur = cur->next[i];
            }
        }
        cur = cur->next[0];
        return cur && cur->val == target;
    }

    void add(int num) {
        vector<Node*> update(MAX_LEVEL, nullptr);
        Node* cur = head;

        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->val < num) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }

        int nodeLevel = randomLevel();
        if (nodeLevel > level) {
            for (int i = level; i < nodeLevel; ++i) update[i] = head;
            level = nodeLevel;
        }

        Node* node = new Node(num, nodeLevel);
        for (int i = 0; i < nodeLevel; ++i) {
            node->next[i] = update[i]->next[i];
            update[i]->next[i] = node;
        }
    }

    bool erase(int num) {
        vector<Node*> update(MAX_LEVEL, nullptr);
        Node* cur = head;

        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->val < num) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }

        Node* target = update[0]->next[0];
        if (!target || target->val != num) return false;

        for (int i = 0; i < level; ++i) {
            if (update[i]->next[i] != target) break;
            update[i]->next[i] = target->next[i];
        }
        delete target;

        while (level > 1 && head->next[level - 1] == nullptr) --level;
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
# @lc code=end
