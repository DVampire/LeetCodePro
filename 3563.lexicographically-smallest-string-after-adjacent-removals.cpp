#include <string>
#include <vector>
#include <functional>
using namespace std;

class Solution {
private:
    bool cons(char a, char b) {
        int diff = (a - b + 26) % 26;
        return diff == 1 || diff == 25;
    }
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        vector<vector<bool>> vis(n, vector<bool>(n));
        vector<vector<string>> memo(n, vector<string>(n));
        
        function<string(int,int)> dfs = [&](int l,int r)->string {
            if(l > r) return "";
            if(l == r) return string(1,s[l]);
            if(vis[l][r]) return memo[l][r];
            
            vector<string> candidates;
            // entire substring unchanged
            candidates.push_back(s.substr(l, r-l+1));
            // keep first char
            candidates.push_back(string(1,s[l]) + dfs(l+1,r));
            // try matching first char
            for(int j=l+1; j<=r; ++j){
                if(cons(s[l],s[j])){
                    // require interior [l+1 .. j-1] reducible to ""
                    string inner = dfs(l+1,j-1);
                    if(inner.empty()){
                        // remainder
                        candidates.push_back(dfs(j+1,r));
                    }
                }
            }
            
            // find minimum
            string ans = candidates[0];
            for(const auto& str : candidates){
                if(str < ans){
                    ans = str;
                }
            }
            vis[l][r] = true;
            memo[l][r] = ans;
            return ans;
        };
        
        return dfs(0,n-1);
    }
};