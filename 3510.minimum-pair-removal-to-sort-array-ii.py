#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
from heapq import heappush, heappop
from typing import List

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0
        # We'll use a min-heap of tuples (sum of pair, left index, right index)
        # But we need to be able to remove pairs that are no longer valid (when adjacent pairs change).
        # We'll use a doubly linked list to represent the array and maintain pointers.
        # Each node stores value, left, right, and an id for invalidation.
        # We'll also maintain a set of active indices.
        # However, we can simulate using a heap and lazy deletion.
        # Approach: Use a heap to always get the pair with minimum sum (and leftmost).
        # When we merge two nodes, we create a new node with sum, update neighbors.
        # We push the new possible pairs (left with new, new with right) into heap.
        # We also need to mark the old nodes as deleted so we skip them when popped.
        # We'll keep arrays for value, left, right.
        value = nums[:]
        left = [i-1 for i in range(n)]
        right = [i+1 for i in range(n)]
        deleted = [False] * n
        # Min-heap: (sum, left_index, right_index)
        heap = []
        # Initialize heap with all adjacent pairs
        for i in range(n-1):
            s = value[i] + value[i+1]
            heappush(heap, (s, i, i+1))
        ops = 0
        while heap:
            s, i, j = heappop(heap)
            if deleted[i] or deleted[j]:
                continue
            # Check if i and j are still adjacent (they should be because we only push valid pairs)
            # But due to merges, they might not be direct neighbors? Actually our updates ensure that.
            # However we also need to ensure that right[i] == j and left[j] == i.
            if right[i] != j or left[j] != i:
                continue
            # Perform merge: replace pair (i,j) with new node at index i? Actually we can reuse one index and mark other as deleted.
            # Let's reuse i as the merged node. Update value[i] = s.
            value[i] = s
            deleted[j] = True
            ops += 1
            # Update links: new node's left is left[i], new node's right is right[j].
            l = left[i]
            r = right[j]
            if l != -1:
                right[l] = i
                left[i] = l
                # Push new pair (l, i) if both are active (l not deleted). Since l is not deleted by construction.
                heappush(heap, (value[l] + value[i], l, i))
            else:
                left[i] = -1
            if r != n:
                left[r] = i
                right[i] = r
                # Push new pair (i, r)
                heappush(heap, (value[i] + value[r], i, r))
            else:
eright[i] = n
            # After merging, check if array is non-decreasing? Actually we need to continue until array is non-decreasing.
            # But we cannot check entire array each time. Instead we can keep track of violations.
            # However the problem asks for minimum number of operations to make array non-decreasing. 
            # The operations are forced: always merge the minimum sum pair. So we just simulate until no more merges? Not exactly: we stop when array is non-decreasing.
            # But note: after each merge we should check if the array becomes non-decreasing. If yes break early.
            # Checking entire array each time would be O(n^2) worst case. But maybe we can maintain a count of inversions?
            # Alternatively we can simulate until only one element remains? That would always be sorted but not minimal operations necessarily? Actually merging reduces length and may fix violations. The problem says minimum number of operations needed; but operations are predetermined by the rule (always pick min sum pair). So it's deterministic; we just simulate until array is non-decreasing. So after each operation we can check if current active list is sorted. To check efficiently we can maintain a flag or count of adjacent inversions. Let's keep a set of indices where nums[i] > nums[next(i)]. When merging we update these counts. Complexity O(n log n). Let's implement checking after each merge by traversing from head? That could be O(n) per operation leading to O(n^2). Instead maintain a variable that indicates whether sorted. Actually after merging only local neighborhood changes; so we can update violations around merged node. Let's keep a boolean variable 'sorted' that becomes true when no adjacent inversion exists. We'll maintain a count of inversions. Initially compute number of indices i such that value[i] > value[right[i]] where both active and right exists.  After merging nodes i and j into new node at i, we need to update inversions involving left neighbor l and right neighbor r. We'll decrement inversions for pairs that were previously considered but now changed. Then increment new inversions if any. Steps: 1. Before merging remove inversions involving (l,i), (i,j), (j,r) from count.  2. After merging add inversions involving (l,i_new) and (i_new,r).  Then if count becomes 0 break early. Implementation details: need functions to check if an edge exists and whether it's an inversion. Let's code accordingly. First compute initial inversion count on original list using active nodes only? Initially all nodes active; but later some become deleted. We'll compute using linked list traversal from head. Simpler: after each merge update locally as described. Let's implement helper functions: is_inversion(a,b) returns True if value[a] > value[b].  But must ensure both indices are valid and not deleted; edges are between active consecutive nodes. We'll store inversion count globally. Initialize inversion count: traverse from head while node != -1 and next exists:   if value[node] > value[right[node]] then inc count Find head: index where left == -1 At start head=0 After merges head may change if first element merged? Actually when merging pair at indices i,j; if l==-1 then head becomes i; else head unchanged	 So maintain head variable initially 0	 Update head when l==-1: head=i Now code:""""