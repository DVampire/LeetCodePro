#
# @lc app=leetcode id=3474 lang=python3
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        L = n + m - 1
        res = [None] * L
        fixed = [False] * L
        
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    if res[i + j] is not None and res[i + j] != str2[j]:
                        return ""
                    res[i + j] = str2[j]
                    fixed[i + j] = True
        
        for i in range(L):
            if res[i] is None:
                res[i] = 'a'
        
        for i in range(n - 1, -1, -1):
            if str1[i] == 'F':
                match = True
                for j in range(m):
                    if res[i + j] != str2[j]:
                        match = False
                        break
                if match:
                    changed = False
                    for j in range(m - 1, -1, -1):
                        if not fixed[i + j]:
                            original = res[i + j]
                            for char_code in range(ord(original) + 1, ord('z') + 1):
                                res[i + j] = chr(char_code)
                                # Since we only need to break the match for str1[i] == 'F',
                                # and we are moving right to left, 'a' is usually best,
                                # but here we just need ANY char that isn't str2[j].
                                if res[i + j] != str2[j]:
                                    changed = True
                                    break
                            if changed: break
                    if not changed:
                        return ""
        
        # Final validation pass to ensure lexicographical changes didn't break previous F constraints
        # Actually, the greedy approach from right to left for F constraints should be checked
        for i in range(n):
            sub = "".join(res[i:i+m])
            if str1[i] == 'T' and sub != str2: return ""
            if str1[i] == 'F' and sub == str2: return ""
            
        return "".join(res)
# @lc code=end