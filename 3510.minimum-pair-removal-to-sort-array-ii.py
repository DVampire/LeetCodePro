#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
import heapq
from typing import List

class Node:
    def __init__(self, val: int, min_idx: int):
        self.val = val
        self.min_idx = min_idx
        self.id = 0
        self.prev = None
        self.next = None

# @lc code=end
class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0
        
        nodes = []
        id_counter = 0
        id_to_node = {}
        for i, val in enumerate(nums):
            node = Node(val, i)
            node.id = id_counter
            id_counter += 1
            id_to_node[node.id] = node
            nodes.append(node)
        
        for i in range(n - 1):
            nodes[i].next = nodes[i + 1]
            nodes[i + 1].prev = nodes[i]
        
        # Compute initial violations
        violations = 0
        cur = nodes[0]
        while cur.next:
            if cur.val > cur.next.val:
                violations += 1
            cur = cur.next
        
        if violations == 0:
            return 0
        
        # Initialize priority queue
        pq = []
        cur = nodes[0]
        while cur.next:
            s = cur.val + cur.next.val
            heapq.heappush(pq, (s, cur.min_idx, cur.id, cur.next.id))
            cur = cur.next
        
        ops = 0
        while violations > 0:
            # Find valid minimum pair
            while pq:
                s, minidx, lid, rid = heapq.heappop(pq)
                if lid not in id_to_node or rid not in id_to_node:
                    continue
                node_l = id_to_node[lid]
                node_r = id_to_node[rid]
                if node_l.next != node_r:
                    continue
                # Valid pair found
                break
            else:
                # No more pairs, should not happen if violations > 0
                return ops
            
            # Update violations delta
            delta = 0
            p = node_l.prev
            if p:
                delta -= 1 if p.val > node_l.val else 0
            delta -= 1 if node_l.val > node_r.val else 0
            nxt = node_r.next
            if nxt:
                delta -= 1 if node_r.val > nxt.val else 0
            
            new_val = node_l.val + node_r.val
            if p:
                delta += 1 if p.val > new_val else 0
            if nxt:
                delta += 1 if new_val > nxt.val else 0
            
            violations += delta
            
            # Create new node
            new_node = Node(new_val, min(node_l.min_idx, node_r.min_idx))
            new_node.id = id_counter
            id_counter += 1
            id_to_node[new_node.id] = new_node
            
            # Relink
            new_node.prev = p
            new_node.next = nxt
            if p:
                p.next = new_node
            if nxt:
                nxt.prev = new_node
            
            # Deactivate old nodes
            del id_to_node[lid]
            del id_to_node[rid]
            
            # Push new pairs
            if p:
                news = p.val + new_node.val
                heapq.heappush(pq, (news, p.min_idx, p.id, new_node.id))
            if nxt:
                news = new_node.val + nxt.val
                heapq.heappush(pq, (news, new_node.min_idx, new_node.id, nxt.id))
            
            ops += 1
        
        return ops