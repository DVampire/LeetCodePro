#
# @lc app=leetcode id=3525 lang=python3
#
# [3525] Find X Value of Array II
#

# @lc code=start
from typing import List

class Solution:
    def resultArray(self, nums: List[int], k: int,
                    queries: List[List[int]]) -> List[int]:
        n = len(nums)
        # Reduce numbers modulo k
        arr_mod = [num % k for num in nums]

        # Helper Node class
        class Node:
            __slots__ = ('total_prod', 'mat')
            def __init__(self):
                self.total_prod = 0
                self.mat = [[0]*k for _ in range(k)]

        # Build Segment Tree
        size = 4*n
        tree = [Node() for _ in range(size)]

        # Combine two nodes representing consecutive intervals
        def combine(A: Node, B: Node) -> Node:
            res = Node()
            res.total_prod = (A.total_prod * B.total_prod) % k
            # Add contributions from staying entirely inside A
            for s in range(k):
                rowA = A.mat[s]
                rowRes = res.mat[s]
                for t in range(k):
                    rowRes[t] += rowA[t]
            # Add contributions from going through entire A plus non-empty prefix inside B
            for s in range(k):
                f_s = (s * A.total_prod) % k
                rowB = B.mat[f_s]
                rowRes = res.mat[s]
                for t in range(k):
                    rowRes[t] += rowB[t]
            return res

        # Build recursively
        def build(node:int,l:int,r:int):
            if l == r:
                v = arr_mod[l]
                nd = tree[node]
                nd.total_prod = v
                # Set mat
                mat = nd.mat
                # Reset mat to zeros already done
                # Fill
                for s in range(k):
                    t = (s*v) % k
                    mat[s][t] = 1
                return
            mid = (l+r)//2
            build(node<<1,l,mid)
            build(node<<1|1,mid+1,r)
            tree[node] = combine(tree[node<<1],tree[node<<1|1])

        build(0,0,n-1)

        # Point update
        def update(idx:int,v:int):
            def upd(node:int,l:int,r:int):
                if l == r:
                    nd = tree[node]
                    nd.total_prod = v
                    mat = nd.mat
                    # Reset mat
                    for row in mat:
                        row[:] = [0]*k
                    # Fill again
                    for s in range(k):
                        t=(s*v)%k
                        mat[s][t]=1
                    return
                mid=(l+r)//2
                if idx<=mid:
                    upd(node<<1,l,mid)
                else:
                    upd(node<<1|1,mid+1,r)
                tree[node]=combine(tree[node<<1],tree[node<<1|1])
            upd(0,0,n-1)

        # Range query returning Node
        def query(q_l:int,q_r:int)->Node:
            def que(node:int,l:int,r:int)->Node:
                if q_l<=l<=r<=q_r:
                    return tree[node]
                mid=(l+r)//2
                if q_r <= mid:
                    return que(node<<1,l,mid)
                elif q_l > mid:
                    return que(node<<1|1,mid+1,r)
                else:
                    left_res = que(node<<1,l,mid)
                    right_res = que(node<<1|1,mid+1,r)
                    return combine(left_res,right_res)
            return que(0,0,n-1)

        ans = []
        for idx_val_start_x in queries:
            idx_val_start_x...
            index_i_value_i_start_i_xi...
            index_i_value_i_start_i_xi ...
Actually parse variable names:
for idx_val_start_x ...
Actually unpack:
index_val_start_x ...
Actually each query has four integers.
Let idx valuei starti xi.
So:
index_val_start_x ...
index_val_start_x ...
Actually variable names:
for idxvaluestartx ...
for idxvaluestartx ...
Actually use:
index_val_start_x ...
for idxvaluestartx ...
for idxvaluestartx ...
Let idxvalueistartixi.
So:
index_value_start_x ...
Actually code:
for idxvaluestartx ...
for idxvaluestartx ...
Let idxvalueistartixi.
So write:
for idxvaluestartx ...
for idxvalueistartixi.
Ok.
