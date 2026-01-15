#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

from typing import List

# @lc code=start
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        # First, compute the number of alternating permutations.
        # Let dp[i][0] = number of alternating permutations of length i ending with an even number.
        # Let dp[i][1] = number of alternating permutations of length i ending with an odd number.
        # But we need total count for each starting number? Actually we can think differently.
        # We need to generate the k-th permutation lexicographically.
        # We can use a recursive approach: at each step, choose the smallest possible number that maintains the alternating property.
        # We need to know how many permutations start with a given prefix.
        # We can precompute counts using combinatorial formulas.
        
        # Observations: Alternating means parity alternates. So if we have a list of odds and evens separately.
        # Let odd_count = (n+1)//2, even_count = n//2.
        # For a permutation of length n, the parity pattern is determined by the first element's parity.
        # If first is odd, then positions: odd, even, odd, even,...
        # If first is even, then positions: even, odd, even, odd,...
        # So we can think of constructing permutations by picking numbers from the appropriate parity set at each step.
        
        # Let's define f(i, parity) = number of ways to arrange remaining numbers of appropriate parities to fill remaining positions.
        # But the counts depend on how many odds and evens are left. However, the pattern is fixed: if current position expects an odd number, we must choose from remaining odds; similarly for evens.
        # So we can precompute factorials and combinations to compute counts quickly.
        
        # However, note that the numbers are distinct from 1..n. So odds are specific numbers, evens specific numbers. The counts are not just combinations but permutations within each parity group because the order matters but constrained by alternating pattern.
        
        # Actually, once we fix the sequence of parities (alternating), we are essentially interleaving two sequences: one of odd numbers in some order and one of even numbers in some order. The total number of alternating permutations is:
        # If n is odd:
        #   If start with odd: odd_count! * even_count!
        #   If start with even: even_count! * odd_count! (same)
        # But wait: if start with odd, then pattern: odd at positions 1,3,5,... and even at 2,4,...
        # So we need to permute all odds among the odd positions and all evens among the even positions. Since positions are fixed (odd positions are all indices with same parity), the number is (number_of_odds)! * (number_of_evens)!
        # Similarly if start with even: same product.
        # However, note that if n is even, starting with odd gives odds at positions 1,3,..., n-1 (count = n/2) and evens at 2,..., n (count = n/2). Starting with even swaps the counts but product same.
        # So total alternating permutations = 2 * (odd_count! * even_count!) when both parities present? But check example n=4: odds=2 (1,3), evens=2 (2,4). Then product = 2! * 2! = 4. Multiply by 2 gives 8. Indeed there are 8 permutations as per example. For n=3: odds=2 (1,3), evens=1 (2). Product = 2! *1! =2. Multiply by 2? That would be 4 but there are only 2 permutations according to example. Wait why? Because if start with even for n=3: pattern would be even, odd, even. But there is only one even number (2). So first element could be 2. Then second must be odd: choose from {1,3}. Then third must be even but no evens left? Actually after using 2 as first and one odd as second, we have one odd left and no evens left for third position which requires even -> impossible. So starting with even for n=3 leads to zero permutations. Similarly starting with odd leads to two permutations. So total is only when starting parity matches that there are enough numbers.

# Therefore we need to consider feasibility based on counts. In general:
# Let a = number of odds required at positions that expect odds; b = number of evens required at positions that expect evens.
# For a given starting parity p (0 for even? let's define), the pattern determines how many odds and evens needed. For length n:
# If start with odd:
#   num_odd_positions = (n+1)//2
#   num_even_positions = n//2
# If start with even:
#   num_odd_positions = n//2
#   num_even_positions = (n+1)//2

# We must have num_odd_positions <= total_odds and num_even_positions <= total_evens. Otherwise zero permutations for that starting parity.

# For each feasible starting parity p, the count is C(total_odds, num_odd_positions) * C(total_evens, num_even_positions) * (num_odd_positions)! * (num_even_positions)! ? Actually once we select which odds go into odd positions (combination) and which evens go into even positions (combination), then we can arrange them independently among their respective positions in any order. That yields:
# count_p = C(odd_total, num_odd) * num_odd! * C(even_total, num_even) * num_even! 
# which simplifies to P(odd_total, num_odd) * P(even_total, num_even)
# where P(n,k)= n!/(n-k)! .

