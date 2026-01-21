#
# @lc app=leetcode id=1670 lang=cpp
#
# [1670] Design Front Middle Back Queue
#
#include <deque>
using namespace std;

# @lc code=start
class FrontMiddleBackQueue {
    deque<int> L, R; // queue = L + R

    void rebalance() {
        while (L.size() > R.size() + 1) {
            R.push_front(L.back());
            L.pop_back();
        }
        while (L.size() < R.size()) {
            L.push_back(R.front());
            R.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        L.push_front(val);
        rebalance();
    }

    void pushMiddle(int val) {
        if (L.size() > R.size()) {
            R.push_front(L.back());
            L.pop_back();
        }
        L.push_back(val);
        rebalance();
    }

    void pushBack(int val) {
        R.push_back(val);
        rebalance();
    }

    int popFront() {
        if (L.empty() && R.empty()) return -1;
        int ans = L.front();
        L.pop_front();
        rebalance();
        return ans;
    }

    int popMiddle() {
        if (L.empty() && R.empty()) return -1;
        int ans = L.back();
        L.pop_back();
        rebalance();
        return ans;
    }

    int popBack() {
        if (L.empty() && R.empty()) return -1;
        int ans;
        if (!R.empty()) {
            ans = R.back();
            R.pop_back();
        } else {
            ans = L.back();
            L.pop_back();
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
