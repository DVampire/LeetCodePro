#
# @lc app=leetcode id=1670 lang=cpp
#
# [1670] Design Front Middle Back Queue
#
# @lc code=start
#include <deque>
using namespace std;

class FrontMiddleBackQueue {
    deque<int> left, right;

    void rebalance() {
        if (left.size() > right.size() + 1) {
            right.push_front(left.back());
            left.pop_back();
        } else if (left.size() < right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        left.push_front(val);
        rebalance();
    }

    void pushMiddle(int val) {
        if (left.size() > right.size()) {
            right.push_front(left.back());
            left.pop_back();
        }
        left.push_back(val);
        // invariant already satisfied
    }

    void pushBack(int val) {
        right.push_back(val);
        rebalance();
    }

    int popFront() {
        if (left.empty() && right.empty()) return -1;
        int ans;
        if (!left.empty()) {
            ans = left.front();
            left.pop_front();
        } else {
            ans = right.front();
            right.pop_front();
        }
        rebalance();
        return ans;
    }

    int popMiddle() {
        if (left.empty() && right.empty()) return -1;
        int ans = left.back();
        left.pop_back();
        rebalance();
        return ans;
    }

    int popBack() {
        if (left.empty() && right.empty()) return -1;
        int ans;
        if (!right.empty()) {
            ans = right.back();
            right.pop_back();
        } else {
            ans = left.back();
            left.pop_back();
        }
        rebalance();
        return ans;
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
