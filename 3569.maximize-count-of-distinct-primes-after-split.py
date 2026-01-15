#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
from typing import List
import math

class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        # Precompute primes up to 100000 using sieve
        MAX_VAL = 100000
        is_prime = [True] * (MAX_VAL + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(math.sqrt(MAX_VAL)) + 1):
            if is_prime[i]:
                step = i
                start = i * i
                for j in range(start, MAX_VAL + 1, step):
                    is_prime[j] = False
        
        n = len(nums)
        # Count distinct primes in entire array initially
        # We'll maintain two frequency maps: one for prefix (from left to right) and one for suffix (from right to left)
        # But we need to answer after each update: we need to compute max over k of (distinct primes in prefix up to k-1 + distinct primes in suffix from k to n-1)
        # Let dp_prefix[i] be number of distinct primes in nums[0..i-1] (i elements). Actually we need distinct counts as we extend.
        # We can maintain a global frequency map of primes in the whole array.
        # For each split point k, the distinct primes in prefix are those that appear at least once in [0..k-1]; similarly suffix.
        # We can precompute for each prime, the first and last occurrence? That might be heavy.
        # Alternative: For each index i, we can know how many distinct primes are in prefix ending at i and suffix starting at i.
        # But updates change values, so we need dynamic structure.
        # Since n up to 5e4 and queries up to 5e4, we need O(log n) per query.
        # We can use segment tree that stores for each segment:
        #   - set of distinct primes? That would be too large.
        # Instead, note that the total number of distinct primes across all numbers is limited because each number <=1e5 and there are about 9592 primes up to 1e5.
        # But storing sets per segment would still be heavy.
        # Another approach: The sum of distinct primes in prefix + suffix equals (distinct primes in prefix) + (distinct primes in suffix). 
        # For a given split k, let A be set of primes in prefix, B be set of primes in suffix. Then total = |A| + |B|.
        # Note that A and B may overlap. Overlap is counted twice. So total = |A ∪ B| + |A ∩ B| = total_distinct_in_whole_array + |A ∩ B|.
        # Because |A ∪ B| is the set of all primes present in the whole array (since every prime appears somewhere). Actually not necessarily: a prime might appear only in prefix or only in suffix. But A ∪ B is exactly the set of primes that appear anywhere in the array. So |A ∪ B| is constant for the whole array regardless of split? Wait, if a prime appears only in prefix and not suffix, it's still in A ∪ B. Similarly only in suffix. So indeed A ∪ B is the set of all primes that appear anywhere in nums. That set does not depend on split k. Let total_distinct = |A ∪ B| for whole array.
        # Then total = total_distinct + |A ∩ B|. So maximizing total is equivalent to maximizing the size of intersection between prefix primes and suffix primes.
        # Because total_distinct is fixed for the current array state.
        # So we need to choose k such that the number of distinct primes that appear both in prefix [0..k-1] AND suffix [k..n-1] is maximized.
        # Let’s denote for each prime p, let first[p] be first index where p appears, last[p] be last index where p appears.
        # Then p is in both prefix and suffix for a split k if first[p] < k <= last[p]. Because p must appear at least once in prefix (so first[p] <= k-1) and at least once in suffix (so last[p] >= k). Actually condition: exists i < k with nums[i]=p and exists j >= k with nums[j]=p. That means first[p] < k and last[p] >= k. So condition: first[p] < k <= last[p].
        # Therefore, for each prime p, it contributes to intersection for all k such that first[p]+1 <= k <= last[p]. That's a range [first[p]+1, last[p]].
        # So the problem reduces to: given a collection of intervals (one per distinct prime), find the integer point k (1<=k<n) covered by the maximum number of intervals. The answer for query is total_distinct + max_coverage.
        # This is classic interval point maximum overlap problem. We can use sweep line: for each interval [l,r], add +1 at l and -1 at r+1. Then sweep over possible k from 1 to n-1 to get coverage count at each k.
        # However, we have updates that change nums values. Each update changes at most two numbers: old value at idx and new value at idx. So we need to update intervals for primes affected by those changes.
        # We need to maintain:
        #   - For each prime p, its first occurrence index and last occurrence index across current nums.
        #   - Then generate intervals as described.
        #   - Maintain a data structure that supports adding an interval, removing an interval, and querying maximum coverage over integer points 1..n-1.
        # Since n up to 5e4 and queries up to 5e4, we can use difference array with Fenwick tree or segment tree that supports range add and point query? Actually we need point queries after range updates to get coverage at each point; but we need maximum over all points. We can use segment tree with lazy propagation that stores max value over range after range additions. Because adding an interval corresponds to adding +1 on range [l,r]. Removing an interval corresponds to adding -1 on same range. Then the maximum value over points 1..n-1 gives max_coverage.
        # So plan:
        #   - Precompute prime list up to 100000.
        #   - Maintain arrays first_occ and last_occ for each prime (size ~9592). But indices are up to n=5e4; we can store default first_occ = INF, last_occ = -INF.
        #   - Also maintain frequency count per prime? Actually we need existence across indices; but if multiple occurrences, first and last suffice because any occurrence between them ensures interval condition holds regardless of interior presence? Wait condition requires existence both before and after split. If there are multiple occurrences but all before split or all after split then it doesn't count. So indeed only first and last matter because if there's any occurrence before split and any after split then p contributes. The existence before split requires at least one occurrence index < k; existence after requires at least one index >= k. So having first < k <= last ensures both conditions because first < k means there exists an occurrence before split (since first < k implies index=first < k), and last >= k means there exists an occurrence after or at split? Actually condition needs existence after split meaning index >= k; but if last == k then index ==k which is part of suffix? Suffix starts at index k; so yes includes nums[k]. So condition is first < k <= last works because if first < k then there's an occurrence strictly before split; if last >=k then there's an occurrence at or after split. However note: if there's exactly one occurrence at position idx, then first=last=idx. Then condition becomes idx < k <= idx which is impossible; so such prime never contributes to intersection as it cannot be both sides simultaneously. That's correct because single occurrence cannot be on both sides no matter where you split unless you allow empty? Not allowed non-empty parts; but even if you could split exactly at idx? Not allowed because parts must be non-empty; but splitting at idx would put idx into suffix? Wait suffix starts at idx; so left part ends before idx; right part includes idx; so indeed it's only on right side; not left side; so doesn't contribute intersection.
