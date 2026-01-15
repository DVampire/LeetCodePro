#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10**9 + 7
        # Convert l and r to base b digits (list of integers)
        def to_base(s: str) -> list:
            # s is decimal string
            num = int(s)
            if num == 0:
                return [0]
            digits = []
            while num > 0:
                digits.append(num % b)
                num //= b
            return digits[::-1]  # most significant first
        
        L = to_base(l)
        R = to_base(r)
        
        # DP function to count numbers <= given digits (as list) and non-decreasing
        # We'll use digit DP with state (pos, last_digit, tight, started)
        # But note: numbers can have leading zeros? Actually we are counting numbers in base b representation.
        # The representation does not have leading zeros. So we need to handle numbers with fewer digits.
        # We can count all numbers with up to len(digits) digits, non-decreasing, and then subtract those with leading zeros? Actually we want numbers from 0 to N inclusive.
        # But l and r are positive? l and r are strings of decimal digits representing positive integers? Constraints: l and r consist only of digits and no leading zeros. So l >= 1.
        # However, we need to count from 0 to N for DP convenience, then compute f(R) - f(L-1).
        # So we need a function f(N_digits) that returns count of numbers from 0 to N (inclusive) that have non-decreasing digits in base b.
        # But note: representation of 0 is "0" which has one digit and is non-decreasing (single digit). It should be included if we consider from 0.
        # We'll compute f(N) for N being integer represented by digits list.
        
        def count_up_to(digits):
            n = len(digits)
            # dp[pos][last_digit][tight][started]
            # pos: from 0 to n (we process from most significant)
            # last_digit: from 0 to b-1 (the previous digit chosen)
            # tight: whether the prefix matches exactly the prefix of digits so far
            # started: whether we have started placing non-leading-zero digits (i.e., if we have chosen a non-zero digit yet). This is needed because leading zeros are allowed in the number representation? Actually the number's representation does not have leading zeros. For example, number 5 in base 10 is "5", not "05". So when counting numbers with exactly certain number of digits, we cannot allow leading zeros. But we are counting all numbers from 0 up to N inclusive. Numbers with fewer digits than n are allowed; they are effectively represented with leading zeros padded to length n? We can treat them as having leading zeros but those zeros do not affect non-decreasing condition because they are not part of the actual representation? However, when considering non-decreasing property, we only consider the actual digits without leading zeros. For example, number 5 in base 10 is "5", which is non-decreasing. If we pad it as "005", the leading zeros would break non-decreasing because 0 <= 0 <=5? Actually if we include leading zeros in the digit sequence, then the sequence [0,0,5] is non-decreasing (0<=0<=5). But that would incorrectly include numbers like 50? Wait no. For number 5, its representation without leading zeros is just [5]. Leading zeros are not part of the representation. So when we count numbers with up to n digits, we need to consider numbers with fewer digits as well. One approach: count all numbers with exactly k digits (non-leading zero) for k from 1 to n-1, plus those with exactly n digits that are <= N.
            # Alternatively, use DP that allows skipping leading zeros: started flag indicates whether we have placed a non-zero digit yet. If not started, then we can either skip (place a zero that doesn't count as a digit) or start with a digit from 1..max_digit. And once started, we must follow non-decreasing rule.
            
            memo = {}
            def dfs(pos, last_digit, tight, started):
                if pos == n:
                    return 1 if started else 1  # If never started, that means the number is zero (all skipped). Zero is considered valid? Yes, single digit zero is non-decreasing. So return 1.
                key = (pos, last_digit, tight, started)
                if key in memo:
                    return memo[key]
                max_digit = digits[pos] if tight else b-1
                total = 0
                for d in range(0, max_digit+1):
                    next_tight = tight and (d == max_digit)
                    if not started:
                        if d == 0:
                            # skip this digit (still not started)
                            total += dfs(pos+1, last_digit, next_tight, False)
                        else:
                            # start with d
                            total += dfs(pos+1, d, next_tight, True)
                    else:
                        if d >= last_digit:
                            total += dfs(pos+1, d, next_tight, True)
                        else:
                            continue
                memo[key] = total % MOD
                return memo[key]
            
            return dfs(0, -1, True, False) % MOD
        
        def subtract_one(digits):
			# compute digits for N-1
			num = int(l) - 1
			if num <   : actually better convert l to integer subtract one then convert back
		We'll do outside
	Actually easier: compute f(R) - f(L-1). So need L-1 in base b.We already have L as list for l; but L-1 might have fewer digits.Let's compute integer values.Because lengths up to  100 decimal digits -> integer conversion may be huge but Python handles big integers fine.So compute integer values of l and r using int(l), int(r). Then compute L_minus_one = int(l)-1.Convert L_minus_one to base b list similarly.If L_minus_one <   : but l >=   so L_minus_one >=   .So implement function f(num_str) that computes count up to num_str decimal string.But our count_up_to takes list of base b digits. So helper function g(num_int): convert num_int to base b list and call count_up_to.We'll do:def cnt(s):    num = int(s)    if num <   : actually negative? no s >=   .    dig = [] if num ==   else ...    return count_up_to(dig) % MODThen result = cnt(r) - cnt(str(int(l)- ) ) mod MODBut careful: cnt includes zero? Yes includes zero. Since l>= , subtracting cnt(L-) includes zero.. Actually we want [l,r] inclusive so f(r)-f(l-) where f(x)=count of numbers from   inclusive up to x inclusive that satisfy condition.So compute total = cnt(r) - cnt(str(int(l)- ) ) mod MODIf result negative add MOD.Let's implement cnt(s).Edge case when s == " " ? l length>= , but l could be " ". Actually constraints say l consists only of digits and no leading zeros so l>= . So fine.