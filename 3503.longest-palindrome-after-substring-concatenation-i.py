#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        # We need to consider all possible substrings from s and t, concatenated.
        # Since lengths are <=30, total possible substrings O(n^2) each => ~900 each.
        # We can generate all substrings for s and t, store them in sets or list.
        # Then we need to find the longest palindrome formed by concatenating one substring from s and one from t (in order).
        # However, checking palindrome for each concatenated string would be O(L) where L up to 60, and combinations up to ~900*900 = 810k. That's acceptable (810k * 60 = 48.6M operations). But we can optimize.
        # Alternatively, we can think of the palindrome as having a center. But given constraints, brute force is fine.
        # Steps:
        # 1. Generate all substrings of s and t (including empty substring?). The problem says possibly empty substrings. So we need to consider empty substring as well.
        # 2. For each substring a from s (including empty), each substring b from t (including empty), form concat = a + b.
        # 3. Check if concat is palindrome, record max length.
        # However, there are many combinations: (len(s)+1)*len(s)/2 +1 for s? Actually number of non-empty substrings is n*(n+1)/2. Including empty adds 1. So total substrings per string: n*(n+1)/2 + 1. For n=30, that's 465+1=466. So combinations: 466*466 = ~217k. That's even less.
        # Checking palindrome for each concat of length up to 60: O(L). So total operations ~217k * 60 = 13M, which is fine.
        # Implementation:
        def is_pal(x):
            return x == x[::-1]
        
        # Generate all substrings including empty
        def all_substrings(string):
            n = len(string)
            subs = [""]  # include empty
            for i in range(n):
                for j in range(i+1, n+1):
                    subs.append(string[i:j])
            return subs
        
        subs_s = all_substrings(s)
        subs_t = all_substrings(t)
        
        best = 0
        for a in subs_s:
            for b in subs_t:
                cand = a + b
                if is_pal(cand):
                    best = max(best, len(cand))
        return best

# @lc code=end