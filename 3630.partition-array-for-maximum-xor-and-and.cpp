#
# @lc app=leetcode id=3630 lang=cpp
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution {
public:
    long long ans;
    vector<int> arr;
    int n;

    void dfs(int idx, long long xorA, long long andB, long long xorC) {
        if(idx == n){
            ans = max(ans ,xorA+andB+xorC);
            return;
        }
        // assign arr[idx] to A
        dfs(idx+1 ,xorA^arr[idx],andB,xorC);
        // assign arr[idx] to B
        dfs(idx+1 ,xorA ,andB&arr[idx],xorC);
        // assign arr[idx] to C
        dfs(idx+1 ,xorA ,andB ,xorC^arr[idx]);
    }

    long long maximizeXorAndXor(vector<int>& nums) {
        arr=nums;
        n=nums.size();
        ans=0;
        // sort descending might help pruning early
        sort(arr.rbegin(),arr.rend());
        // initialise :
        // empty group A :xorA=0
        // empty group B :andB should be identity => all ones (~0LL)
        // empty group C :xorC=0
        dfs(0 ,0,(long long)(~0LL),0);
        return ans;
    }
};
# @lc code=end