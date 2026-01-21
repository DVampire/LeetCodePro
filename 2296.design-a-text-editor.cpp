#
# @lc app=leetcode id=2296 lang=cpp
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor {
    string left;   // text to the left of cursor
    string right;  // text to the right of cursor, stored reversed (top near cursor)

    string last10Left() {
        int n = (int)left.size();
        int take = min(10, n);
        return left.substr(n - take, take);
    }

public:
    TextEditor() {}

    void addText(string text) {
        left += text;
    }

    int deleteText(int k) {
        int del = min(k, (int)left.size());
        left.resize(left.size() - del);
        return del;
    }

    string cursorLeft(int k) {
        while (k-- > 0 && !left.empty()) {
            right.push_back(left.back());
            left.pop_back();
        }
        return last10Left();
    }

    string cursorRight(int k) {
        while (k-- > 0 && !right.empty()) {
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
# @lc code=end
