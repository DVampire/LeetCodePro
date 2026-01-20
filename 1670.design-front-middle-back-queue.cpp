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

    // Maintain invariant: left.size() <= right.size() <= left.size() + 1
    void balance() {
        if (left.size() > right.size()) {
            right.push_front(left.back());
            left.pop_back();
        } else if (right.size() > left.size() + 1) {
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
        if (left.size() == right.size()) {
            right.push_front(val);
        } else {
            left.push_back(val);
        }
    }
    
    void pushBack(int val) {
        right.push_back(val);
        balance();
    }
    
    int popFront() {
        if (left.empty() && right.empty()) return -1;
        int val;
        if (left.empty()) {
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
        int val;
        if (left.size() == right.size()) {
            val = left.back();
            left.pop_back();
        } else {
            val = right.front();
            right.pop_front();
        }
        // Invariant is naturally maintained by logic
        return val;
    }
    
    int popBack() {
        if (right.empty()) return -1;
        int val = right.back();
        right.pop_back();
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