//
// @lc app=leetcode id=2296 lang=cpp
//
// [2296] Design a Text Editor
//

// @lc code=start
class TextEditor {
private:
    string left;  // Characters to the left of cursor
    string right; // Characters to the right of cursor (stored in reverse)
    
public:
    TextEditor() {
        
    }
    
    void addText(string text) {
        left += text;
    }
    
    int deleteText(int k) {
        int deleted = min(k, (int)left.size());
        left.resize(left.size() - deleted);
        return deleted;
    }
    
    string cursorLeft(int k) {
        int moves = min(k, (int)left.size());
        while (moves--) {
            right.push_back(left.back());
            left.pop_back();
        }
        int len = min(10, (int)left.size());
        return len == 0 ? "" : left.substr(left.size() - len);
    }
    
    string cursorRight(int k) {
        int moves = min(k, (int)right.size());
        while (moves--) {
            left.push_back(right.back());
            right.pop_back();
        }
        int len = min(10, (int)left.size());
        return len == 0 ? "" : left.substr(left.size() - len);
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