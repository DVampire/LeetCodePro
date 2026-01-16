#
# @lc app=leetcode id=3474 lang=python3
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        word_len = n + m - 1
        
        # Initialize result array with 'a' (lexicographically smallest)
        result = ['a'] * word_len
        
        # For each position i in str1, check the constraint
        for i in range(n):
            # Extract the substring of length m starting at position i
            if i + m <= word_len:
                current_substring = ''.join(result[i:i+m])
                
                if str1[i] == 'T':
                    # Must equal str2
                    if current_substring != str2:
                        # Try to make it equal to str2
                        for j in range(m):
                            result[i + j] = str2[j]
                else:  # str1[i] == 'F'
                    # Must NOT equal str2
                    if current_substring == str2:
                        # Need to change at least one character
                        # Change the last character to the next character if possible
                        # or previous if it's 'z'
                        pos = i + m - 1
                        if pos < word_len:
                            if result[pos] < 'z':
                                result[pos] = chr(ord(result[pos]) + 1)
                            else:
                                result[pos] = chr(ord(result[pos]) - 1)
                        else:
                            # This shouldn't happen due to initialization
                            return ""
            else:
                # Not enough characters left for substring of length m
                return ""
        
        # Verify the solution satisfies all constraints
        for i in range(n):
            if i + m <= word_len:
                substring = ''.join(result[i:i+m])
                if str1[i] == 'T' and substring != str2:
                    return ""
                if str1[i] == 'F' and substring == str2:
                    return ""
            else:
                return ""
        
        return ''.join(result)
        
# @lc code=end