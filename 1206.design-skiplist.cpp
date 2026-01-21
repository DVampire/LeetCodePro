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
        vector<Node*> forward;
        Node(int v, int level) : val(v), forward(level, nullptr) {}
    };
    
    Node* head;
    int maxLevel;
    int currentLevel;
    
    int randomLevel() {
        int level = 1;
        while (rand() % 2 == 0 && level < maxLevel) {
            level++;
        }
        return level;
    }
    
public:
    Skiplist() {
        maxLevel = 16;
        currentLevel = 1;
        head = new Node(-1, maxLevel);
    }
    
    bool search(int target) {
        Node* curr = head;
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        return curr && curr->val == target;
    }
    
    void add(int num) {
        vector<Node*> update(maxLevel, nullptr);
        Node* curr = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        
        int level = randomLevel();
        if (level > currentLevel) {
            for (int i = currentLevel; i < level; i++) {
                update[i] = head;
            }
            currentLevel = level;
        }
        
        Node* newNode = new Node(num, level);
        for (int i = 0; i < level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool erase(int num) {
        vector<Node*> update(maxLevel, nullptr);
        Node* curr = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        
        curr = curr->forward[0];
        if (!curr || curr->val != num) {
            return false;
        }
        
        for (int i = 0; i < currentLevel; i++) {
            if (update[i]->forward[i] != curr) {
                break;
            }
            update[i]->forward[i] = curr->forward[i];
        }
        
        delete curr;
        
        while (currentLevel > 1 && !head->forward[currentLevel - 1]) {
            currentLevel--;
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
# @lc code=end