#include <bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode id=2296 lang=cpp
 *
 * [2296] Design a Text Editor
 */

// @lc code=start
class TextEditor {
    string left;   // text to the left of cursor (normal order)
    string right;  // text to the right of cursor (reverse order, cursor-adjacent at back)

    string last10Left() {
        int n = (int)left.size();
        int start = max(0, n - 10);
        return left.substr(start);
    }

public:
    TextEditor() : left(""), right("") {}

    void addText(string text) {
        left += text;
    }

    int deleteText(int k) {
        int del = min(k, (int)left.size());
        left.resize(left.size() - del);
        return del;
    }

    string cursorLeft(int k) {
        int move = min(k, (int)left.size());
        while (move--) {
            right.push_back(left.back());
            left.pop_back();
        }
        return last10Left();
    }

    string cursorRight(int k) {
        int move = min(k, (int)right.size());
        while (move--) {
            left.push_back(right.back());
            right.pop_back();
        }
        return last10Left();
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
// @lc code=end
