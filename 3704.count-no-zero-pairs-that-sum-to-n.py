#
# @lc app=leetcode id=3704 lang=python3
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        s = str(n)
        D = len(s)
        digits = [int(c) for c in s[::-1]]  # digits[i] = digit at position i (LSB to MSB)
        
        # dp[(carry, a_cont, b_cont)] = count
        # a_cont: whether a's representation can continue (True) or has ended (False)
        # b_cont: same for b
        dp = {(0, True, True): 1}
        
        for pos in range(D):
            n_pos = digits[pos]
            new_dp = {}
            
            for (carry, a_cont, b_cont), cnt in dp.items():
                # Determine choices for a_pos
                if a_cont:
                    # At pos=0, a_pos must be 1-9 (to ensure a >= 1)
                    # At pos>0, a_pos can be 0 (end) or 1-9 (continue)
                    a_choices = range(1, 10) if pos == 0 else range(0, 10)
                else:
                    a_choices = [0]  # a has ended
                
                # Determine choices for b_pos
                if b_cont:
                    b_choices = range(1, 10) if pos == 0 else range(0, 10)
                else:
                    b_choices = [0]  # b has ended
                
                for a_pos in a_choices:
                    for b_pos in b_choices:
                        total = a_pos + b_pos + carry
                        if total % 10 != n_pos:
                            continue
                        carry_out = total // 10
                        
                        # Update continuation flags
                        new_a_cont = a_cont and (a_pos > 0)
                        new_b_cont = b_cont and (b_pos > 0)
                        
                        key = (carry_out, new_a_cont, new_b_cont)
                        new_dp[key] = new_dp.get(key, 0) + cnt
            
            dp = new_dp
        
        # Sum contributions where final carry is 0
        return sum(cnt for (carry, _, _), cnt in dp.items() if carry == 0)
# @lc code=end