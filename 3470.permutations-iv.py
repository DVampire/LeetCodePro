#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
from typing import List

class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        if n == 0:
            return []
        avail_odd = list(range(1, n + 1, 2))
        avail_even = list(range(2, n + 1, 2))
        fact = [1] * 101
        for i in range(1, 101):
            fact[i] = fact[i - 1] * i
        result = []
        current_k = k
        # First position: try numbers 1 to n in lex order
        picked = False
        for num in range(1, n + 1):
            is_odd_num = (num % 2 == 1)
            ro = len(avail_odd) - (1 if is_odd_num else 0)
            re = len(avail_even) - (1 if not is_odd_num else 0)
            rem_len = n - 1
            next_req_odd = not is_odd_num
            req_odd_count = (rem_len + 1) // 2 if next_req_odd else rem_len // 2
            count = fact[ro] * fact[re] if ro >= 0 and re >= 0 and ro == req_odd_count else 0
            if count >= current_k:
                result.append(num)
                if is_odd_num:
                    avail_odd.remove(num)
                else:
                    avail_even.remove(num)
                last_req_odd = next_req_odd
                picked = True
                break
            current_k -= count
        if not picked:
            return []
        # Remaining positions
        while len(result) < n:
            if last_req_odd:
                cand_list = avail_odd
                is_cand_odd = True
            else:
                cand_list = avail_even
                is_cand_odd = False
            if not cand_list:
                return []
            picked = False
            for i in range(len(cand_list)):
                num = cand_list[i]
                ro = len(avail_odd) - (1 if is_cand_odd else 0)
                re = len(avail_even) - (1 if not is_cand_odd else 0)
                rem_len = len(avail_odd) + len(avail_even) - 1
                next_req_odd = not is_cand_odd
                req_odd_count = (rem_len + 1) // 2 if next_req_odd else rem_len // 2
                count = fact[ro] * fact[re] if ro >= 0 and re >= 0 and ro == req_odd_count else 0
                if count >= current_k:
                    result.append(num)
                    del cand_list[i]
                    last_req_odd = next_req_odd
                    picked = True
                    break
                current_k -= count
            if not picked:
                return []
        return result

# @lc code=end
