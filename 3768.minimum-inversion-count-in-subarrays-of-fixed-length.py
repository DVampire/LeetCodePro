#
# @lc app=leetcode id=3768 lang=python3
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

from typing import List

# @lc code=start
class FenwickTree:
    def __init__(self,n):
        self.n=n
        self.tree=[0]*(n+2)
    def _lowbit(self,x):
        return x&(-x)
    def _update(self,i,v):
        while i<=self.n:
            self.tree[i]+=v
            i+=self._lowbit(i)
    def _query(self,i):
        s=0
        while i>0:
            s+=self.tree[i]
            i-=self._lowbit(i)
        return s
    def add(self,c):
        self._update(c+1,+1)
    def remove(self,c):
        self._update(c+1,-1)
    def count_less(self,c):
        if c<=0:
            return 0
        return self._query(c)
    def count_less_equal(self,c):
        return self._query(c+1)

class Solution:
    def minInversionCount(self,nums,k):
        n=len(nums)
        if k==:
            return 

        # coordinate compression
        sorted_unique=sorted(set(nums))
        val_to_idx={v:i for i,v in enumerate(sorted_unique)}
        m=len(sorted_unique)

        ft=FenwickTree(m)

        # compute initial inversion count for first k elements
        inv=
        for i in range(k):
            idx=val_to_idx[nums[i]]
            # number of previously inserted elements greater than nums[i]
            cur_total=i
            leq=ft.count_less_equal(idx)
            inv += cur_total-leq
            ft.add(idx)

        min_inv=inv

        # slide windows
        for left in range(n-k):
            # remove leftmost
            idx_left=val_to_idx[nums[left]]
            smaller=ft.count_less(idx_left)
            inv-=smaller
            ft.remove(idx_left)

            # add new rightmost
            idx_new=val_to_idx[nums[left+k]]
            cur_total=k-
            leq_new=ft.count_less_equal(idx_new)
            greater=cur_total-leq_new
            inv+=greater
            ft.add(idx_new)

            min_inv=min(min_inv,inv)

        return min_inv
# @lc code=end