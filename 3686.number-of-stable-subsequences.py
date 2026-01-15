#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
from typing import List

class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums)
        # dp[i][j][k]: number of stable subsequences ending at index i (considering first i+1 elements) 
        # with parity j of last element (0: even, 1: odd) and length of consecutive same parity at end k (1 or 2)
        # Actually we need to count all stable subsequences, not just ending at i.
        # We can maintain cumulative counts.
        # Let's define:
        # total = total number of stable subsequences so far.
        # For each parity p (0/1), we keep:
        # cnt[p][1]: number of stable subsequences ending with parity p and having exactly 1 consecutive p at the end.
        # cnt[p][2]: number of stable subsequences ending with parity p and having exactly 2 consecutive p at the end.
        # When we add a new element with parity cur, we need to update counts.
        # For each existing subsequence, we can append current element to it, forming new subsequence.
        # However, we must avoid creating three consecutive same parity.
        # So we consider transitions:
        # If we append to a subsequence ending with parity other than cur -> new subsequence ends with cur, length 1.
        # If we append to a subsequence ending with parity cur and length 1 -> new subsequence ends with cur, length 2.
        # If we append to a subsequence ending with parity cur and length 2 -> NOT allowed because that would make three consecutive same parity.
        # Also, the empty subsequence is not counted in total? The problem likely counts non-empty subsequences? 
        # But examples: nums=[1,3,5] output 6. All non-empty subsets except [1,3,5]. Total subsets = 2^3 -1 =7. Excluding one gives 6. So they count non-empty subsequences? Actually they list [1],[3],[5],[1,3],[1,5],[3,5]. That's all non-empty except [1,3,5]. So they count non-empty subsequences. But is empty considered stable? Usually subsequences can be empty but problem says "A subsequence is stable if..." maybe empty is trivially stable but not counted? In example they didn't include empty. So we count only non-empty stable subsequences.
        # We can start with total = 0 and cnt arrays zero.
        cnt = [[0]*3 for _ in range(2)]  # indices: parity p, length l (1 or 2). We'll use l=1 and l=2 only; l=0 unused.
        total = 0
        for x in nums:
            p = x % 2
            # New subsequences consisting of only current element: length 1, parity p.
            new_len1 = 1  # just the single element
            # Now consider appending current element to existing stable subsequences that remain stable after appending.
            # For each existing subsequence that ends with parity other than p: we can append.
            other = 1 - p
            # Number of such subsequences: those ending with other parity (any length) because appending a different parity resets consecutive count to 1.
            from_other = (cnt[other][1] + cnt[other][2]) % MOD
            new_len1 += from_other
            new_len1 %= MOD
            # For existing subsequences ending with same parity and length exactly 1: appending gives length 2.
            from_same_len1 = cnt[p][1]
            new_len2 = from_same_len1 % MOD
            # Cannot append to those with length 2 because that would cause three consecutive same parity.
            
            # Update total: add all new stable subsequences created by appending current element?
            # But careful: total currently includes all stable subsequences using previous elements. 
            # The new ones are those formed by taking existing ones and appending x, plus the single-element one.
            new_total = (new_len1 + new_len2) % MOD   # new_len1 includes single element and those from other; new_len2 are those from same len1.
            total = (total + new_total) % MOD
            
            # Update cnt for parity p:
            cnt[p][1] = (cnt[p][1] + new_len1) % MOD   ? Wait: need to replace or add?
            cnt[p][2] = (cnt[p][2] + new_len2) % MOD
            
            ## Actually careful: The existing cnt[p][*] represent counts of subsequences ending at previous indices. 
            ## When we add current element x, we create new subsequences that end at x. The old ones that ended earlier still exist as separate subsequences; they are still counted in total and still have their own endings. So cnt should accumulate the newly created ones that end at current index? But our dp definition should be for endings up to current index? Actually typical dynamic programming for counting subsequences often uses dp[i] as number of valid subsequences ending at i. Then total sum over i plus maybe empty? Here we want total number over all possible endings. So we can maintain cnt as cumulative over all indices? Let's think differently.
            ## Let dp_even_one be number of stable subsequences that end at some processed element with even last element and exactly one even at end (i.e., last two elements have different parity or it's single even). Similarly dp_even_two for two consecutive evens at end. Same for odd.
            ## When processing a new element x with parity p:
            ## New sequences ending at x:
                ## Single element x -> contributes to dp_p_one += 1
                ## Sequences formed by appending x to any sequence ending with other parity -> contributes to dp_p_one += dp_other_one + dp_other_two
                ## Sequences formed by appending x to sequences ending with same parity and length one -> contributes to dp_p_two += dp_p_one_old (the old value before update)" This is tricky because dp_p_one may be updated already within this step if we update in place. We need temporary variables.""