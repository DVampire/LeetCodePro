#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10**9 + 7
        
        def to_base_b(num_str, base):
            if num_str == "0":
                return [0]
            
            num = list(num_str)
            result = []
            
            while not (len(num) == 1 and num[0] == '0'):
                remainder = 0
                new_num = []
                for digit in num:
                    current = remainder * 10 + int(digit)
                    quotient = current // base
                    remainder = current % base
                    if new_num or quotient > 0:
                        new_num.append(str(quotient))
                result.append(remainder)
                num = new_num if new_num else ['0']
            
            return result[::-1]
        
        def count(num_str, base):
            if num_str == "0":
                return 0
            
            digits = to_base_b(num_str, base)
            n = len(digits)
            
            memo = {}
            
            def dp(pos, last, tight, started):
                if pos == n:
                    return 1 if started else 0
                
                key = (pos, last, tight, started)
                if key in memo:
                    return memo[key]
                
                limit = digits[pos] if tight else base - 1
                result = 0
                
                for d in range(0, limit + 1):
                    new_tight = tight and (d == limit)
                    new_started = started or (d > 0)
                    
                    if not new_started:
                        result = (result + dp(pos + 1, -1, new_tight, False)) % MOD
                    else:
                        if last == -1 or d >= last:
                            result = (result + dp(pos + 1, d, new_tight, True)) % MOD
                
                memo[key] = result
                return result
            
            return dp(0, -1, True, False)
        
        def subtract_one(s):
            if s == "0":
                return "-1"
            digits = list(s)
            i = len(digits) - 1
            while i >= 0 and digits[i] == '0':
                digits[i] = '9'
                i -= 1
            if i >= 0:
                digits[i] = str(int(digits[i]) - 1)
            result = ''.join(digits).lstrip('0')
            return result if result else '0'
        
        l_minus_1 = subtract_one(l)
        
        count_r = count(r, b)
        count_l_minus_1 = count(l_minus_1, b) if l_minus_1 != "-1" else 0
        
        return (count_r - count_l_minus_1 + MOD) % MOD
# @lc code=end