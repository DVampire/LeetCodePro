#
# @lc app=leetcode id=1670 lang=cpp
#
# [1670] Design Front Middle Back Queue
#

# @lc code=start
#include <deque>

class FrontMiddleBackQueue {
private:
    std::deque<int> left;
    std::deque<int> right;

    // Helper function to maintain balance: 
    // We want left.size() == right.size() or left.size() == right.size() + 1
    void balance() {
        if (left.size() > right.size() + 1) {
            right.push_front(left.back());
            left.pop_back();
        } else if (left.size() < right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {
        
    }
    
    void pushFront(int val) {
        left.push_front(val);
        balance();
    }
    
    void pushMiddle(int val) {
        // If sizes are equal, the new element belongs to left (becoming the new middle)
        // If left > right, we move the current middle (left.back) to right, then add to left.
        if (left.size() > right.size()) {
            right.push_front(left.back());
            left.pop_back();
        }
        left.push_back(val);
        // No explicit balance needed as we handled the shift manually, 
        // but calling it is safe.
    }
    
    void pushBack(int val) {
        right.push_back(val);
        balance();
    }
    
    int popFront() {
        if (left.empty() && right.empty()) return -1;
        int val;
        if (left.empty()) {
            // This case happens if only right has elements (shouldn't happen with our balance invariant unless total size is 0, handled above)
            // However, strictly speaking if left is empty, right must be empty too based on invariant.
            // But for safety/logic flow:
            val = right.front();
            right.pop_front();
        } else {
            val = left.front();
            left.pop_front();
        }
        balance();
        return val;
    }
    
    int popMiddle() {
        if (left.empty() && right.empty()) return -1;
        // The middle element is always at left.back() due to our invariant
        // (left.size() >= right.size())
        int val = left.back();
        left.pop_back();
        balance();
        return val;
    }
    
    int popBack() {
        if (left.empty() && right.empty()) return -1;
        int val;
        if (right.empty()) {
            val = left.back();
            left.pop_back();
        } else {
            val = right.back();
            right.pop_back();
        }
        balance();
        return val;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
# @lc code=end