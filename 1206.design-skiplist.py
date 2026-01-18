#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
import random

class Node:
    __slots__ = 'val', 'right', 'down'
    def __init__(self, val, right=None, down=None):
        self.val = val
        self.right = right
        self.down = down

class Skiplist:

    def __init__(self):
        # Initialize with a sentinel node representing the top-left of the skiplist
        self.head = Node(-1)

    def search(self, target: int) -> bool:
        curr = self.head
        while curr:
            # Move right as far as possible at the current level
            while curr.right and curr.right.val < target:
                curr = curr.right
            # If found, return True
            if curr.right and curr.right.val == target:
                return True
            # Move down to the next level
            curr = curr.down
        return False

    def add(self, num: int) -> None:
        # Track the nodes where we move down to insert the new value at multiple levels
        stack = []
        curr = self.head
        while curr:
            while curr.right and curr.right.val < num:
                curr = curr.right
            stack.append(curr)
            curr = curr.down
        
        insert = True
        down_node = None
        while insert and stack:
            prev = stack.pop()
            # Insert the new node to the right of the predecessor
            prev.right = Node(num, prev.right, down_node)
            # Update the down_node for the next level up
            down_node = prev.right
            # Decide whether to promote to the next level
            insert = (random.random() < 0.5)
        
        # If we need to add a new level beyond the current height
        if insert:
            self.head = Node(-1, Node(num, None, down_node), self.head)

    def erase(self, num: int) -> bool:
        curr = self.head
        found = False
        while curr:
            # Move right to find the predecessor of the target value
            while curr.right and curr.right.val < num:
                curr = curr.right
            # If target found at this level, remove it
            if curr.right and curr.right.val == num:
                found = True
                curr.right = curr.right.right
                # Continue searching/removing in lower levels to remove the whole tower
            curr = curr.down
        return found

# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end