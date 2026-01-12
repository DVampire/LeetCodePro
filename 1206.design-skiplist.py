import random

#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
class Node:
    __slots__ = 'val', 'right', 'down'
    def __init__(self, val=-1, right=None, down=None):
        self.val = val
        self.right = right
        self.down = down

class Skiplist:
    def __init__(self):
        # Initialize with a dummy head node
        self.head = Node()

    def search(self, target: int) -> bool:
        curr = self.head
        while curr:
            # Move right as far as possible
            while curr.right and curr.right.val < target:
                curr = curr.right
            # Check if found
            if curr.right and curr.right.val == target:
                return True
            # Move down to the next level
            curr = curr.down
        return False

    def add(self, num: int) -> None:
        # Track the path of predecessors
        nodes = []
        curr = self.head
        while curr:
            while curr.right and curr.right.val < num:
                curr = curr.right
            nodes.append(curr)
            curr = curr.down
        
        down_node = None
        should_insert = True
        # Insert from bottom up using the predecessors path
        while should_insert and nodes:
            prev = nodes.pop()
            prev.right = Node(num, prev.right, down_node)
            down_node = prev.right
            # 50% chance to promote to a higher level
            should_insert = random.random() < 0.5
        
        # If we still need to promote but ran out of levels, create a new level
        if should_insert:
            self.head = Node(-1, Node(num, None, down_node), self.head)

    def erase(self, num: int) -> bool:
        curr = self.head
        found = False
        while curr:
            while curr.right and curr.right.val < num:
                curr = curr.right
            # If found at this level, remove it and continue to lower levels
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