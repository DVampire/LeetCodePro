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
        std::vector<Node*> next;
        Node(int v, int level) : val(v), next(level, nullptr) {}
    };

    Node* head;
    const int MAX_LEVEL = 16;

    int randomLevel() {
        int lv = 1;
        // Probability p = 0.5 for level promotion
        while (lv < MAX_LEVEL && (rand() & 1)) {
            lv++;
        }
        return lv;
    }

public:
    Skiplist() {
        // Initialize head with a dummy value and maximum possible height
        head = new Node(-1, MAX_LEVEL);
    }
    
    bool search(int target) {
        Node* curr = head;
        // Traverse from top level to bottom
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < target) {
                curr = curr->next[i];
            }
        }
        // Move to the actual potential node at level 0
        curr = curr->next[0];
        return curr != nullptr && curr->val == target;
    }
    
    void add(int num) {
        std::vector<Node*> update(MAX_LEVEL, head);
        Node* curr = head;
        // Find predecessors for the new node at each level
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        int level = randomLevel();
        Node* newNode = new Node(num, level);
        // Link the new node into the levels
        for (int i = 0; i < level; ++i) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
    
    bool erase(int num) {
        std::vector<Node*> update(MAX_LEVEL, head);
        Node* curr = head;
        // Find predecessors for the target node
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->next[i] && curr->next[i]->val < num) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        curr = curr->next[0];
        // If node doesn't exist, return false
        if (!curr || curr->val != num) return false;

        // Update pointers at each level to remove the node
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