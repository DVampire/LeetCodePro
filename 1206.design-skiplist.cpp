#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
class Skiplist {
public:
    struct Node {
        int val;
        Node* forward[17];
        Node(int x) : val(x) {
            for (int i = 0; i < 17; ++i) {
                forward[i] = nullptr;
            }
        }
    };

    Skiplist() {
        head = new Node(-1);
        level = 0;
    }
    
    bool search(int target) {
        Node* cur = head;
        for (int i = level; i >= 0; --i) {
            while (cur->forward[i] != nullptr && cur->forward[i]->val < target) {
                cur = cur->forward[i];
            }
        }
        return cur->forward[0] != nullptr && cur->forward[0]->val == target;
    }
    
    void add(int num) {
        Node* update[17];
        Node* cur = head;
        for (int i = level; i >= 0; --i) {
            while (cur->forward[i] != nullptr && cur->forward[i]->val < num) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        Node* newnode = new Node(num);
        int newlev = randomLevel();
        if (newlev > level) {
            for (int i = level + 1; i < newlev; ++i) {
                update[i] = head;
            }
            level = newlev;
        }
        for (int i = 0; i < newlev; ++i) {
            newnode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newnode;
        }
    }
    
    bool erase(int num) {
        Node* update[17];
        Node* cur = head;
        for (int i = level; i >= 0; --i) {
            while (cur->forward[i] != nullptr && cur->forward[i]->val < num) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        Node* cand = update[0]->forward[0];
        if (cand == nullptr || cand->val != num) {
            return false;
        }
        for (int i = 0; i <= level; ++i) {
            if (update[i]->forward[i] == cand) {
                update[i]->forward[i] = cand->forward[i];
            }
        }
        return true;
    }

private:
    Node* head;
    int level;
    int randomLevel() {
        int res = 1;
        while (res < 16 && rand() % 2 == 0) {
            ++res;
        }
        return res;
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
