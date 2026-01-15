#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
class Solution:
    def specialPalindrome(self, n: int) -> int:
        # Helper function to check if a number is special palindrome
        def is_special(num_str):
            # Count occurrences of each digit (0-9)
            cnt = [0] * 10
            for ch in num_str:
                d = ord(ch) - ord('0')
                cnt[d] += 1
            # Check palindrome condition
            if num_str != num_str[::-1]:
                return False
            # Check digit frequency condition: for each digit k, cnt[k] must be either 0 or k
            for k in range(1, 10):  # digit 0 cannot appear because k times, but 0 times is allowed. However, if digit 0 appears, it must appear exactly 0 times? Actually condition: every digit k in the number appears exactly k times. So if digit 0 appears, it would need to appear exactly 0 times, which is impossible. So digit 0 cannot appear at all.
                if cnt[k] != 0 and cnt[k] != k:
                    return False
            # Check digit 0: must not appear (since cannot appear exactly 0 times while present)
            if cnt[0] > 0:
                return False
            return True
        
        # Start searching from n+1 upwards
        candidate = n + 1
        while True:
            s = str(candidate)
            if is_special(s):
                return candidate
            candidate += 1
# @lc code=end