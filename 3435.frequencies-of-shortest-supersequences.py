#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        from collections import deque, defaultdict
        
        # Convert words to a set for faster lookup
        word_set = set(words)
        n = len(words)
        
        # We'll use BFS to find all shortest supersequences
        # State: (mask of covered words, character frequency tuple, current string)
        queue = deque([(0, tuple([0]*26), "")])
        visited = set()
        visited.add((0, tuple([0]*26)))
        
        # To store results: set of frequency tuples
        result_freqs = set()
        target_mask = (1 << n) - 1  # All words covered
        min_length = float('inf')
        
        while queue:
            mask, freq_tuple, current_str = queue.popleft()
            
            # If we've found a solution and current length exceeds min_length, stop
            if mask == target_mask:
                if len(current_str) < min_length:
                    min_length = len(current_str)
                    result_freqs.clear()
                    result_freqs.add(freq_tuple)
                elif len(current_str) == min_length:
                    result_freqs.add(freq_tuple)
                continue
            
            # If current length already equals or exceeds min_length, skip
            if len(current_str) >= min_length and min_length != float('inf'):
                continue
            
            # Try adding each character a-z
            for c in 'abcdefghijklmnopqrstuvwxyz':
                new_str = current_str + c
                new_freq = list(freq_tuple)
                new_freq[ord(c) - ord('a')] += 1
                new_freq_tuple = tuple(new_freq)
                
                # Check which words are now satisfied
                new_mask = mask
                for i, word in enumerate(words):
                    if (mask >> i) & 1:  # Already covered
                        continue
                    if self.is_subsequence(word, new_str):
                        new_mask |= (1 << i)
                
                # If this state hasn't been visited
                state_key = (new_mask, new_freq_tuple)
                if state_key not in visited:
                    visited.add(state_key)
                    queue.append((new_mask, new_freq_tuple, new_str))
        
        # Convert to canonical form by sorting to eliminate permutations
        canonical_results = set()
        for freq in result_freqs:
            canonical_results.add(tuple(sorted(freq, reverse=True)))
        
        # Map back to original frequency format
        final_results = set()
        freq_to_canonical = {}
        
        for freq in result_freqs:
            canonical = tuple(sorted(freq, reverse=True))
            if canonical not in freq_to_canonical:
                freq_to_canonical[canonical] = freq
                final_results.add(freq)
        
        return [list(freq) for freq in final_results]
    
    def is_subsequence(self, word, string):
        # Check if word is a subsequence of string
        i = 0  # pointer for word
        for char in string:
            if i < len(word) and char == word[i]:
                i += 1
        return i == len(word)
# @lc code=end