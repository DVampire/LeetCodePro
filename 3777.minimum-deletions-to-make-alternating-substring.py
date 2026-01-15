#
# @lc app=leetcode id=3777 lang=python3
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        s = list(s)  # Convert to list for mutability
        
        # Fenwick Tree (BIT) for transition counts
        bit = [0] * (n + 1)  # 1-indexed
        
        def update(i, delta):
            while i <= n:
                bit[i] += delta
                i += i & (-i)
        
        def query(i):
            result = 0
            while i > 0:
                result += bit[i]
                i -= i & (-i)
            return result
        
        # Initialize: transition at position i means s[i] != s[i-1]
        for i in range(1, n):
            if s[i] != s[i-1]:
                update(i, 1)
        
        result = []
        for q in queries:
            if q[0] == 1:
                j = q[1]
                
                # Update transition at position j (s[j] vs s[j-1])
                if j > 0:
                    was_diff = s[j] != s[j-1]
                    if was_diff:
                        update(j, -1)
                    else:
                        update(j, 1)
                
                # Update transition at position j+1 (s[j+1] vs s[j])
                if j + 1 < n:
                    was_diff = s[j+1] != s[j]
                    if was_diff:
                        update(j + 1, -1)
                    else:
                        update(j + 1, 1)
                
                # Flip the character
                s[j] = 'B' if s[j] == 'A' else 'A'
            else:
                l, r = q[1], q[2]
                length = r - l + 1
                # Transitions in range [l, r] = sum from l+1 to r
                transitions = query(r) - query(l)
                groups = 1 + transitions
                min_del = length - groups
                result.append(min_del)
        
        return result
# @lc code=end