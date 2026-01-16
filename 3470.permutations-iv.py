#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        # Separate odd and even numbers
        odds = [i for i in range(1, n+1) if i % 2 == 1]
        evens = [i for i in range(1, n+1) if i % 2 == 0]
        
        # For alternating permutations, we can start with either odd or even
        # Pattern 1: odd, even, odd, even, ...
        # Pattern 2: even, odd, even, odd, ...
        
        def factorial(x):
            result = 1
            for i in range(1, x+1):
                result *= i
            return result
        
        # Count how many valid permutations for each pattern
        count_pattern1 = factorial(len(odds)) * factorial(len(evens))
        count_pattern2 = factorial(len(evens)) * factorial(len(odds))
        
        total_count = count_pattern1 + count_pattern2
        
        if k > total_count:
            return []
        
        # Generate the k-th permutation
        def get_permutation(elements, index):
            # Get the index-th permutation of elements
            if not elements:
                return []
            
            factorial_val = factorial(len(elements) - 1)
            idx = index // factorial_val
            remainder = index % factorial_val
            
            selected = elements[idx]
            remaining = elements[:idx] + elements[idx+1:]
            
            return [selected] + get_permutation(remaining, remainder)
        
        if k <= count_pattern1:
            # Pattern 1: start with odd
            odd_perm = get_permutation(odds, (k-1) // factorial(len(evens)))
            even_perm = get_permutation(evens, (k-1) % factorial(len(evens)))
            
            result = []
            max_len = max(len(odd_perm), len(even_perm))
            for i in range(max_len):
                if i < len(odd_perm):
                    result.append(odd_perm[i])
                if i < len(even_perm):
                    result.append(even_perm[i])
            return result
        else:
            # Pattern 2: start with even
            k -= count_pattern1
            even_perm = get_permutation(evens, (k-1) // factorial(len(odds)))
            odd_perm = get_permutation(odds, (k-1) % factorial(len(odds)))
            
            result = []
            max_len = max(len(even_perm), len(odd_perm))
            for i in range(max_len):
                if i < len(even_perm):
                    result.append(even_perm[i])
                if i < len(odd_perm):
                    result.append(odd_perm[i])
            return result
# @lc code=end