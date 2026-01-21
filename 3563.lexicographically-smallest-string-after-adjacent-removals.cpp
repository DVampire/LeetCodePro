#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#
# @lc code=start
class Solution {
public:
    bool isConsecutive(char a, char b) {
        int diff = abs(a - b);
        return diff == 1 || diff == 25;
    }
    
    string lexicographicallySmallestString(string s) {
        set<string> visited;
        queue<string> q;
        q.push(s);
        visited.insert(s);
        string result = s;
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            if (curr < result) {
                result = curr;
            }
            
            // Try all possible removals
            for (int i = 0; i < (int)curr.length() - 1; i++) {
                if (isConsecutive(curr[i], curr[i+1])) {
                    string next = curr.substr(0, i) + curr.substr(i + 2);
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        
        return result;
    }
};
# @lc code=end