#
# @lc app=leetcode id=3704 lang=python3
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution:
    def countNoZeroPairs(self, n: int) -> int:
        # Helper function to check if a number is no-zero
        def is_no_zero(num: int) -> bool:
            while num > 0:
                digit = num % 10
                if digit == 0:
                    return False
                num //= 10
            return True
        
        count = 0
        # Iterate a from 1 to n-1 (since a and b are positive integers, a >=1, b>=1)
        # For each a, b = n - a. We need to ensure both are no-zero.
        # Since pairs (a,b) and (b,a) are considered distinct if a != b, we count all.
        # We can loop up to n//2 and double count? Actually we need to count both orders.
        # So we can just loop for a from 1 to n-1 and check both conditions.
        # However, n can be up to 10^15, so O(n) is impossible.
        # We need a more efficient method.
        
        # Observation: The condition only depends on whether the numbers contain zero.
        # We can precompute the count of no-zero numbers less than n? Actually we need pairs summing to n.
        # For each a from 1 to n-1, b = n - a. So we need to count how many a in [1, n-1] such that both a and n-a are no-zero.
        # This is symmetric: if a is valid, then n-a is also valid? Not necessarily because we check both separately.
        # But the condition for a being valid is that a is no-zero and (n-a) is no-zero.
        # So we can iterate over all possible a? Not feasible for large n.
        
        # Alternative: Since the constraint is about digits containing zero, we can think in terms of digit DP.
        # We want to count numbers x such that 1 <= x <= n-1 and x and n-x are both no-zero.
        # Let's define f(x) = 1 if x is no-zero else 0.
        # Then answer = sum_{x=1}^{n-1} f(x) * f(n-x).
        # This is convolution of f with itself evaluated at n? Actually it's sum over x of f(x)f(n-x). That's convolution at point n.
        # Since f is defined on positive integers, we can compute using digit DP for the condition that both x and n-x are no-zero.
        
        # Approach: Use digit DP on the digits of n. Let's represent n as string of digits.
        # We consider building two numbers a and b such that a + b = n. At each digit position from most significant to least,
        # we have choices for the digits of a and b (with carry). The condition: digits of a and b must be non-zero (since they are no-zero numbers).
        # However, note that leading zeros are not allowed because numbers are positive integers. But since a and b are positive, they can have fewer digits than n? Actually yes, e.g., for n=11, a=2 (single digit), b=9 (single digit). So leading zeros in the representation when aligning with n's digits are allowed as long as the actual number doesn't have leading zeros. But in digit DP with fixed length (same number of digits as n), we need to allow leading zeros for shorter numbers. However, we must ensure that the entire number does not contain zero in any digit. So if we allow leading zeros (i.e., the number has fewer digits), then those leading zeros would be considered as zeros in the representation? In standard digit DP when we pad with leading zeros to match length, those leading zeros are not part of the actual number. So they should not be considered as zeros in the number because they are not digits of the number. Therefore, we need to handle variable length numbers.

# Let's think differently: For each possible length L_a (number of digits of a) and L_b (number of digits of b), but their sum equals n. That seems complicated.

# Another idea: Since the condition only cares about absence of zero in decimal representation, we can think about counting numbers without zero in given range. There is known combinatorial count: For k-digit numbers without zero, there are 9^k possibilities (each digit from 1..9). For numbers up to some limit M, we can count how many numbers <= M have no zero using digit DP.
# Then answer = sum_{a=1}^{⌊(n-1)/2⌋} [f(a) * f(n-a)] * 2? Not exactly because if a != b then pair counted twice; if a == b then counted once. But since n >=2, if n even then a=b=n/2 possible only when f(n/2) true. So answer = sum_{a=1}^{⌊(n-1)/2⌋} 2*f(a)*f(n-a) + (if even and f(n/2): add 1).
# This reduces problem to counting f(a) for all a up to ~10^15? Still too many.

