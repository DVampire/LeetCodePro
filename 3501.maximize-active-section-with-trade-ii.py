#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        # Precompute prefix sums of '1's
        prefix_ones = [0] * (n + 1)
        for i in range(n):
            prefix_ones[i + 1] = prefix_ones[i] + (1 if s[i] == '1' else 0)
        
        def count_ones(l, r):
            return prefix_ones[r + 1] - prefix_ones[l]
        
        def solve_query(l, r):
            # Augment with '1' at both ends
            # The augmented '1's don't contribute to the count
            
            # Count initial active sections in substring
            initial_count = count_ones(l, r)
            
            # If substring is all '1's or all '0's, no trade improves it
            if initial_count == (r - l + 1) or initial_count == 0:
                return initial_count
            
            # Create the augmented string: '1' + s[l:r+1] + '1'
            # But we work with indices in original string
            # The augmented string has length (r - l + 1) + 2
            
            augmented_length = (r - l + 1) + 2
            
            # Find all segments of '1's and '0's in augmented string
            # We simulate the augmented string: 1 + s[l..r] + 1
            
            # Parse the augmented string into segments
            segments = []  # list of (char, count)
            
            # First '1'
            segments.append(('1', 1))
            
            # Process s[l..r]
            if l <= r:
                i = l
                while i <= r:
                    char = s[i]
                    count = 0
                    j = i
                    while j <= r and s[j] == char:
                        count += 1
                        j += 1
                    segments.append((char, count))
                    i = j
            
            # Last '1'
            segments.append(('1', 1))
            
            # Count initial active sections in augmented string (excluding augmented '1's)
            initial_active = count_ones(l, r)
            
            max_active = initial_active
            
            # Try all possible trades
            # Find segments of '1's that are surrounded by '0's
            for i in range(1, len(segments) - 1):
                if segments[i][0] == '1':
                    # Check if this segment of '1's is surrounded by '0's
                    if segments[i-1][0] == '0' and segments[i+1][0] == '0':
                        # This segment of '1's can be converted to '0's
                        ones_count = segments[i][1]
                        
                        # Create new segments after converting this segment to '0's
                        # Merge with adjacent '0' segments
                        new_segments = segments[:i-1] + [('0', segments[i-1][1] + ones_count + segments[i+1][1])] + segments[i+2:]
                        
                        # Now find best segment of '0's to convert to '1's
                        best_gain = 0
                        for j in range(1, len(new_segments) - 1):
                            if new_segments[j][0] == '0':
                                # This segment of '0's can be converted to '1's
                                zeros_count = new_segments[j][1]
                                gain = zeros_count
                                best_gain = max(best_gain, gain)
                        
                        # The new count of active sections
                        new_active = initial_active - ones_count + best_gain
                        max_active = max(max_active, new_active)
            
            return max_active
        
        result = []
        for l, r in queries:
            result.append(solve_query(l, r))
        
        return result
# @lc code=end