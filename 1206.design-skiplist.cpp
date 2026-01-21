#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=1206 lang=cpp
 *
 * [1206] Design Skiplist
 */

// @lc code=start
class Skiplist {
private:
    struct Node {
        int val;
        vector<Node*> next;
        Node(int v, int level) : val(v), next(level, nullptr) {}
    };

    static constexpr int MAX_LEVEL = 32;
    static constexpr double P = 0.5;

    Node* head;
    int level; // current highest level (1..MAX_LEVEL)

    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

    int randomLevel() {
        int lvl = 1;
        while (lvl < MAX_LEVEL && dist(rng) < P) ++lvl;
        return lvl;
    }

public:
    Skiplist() : head(new Node(-1, MAX_LEVEL)), level(1), rng(std::random_device{}()), dist(0.0, 1.0) {}

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
        array<Node*, MAX_LEVEL> update{};
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
        array<Node*, MAX_LEVEL> update{};
        Node* cur = head;

        for (int i = level - 1; i >= 0; --i) {
            while (cur->next[i] && cur->next[i]->val < num) {
                cur = cur->next[i];
            }
            update[i] = cur;
        }

        Node* target = cur->next[0];
        if (!target || target->val != num) return false;

        // Unlink from every level where it appears
        for (int i = 0; i < level; ++i) {
            if (update[i]->next[i] == target) {
                update[i]->next[i] = target->next[i];
            }
        }
        delete target;

        // Decrease current level if top levels are empty
        while (level > 1 && head->next[level - 1] == nullptr) {
            --level;
        }
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
// @lc code=end
