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
        # Sentinel head node for the top level
        self.head = Node(-1)

    def search(self, target: int) -> bool:
        curr = self.head
        while curr:
            while curr.right and curr.right.val < target:
                curr = curr.right
            if curr.right and curr.right.val == target:
                return True
            curr = curr.down
        return False

    def add(self, num: int) -> None:
        path = []
        curr = self.head
        # Find insertion points at each level
        while curr:
            while curr.right and curr.right.val < num:
                curr = curr.right
            path.append(curr)
            curr = curr.down
        
        down_node = None
        should_insert = True
        # Insert from bottom up based on random coin flip
        while should_insert and path:
            prev = path.pop()
            prev.right = Node(num, prev.right, down_node)
            down_node = prev.right
            should_insert = (random.random() < 0.5)
        
        # If still should insert, create a new level
        if should_insert:
            self.head = Node(-1, Node(num, None, down_node), self.head)

    def erase(self, num: int) -> bool:
        curr = self.head
        found = False
        while curr:
            # Find the predecessor at this level
            while curr.right and curr.right.val < num:
                curr = curr.right
            # If found, remove it and continue to lower levels
            if curr.right and curr.right.val == num:
                found = True
                curr.right = curr.right.right
            curr = curr.down
        return found


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end