# Since we need lexicographic order across all feasible permutations regardless of starting parity? The lexicographic order considers all permutations sorted globally. So we need to consider both starting parities together sorted by first element etc.

# Approach: We'll generate permutation step by step using combinatorial counting to skip over blocks.
global_n = n
global_k = k - 1  # zero-indexed k
if global_k < 0:	return []
odds = [i for i in range(1,n+1) if i%2==1]
evens=[i for i in range(1,n+1) if i%2==0]
total_odds=len(odds)
total_evens=len(evens)
factor=[0]*101																	\factor[0]=1; for i in range(100): factor[i+1]=factor[i]*(i+1)
def factorial(x): return factor[x]
def perm(n,r): return factorial(n)//factorial(n-r) if r<= n else 0
def count_for_starting(start_is_odd):	if start_is_odd:	num_odds_needed=(global_n+1)//2; num_evens_needed=global_n//2; else:	num_odds_needed=global_n//2; num_evens_needed=(global_n+1)//2;	if total_odds<num_odds_needed or total_evens<num_evens_needed:	return 0;	return perm(total_odds,num_odds_needed)*perm(total_evens,num_evens_needed);total_valid=	count_for_starting(True)+count_for_starting(False);if global_k>=total_valid:	return [];Now decide starting parity based on counts compared to k.If count_starting_with_true > global_k => choose True else subtract and choose False.start_is_true_count=	count_for_starting(True);if global_k < start_is_true_count:	start_is_true=True; else:	start_is_true=False;	global_k-=start_is_true_count;# Now construct permutation step by stepremaining=list(range(1,n+1));parity_of_first_is_true=	start_is_true;current_position_expects_true=	parity_of_first_is_true;result=[ ];available_true_set=	sorted([x for x in remaining if x%2==1]);available_false_set=	sorted([x for x in remaining if x%2==0]);while len(result)<global_n:# Determine which set to pick from based on current_position_expects_trueset_to_pick=	available_true_set if current_position_expects_true else available_false_set;# For each candidate in sorted order compute how many permutations start with this candidate.# At this point we have remaining true count & false count.# Let rem_true_cnt =	len(available_true_set); rem_false_cnt =	len(available_false_set); After picking candidate c from set_to_pick:# For remaining positions after picking c: The next position expects opposite parity.So remaining true needed?	Let rem_len =	n - len(result)-1; After this pick,the next expected parity is not current_position_expects_true.So future pattern alternates.We can compute count per candidate as:# count =	number_of_arrangements_for_the rest given remaining true/false after removing c.# Let future_expects_true =	not current_position_expects_true;# Then future pattern length rem_len has expected parities alternating starting from future_expects_true.# Number of future arrangements =	future_count(future_expects_true,	after_c_true_cnt,	after_c_false_cnt)# where after_c_true_cnt =	true_cnt - (1 if current_position_expects_true else 0)# similarly false_cnt.We'll define a function future_count(starting_expects,	true_left,alse_left):returns number of ways given that next position expects starting_expects.# This can be computed similarly as before but now true_left/false_left may not match exactly needed numbers because some might have been used earlier.# However note that after picking some numbers,the pattern continues strictly.So let needed_t =	number_of_positions_in_future that expect true,and needed_f =	number_of_positions_in_future that expect false.Given rem_len L,and starting expectation s:# needed_t =	(L+ s? ) Actually formula: if s=True ->positions expecting true at steps offset0 , offset2,... so count =(L+(True?))//? We can compute needed_t =	sum_{i=0}^{L-1} indicator((starting_expects + i)%2==True).Similarly needed_f=L-needed_t.We require needed_t <= true_left and needed_f <= false_left.If not satisfied return0.Else return perm(true_left,
eeded_t)*perm(false_left,
eeded_f).Now iterate candidates sorted ascending.Compute per candidate its future count.If global_k <future_count => choose this candidate else subtract global_k-=future_count continue next candidate.After choosing candidate append c remove from appropriate sets.toggle current_position_expects_true.Continue.Return result.Function future_count defined inside method.Caveat: factorials up to100 since n<=100.We'll precompute factorial list.Now implement accordingly.