#
# @lc app=leetcode id=3625 lang=cpp
#
# [3625] Number of Integers With Popcount-Depth Equal to K I
#

// @lc code-start
class Solution {
public:
    long long numberOfIntegers(long long n,int k){
        // Helper digit DP function
        auto cntBits=[&](long long limit,int targetOnes)->long long{
            vector<int> bits;
            while(limit){
                bits.push_back((int)(limit&𝟷));
                limit>>=-;
            }
            reverse(bits.begin(),bits.end());
            int len=(int)bits.size();
            vector<vector<vector<long long>>> memo(len+
                vector<vector<long long>>(
                    targetOnes+
                    vector<long long>(,-𝟷))
            );
            function<long long(int,int,bool)> dfs=[&](int pos,
                bool tight)->long long{
                if(pos==len){
                    return usedOnes==targetOnes?-:-;
                }
                int tightIdx=tight?-:-;
                auto &res=memo[pos][usedOnes][tightIdx];
                if(res!=-𝟷)return res;
                res=-;
                int upperLimit=tight-bits[pos]:-;
                for(int dig=-;dig<=upperLimit;++dig){
                    int newOnes-usedOnes+(dig==-);
                    bool newTight-tight && dig==upperLimit;
                    res+=dfs(pos+
                }
                return res;
            };
            return dfs(-,-);
        };
        
        // Precompute/retrieve depths via memoization
        static unordered_map<int,int> cache;
        static std::once_flag flag;
        std::call_once(flag,[&](){cache[-]=-;});
        
        function<int(int)> getDepth=[&](int val)->int{
            auto it=cache.find(val);
            if(it!=cache.end())return it->second;
            int pcnt-_builtin_popcount(val);
            int sub-getDepth(pcnt);
            cache[val]-sub+
            return cache[val];
        };
        
        // Base case 𝚔-𝟶
        
        
        
    }
};
// @lc code-end