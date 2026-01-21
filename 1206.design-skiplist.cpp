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
        Node* right;
        Node* down;
        Node(int v = INT_MIN, Node* r = nullptr, Node* d = nullptr) 
            : val(v), right(r), down(d) {}
    };
    
    Node* head;
    
public:
    Skiplist() {
        head = new Node();
    }
    
    bool search(int target) {
        Node* curr = head;
        while (curr) {
            while (curr->right && curr->right->val < target) {
                curr = curr->right;
            }
            if (curr->right && curr->right->val == target) {
                return true;
            }
            curr = curr->down;
        }
        return false;
    }
    
    void add(int num) {
        vector<Node*> path;
        Node* curr = head;
        
        // Find insertion points at each level
        while (curr) {
            while (curr->right && curr->right->val < num) {
                curr = curr->right;
            }
            path.push_back(curr);
            curr = curr->down;
        }
        
        // Insert from bottom, moving up based on coin flip
        bool insertUp = true;
        Node* downNode = nullptr;
        
        for (int i = path.size() - 1; i >= 0 && insertUp; i--) {
            Node* newNode = new Node(num, path[i]->right, downNode);
            path[i]->right = newNode;
            downNode = newNode;
            insertUp = (rand() % 2 == 0);
        }
        
        // Add new levels if coin flip continues
        while (insertUp) {
            Node* newNode = new Node(num, nullptr, downNode);
            Node* newHead = new Node(INT_MIN, newNode, head);
            head = newHead;
            downNode = newNode;
            insertUp = (rand() % 2 == 0);
        }
    }
    
    bool erase(int num) {
        Node* curr = head;
        bool found = false;
        
        while (curr) {
            while (curr->right && curr->right->val < num) {
                curr = curr->right;
            }
            if (curr->right && curr->right->val == num) {
                found = true;
                curr->right = curr->right->right;
            }
            curr = curr->down;
        }
        
        // Clean up empty top levels
        while (head->right == nullptr && head->down != nullptr) {
            head = head->down;
        }
        
        return found;
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