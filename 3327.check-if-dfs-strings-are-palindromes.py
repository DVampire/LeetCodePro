#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        
        # Build adjacency list
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[parent[i]].append(i)
        
        # Sort children for each node
        for i in range(n):
            children[i].sort()
        
        # Build global DFS string and track positions
        dfs_str = []
        start = [0] * n
        end = [0] * n
        
        def dfs(x):
            start[x] = len(dfs_str)
            for child in children[x]:
                dfs(child)
            dfs_str.append(s[x])
            end[x] = len(dfs_str)
        
        dfs(0)
        
        # Convert to string
        dfs_string = ''.join(dfs_str)
        m = len(dfs_string)
        
        # Polynomial rolling hash
        MOD = 10**9 + 7
        BASE = 31
        
        # Forward hash
        fwd_hash = [0] * (m + 1)
        pow_base = [1] * (m + 1)
        for i in range(m):
            fwd_hash[i + 1] = (fwd_hash[i] * BASE + ord(dfs_string[i])) % MOD
            pow_base[i + 1] = (pow_base[i] * BASE) % MOD
        
        # Backward hash
        bwd_hash = [0] * (m + 1)
        for i in range(m):
            bwd_hash[i + 1] = (bwd_hash[i] * BASE + ord(dfs_string[m - 1 - i])) % MOD
        
        def get_hash_range(hash_arr, l, r):
            return (hash_arr[r] - hash_arr[l] * pow_base[r - l]) % MOD
        
        answer = []
        for i in range(n):
            l, r = start[i], end[i]
            
            # Forward hash
            fwd = get_hash_range(fwd_hash, l, r)
            
            # Backward hash
            bwd = get_hash_range(bwd_hash, m - r, m - l)
            
            answer.append(fwd == bwd)
        
        return answer
# @lc code=end