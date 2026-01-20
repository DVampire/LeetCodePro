#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
#include <vector>
#include <cstdlib>

class Skiplist {
    struct Node {
        int val;
        int level;
        Node* next[16];
        Node(int v, int lv) : val(v), level(lv) {
            for (int i = 0; i < 16; ++i) next[i] = nullptr;
        }
    };

    Node* head;
    const int MAX_LEVEL = 16;

    int randomLevel() {
        int lv = 1;
        while (lv < MAX_LEVEL && (rand() % 2 == 0)) {
            lv++;
        }
        return lv;
    }

public:
    Skiplist() {
        head = new Node(-1, MAX_LEVEL);
    }
    
    bool search(int target) {
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < target) {
                curr = curr->next[i];
            }
        }
        curr = curr->next[0];
        return curr != nullptr && curr->val == target;
    }
    
    void add(int num) {
        Node* update[MAX_LEVEL];
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        
        int lv = randomLevel();
        Node* newNode = new Node(num, lv);
        for (int i = 0; i < lv; ++i) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    
    bool erase(int num) {
        Node* update[MAX_LEVEL];
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        
        curr = curr->next[0];
        if (!curr || curr->val != num) {
            return false;
        }
        
        for (int i = 0; i < curr->level; ++i) {
            if (update[i]->next[i] != curr) break;
            update[i]->next[i] = curr->next[i];
        }
        
        delete curr;
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