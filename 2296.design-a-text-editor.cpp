#
# @lc app=leetcode id=2296 lang=cpp
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor {
private:
    string L,R;
public:
    TextEditor() {
        
    }
    
    void addText(string text) {
        L.append(text);
    }
    
    int deleteText(int k) {
        int cnt = min(k,(int)L.size());
        L.resize(L.size()-cnt);
        return cnt;
    }
    
    string cursorLeft(int k) {
        int mv = min(k,(int)L.size());
        while(mv--) {
            R.push_back(L.back());
            L.pop_back();
        }
        int len = L.size();
        int start = max(0,len-10);
        return L.substr(start);
    }
    
    string cursorRight(int k) {
        int mv = min(k,(int)R.size());
        while(mv--) {
            L.push_back(R.back());
            R.pop_back();
        }
        int len = L.size();
        int start = max(0,len-10);
        return L.substr(start);
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