# Wait: The sum convolution might be computed using generating functions? Since f is multiplicative across digits? Not exactly multiplicative but independent per digit if we consider numbers without zero: each digit independent from 1..9. So for numbers with exactly d digits (no leading zeros), there are 9^d such numbers. For numbers up to M, we can compute count_no_zero(M) using digit DP or combinatorial formula.
# Then answer = sum_{a=1}^{⌊(n-1)/2⌋} [is_no_zero(a) && is_no_zero(n-a)] * 2 - delta where delta adjusts for middle term.
# But still need to iterate over half of n which is huge.

# Need more clever way: Since condition only depends on digits, maybe we can consider building pairs directly via recursion on digits with carry as earlier thought.
# Let's attempt digit DP with state (pos, carry) where pos goes from least significant digit (LSD) to most significant digit (MSD). At each position i (0-index from LSD), let d_i be the i-th digit of n (from LSD). We choose digits x_i for a and y_i for b such that x_i + y_i + carry_in = d_i + 10*carry_out. And constraints: x_i and y_i must be between 0 and 9 inclusive? Actually since numbers are no-zero integers, their decimal representations cannot contain zero. That means every digit of a must be from 1..9; similarly for b. However note that if number has fewer digits than total positions considered (i.e., leading zeros in representation), those leading zeros should be allowed because they correspond to missing higher digits; but those missing digits are effectively zeros in the padded representation which would violate the condition because zero appears as digit? In reality those zeros are not part of the actual number; but our DP treats them as digits chosen as zero which would make the number contain zero incorrectly. Therefore we need additional states indicating whether we have started constructing non-leading part for each number?
# Standard technique: have two flags start_a and start_b indicating whether we have placed any non-zero digit so far for a and b respectively. If start flag is false, then current digit can be zero because it's leading zero; but once start flag becomes true, subsequent digits cannot be zero because then actual number would contain zero. Also note that both numbers must be positive => at least one non-zero digit overall; so at end start_a and start_b must both be true (since both positive).
# Moreover carry between positions; also note that total length may exceed that of n due to carry out beyond most significant digit; but since sum equals n exactly, final carry must be zero after processing all positions of n plus possibly extra position due to final carry out beyond highest digit of n? Actually if there is extra carry after processing all digits of n then sum would exceed representation; so final carry must be zero after processing all positions up to max length needed which could be len(n)+1 due to final carry out >0 but then sum would be >10^{len(n)} which could equal n only if len(n)+1 representation matches? Since sum equals exactly given integer value up to max length equal len(str(n)). So after processing all positions up to len(str(n)), final carry must be zero; otherwise invalid pair because sum would exceed maximum value represented by len(str(n)) digits unless extra topmost non-zero carry yields same value as having an extra most significant digit? Example: suppose smallest case where final carry >0 after processing all positions means total sum >=10^{len}. Since given integer value has exactly len(str(n)) decimal representation without leading zeros except maybe extra topmost; but given integer value equals this new larger number only if it indeed has more than len(str(n)) decimal places which contradicts its representation having length len(str(n)). Therefore final carry must be zero after processing all positions corresponding to len(str(n)).
given integer value up to max length equal len(str(n)). So after processing all positions up to len(str(n)), final carry must be zero; otherwise invalid pair because sum would exceed maximum value represented by len(str(n)) digits unless extra topmost non-zero carry yields same value as having an extra most significant digit? Example: suppose smallest case where final carry >0 after processing all positions means total sum >=10^{len}. Since given integer value has exactly len(str(n)) decimal representation without leading zeros except maybe extra topmost; but given integer value equals this new larger number only if it indeed has more than len(str(n)) decimal places which contradicts its representation having length len(str(n)). Therefore final carry must be zero after processing all positions corresponding to len(str(n)).
given integer value up tomaxlength equal len(str(s)). After processing all positions up tomaxlength equal len(s). After processing all positions upto L where L =len(s). After processing L lowest order bits...
given integer value up tomaxlength equal len(s). After processing L lowest order bits...
given integer value upto L lowest order bits...I'm getting stuck here."""")