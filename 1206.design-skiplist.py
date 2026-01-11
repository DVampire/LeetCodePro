#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
import random

class Node:
    def __init__(self, val, next=None, down=None):
        self.val = val
        self.next = next
        self.down = down

class Skiplist:

    def __init__(self):
        # Use a dummy head node. Value -1 is safe as 0 <= num.
        self.head = Node(-1)

    def search(self, target: int) -> bool:
        curr = self.head
        while curr:
            # Move right as much as possible at current level
            while curr.next and curr.next.val < target:
                curr = curr.next
            # Check if target is found
            if curr.next and curr.next.val == target:
                return True
            # Move down to next level
            curr = curr.down
        return False

    def add(self, num: int) -> None:
        stack = []
        curr = self.head
        # Find insertion path
        while curr:
            while curr.next and curr.next.val < num:
                curr = curr.next
            stack.append(curr)
            curr = curr.down
        
        insert = True
        down_node = None
        # Insert from bottom up based on random probability
        while insert and stack:
            prev = stack.pop()
            prev.next = Node(num, prev.next, down_node)
            down_node = prev.next
            # 50% chance to promote to a higher level
            insert = (random.random() < 0.5)
        
        # If we still need to promote but reached the top, create a new level
        if insert:
            self.head = Node(-1, Node(num, None, down_node), self.head)

    def erase(self, num: int) -> bool:
        curr = self.head
        found = False
        while curr:
            # Move right
            while curr.next and curr.next.val < num:
                curr = curr.next
            
            # If found, remove the node at this level and continue down
            if curr.next and curr.next.val == num:
                found = True
                curr.next = curr.next.next
            
            curr = curr.down
        return found


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end