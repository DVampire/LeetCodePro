#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        result = []
        
        for l, r in queries:
            substring = s[l:r+1]
            t = '1' + substring + '1'
            n = len(t)
            
            original_count = s.count('1')
            max_count = original_count
            
            # Find all blocks of '1's surrounded by '0's
            ones_blocks = []
            i = 1
            while i < n - 1:
                if t[i] == '1' and t[i-1] == '0':
                    j = i
                    while j < n - 1 and t[j] == '1':
                        j += 1
                    if t[j] == '0':
                        ones_blocks.append((i, j-1))
                    i = j
                else:
                    i += 1
            
            for i1, j1 in ones_blocks:
                t_prime = list(t)
                for k in range(i1, j1+1):
                    t_prime[k] = '0'
                
                # Find all blocks of '0's surrounded by '1's
                zeros_blocks = []
                i = 1
                while i < n - 1:
                    if t_prime[i] == '0' and t_prime[i-1] == '1':
                        j = i
                        while j < n - 1 and t_prime[j] == '0':
                            j += 1
                        if t_prime[j] == '1':
                            zeros_blocks.append((i, j-1))
                        i = j
                    else:
                        i += 1
                
                for i2, j2 in zeros_blocks:
                    final = list(t_prime)
                    for k in range(i2, j2+1):
                        final[k] = '1'
                    
                    modified_substring = ''.join(final[1:n-1])
                    modified_s = s[:l] + modified_substring + s[r+1:]
                    new_count = modified_s.count('1')
                    max_count = max(max_count, new_count)
            
            result.append(max_count)
        
        return result
# @lc code=end