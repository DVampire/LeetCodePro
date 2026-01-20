#include <vector>
#include <cstdlib>

#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
class Skiplist {
private:
    struct Node {
        int val;
        Node* next[16];
        Node(int v) : val(v) {
            for (int i = 0; i < 16; ++i) next[i] = nullptr;
        }
    };

    Node* head;
    const int MAX_LEVEL = 16;

    int randomLevel() {
        int lvl = 1;
        while (lvl < MAX_LEVEL && (rand() % 2 == 0)) {
            lvl++;
        }
        return lvl;
    }

public:
    Skiplist() {
        head = new Node(-1);
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
        
        int lvl = randomLevel();
        Node* newNode = new Node(num);
        for (int i = 0; i < lvl; ++i) {
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
        if (!curr || curr->val != num) return false;
        
        for (int i = 0; i < MAX_LEVEL; ++i) {
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