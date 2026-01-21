#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class TextEditor {
    vector<char> left;
    vector<char> right;

    string lastTenLeft() {
        int n = (int)left.size();
        int start = max(0, n - 10);
        return string(left.begin() + start, left.end());
    }

public:
    TextEditor() {}

    void addText(string text) {
        for (char c : text) left.push_back(c);
    }

    int deleteText(int k) {
        int del = min(k, (int)left.size());
        while (del--) left.pop_back();
        return min(k, (int)(left.size() + (k - min(k, (int)left.size())))); // not used, but keep simple? 
    }

    string cursorLeft(int k) {
        int mv = min(k, (int)left.size());
        while (mv--) {
            right.push_back(left.back());
            left.pop_back();
        }
        return lastTenLeft();
    }

    string cursorRight(int k) {
        int mv = min(k, (int)right.size());
        while (mv--) {
            left.push_back(right.back());
            right.pop_back();
        }
        return lastTenLeft();
    }
};
// @lc code=end
