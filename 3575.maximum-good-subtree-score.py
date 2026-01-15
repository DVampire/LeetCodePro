#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#
# @lc code=start
from typing import List

class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        MOD = int(10**9 + 7)
        n = len(vals)
        adj = [[] for _ in range(n)]
        
        # Build directed tree edges
        for i in range(1,n):
            p = par[i]
            adj[p].append(i)
        
        # Precompute masks
        valid = [True]*n
        masks = [0]*n
        INF_NEG = -10**18
        
        def get_mask(x:int)->int:
            s=str(x)
            seen_set=set()
            dup=False
            res_mask=0
            for ch in s:
                d=int(ch)
                if d in seen_set:
                    dup=True
                    break
                seen_set.add(d)
                res_mask|= (1<<d)
            return -1 if dup else res_mask
        
        for i,v in enumerate(vals):
            m=get_mask(v)
            valid[i]=False if m==-1 else True
            masks[i]=m
        
        total_sum_mod=[0]
        
        def dfs(u):
            """returns list length 1024"""
            cur=[INF_NEG]*1024
            cur[0]=0
            
            if valid[u]:
                mu,mv=masks[u],vals[u]
                cur[mu]=max(cur[mu], mv)
            
            # Process children
            for v in adj[u]:
                ch_dp=dfs(v)
                ch_list=[(mval,cval)for(mval,cval)in enumerate(ch_dp)if cval>=0]
                
                parent_list=[(mval,cval)for(mval,cval)in enumerate(cur)if cval>=0]
                
                nxt=cur[:]
                
                for pm,pv in parent_list:
                    for cm,cv in ch_list:
                        if pm & cm==0:
                            nmask=pm|cm
                            cand=pv+cv
                            nxt[nmask]=max(nxt[nmask],cand)
                cur=nxt
            
            best=max(cur)
            total_sum_mod[0]=(total_sum_mod[0]+best)%MOD
            return cur
        
        dfs(0)
        return total_sum_mod[0]
# @lc code=end