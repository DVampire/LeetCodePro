#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n+1);
        for(auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        const int MOD = 1000000007;
        int LOG = ceil(log2(n)) + 1;
        vector<vector<int>> up(LOG, vector<int>(n+1));
        vector<int> depth(n+1);

        function<void(int,int)> dfs = [&](int u, int p) {
            up[0][u] = p;
            for(int i=1; i<LOG; ++i) {
                up[i][u] = up[i-1][up[i-1][u]];
            }
            for(int v : adj[u]) {
                if(v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v,u);
            }
        };

        dfs(1,0);

        auto lca = [&](int u,int v)->int {
            if(depth[u]<depth[v]) swap(u,v);
            int diff=depth[u]-depth[v];
            for(int i=0;i<LOG;++i)
                if(diff & (1<<i))
                    u=up[i][u];
            if(u==v) return u;
            for(int i=LOG-1;i>=0;--i)
                if(up[i][u]!=up[i][v]){
                    u=up[i][u];
                    v=up[i][v];
                }
            return up[0][u];
        };

        vector<long long> pow2(n+1);
        pow2[0]=1;
        for(int i=1;i<=n;++i)
            pow2[i]=(pow2[i-1]*2)%MOD;

        vector<int> ans;
        ans.reserve(queries.size());
        for(auto& q : queries) {
            int u=q[0],v=q[1];
            int anc=lca(u,v);
            int d=depth[u]+depth[v]-2*depth[anc];
            ans.push_back(d==0 ? 0 : pow2[d-1]);
        }
        return ans;
    }
};
# @lc code=end