#
# @lc app=leetcode id=3563 lang=python3
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#
from functools import lru_cache
# @lc code=start
class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        n = len(s)
        ords = [ord(ch)-97 for ch in s]
        
        def cons(a,b):
            # circular consecutiveness modulo 26
            diff = abs(ords[a]-ords[b])
            return diff == 25 or diff == 27 or diff == (-25)%32?
Actually simpler use modular difference.
def cons_val(x,y):
x_val,y_val = ords[x],ords[y]
diff_mod=(x_val-y_val)%26return diff_mod==or diff_mod==25Similar.
def cons_idx(i,j):
x,y=ords[i],ords[j]
diff_mod=(x-y)%return diff_mod==or diff_mod==But careful negative Python modulus positive.
def cons_val(x,y):
diff_mod=(x-y)%return diff_mod==or diff_mod==Let's define outside class easier.
def cons_val(x,y):
diff_mod=(x-y)%return diff_mod==or diff_mod==Now back.
def cons_idx(i,j):
x,y=ords[i],ords[j]
diff_mod=(x-y)%return diff_mod==or diff_mod==Simplify create list vals outside.
vls=[ord(c)-for cin]
n len(vls)
def con(a,b):
diff_absabs(vls[a]-vls[b])return diff_abs==or diff_abs==Better just compute absolute difference ignoring circular initially.
def con_val(x,y):
diff_absabs(x-y)							ifdiff_abs == ordiff_abs ==returnTrueelseifdiff_abs ==returnTrueforcircular case'a'and'z'differencebetweenandisnotbutin modular terms|122-97|=butin our mapping aandza->b->...y->soanddifferenceisActually mappingandtoanddifferenceisIndeed ord('a')='b')='difference=|98-'=|Similarly ord('z')='difference=|122-'=|Socircular case corresponds differenceofbecauseaftercomesThus absolute differencemustbeorHence con_val(x,y):diff_absabs(x-y);returndiff_abs == ordiff_abs ==Yes.
def con_idx(i,j):return con_val(vls[i],vls[j]))
good.
good.
good.
good.
good.