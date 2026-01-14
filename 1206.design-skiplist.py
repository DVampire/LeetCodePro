#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
import random

class Skiplist:

    class Node:
        def __init__(self, val, level):
            self.val = val
            self.forward = [None] * (level + 1)
    
    def __init__(self):
        self.max_level = 16
        self.p = 0.5
        self.level = 0
        self.head = self.Node(-1, self.max_level)
    
    def _random_level(self):
        lvl = 0
        while random.random() < self.p and lvl < self.max_level:
            lvl += 1
        return lvl
    
    def search(self, target: int) -> bool:
        curr = self.head
        for i in range(self.level, -1, -1):
            while curr.forward[i] and curr.forward[i].val < target:
                curr = curr.forward[i]
        curr = curr.forward[0]
        return curr is not None and curr.val == target
    
    def add(self, num: int) -> None:
        update = [None] * (self.max_level + 1)
        curr = self.head
        
        for i in range(self.level, -1, -1):
            while curr.forward[i] and curr.forward[i].val < num:
                curr = curr.forward[i]
            update[i] = curr
        
        new_level = self._random_level()
        
        if new_level > self.level:
            for i in range(self.level + 1, new_level + 1):
                update[i] = self.head
            self.level = new_level
        
        new_node = self.Node(num, new_level)
        for i in range(new_level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node
    
    def erase(self, num: int) -> bool:
        update = [None] * (self.max_level + 1)
        curr = self.head
        
        for i in range(self.level, -1, -1):
            while curr.forward[i] and curr.forward[i].val < num:
                curr = curr.forward[i]
            update[i] = curr
        
        curr = curr.forward[0]
        
        if curr is None or curr.val != num:
            return False
        
        for i in range(self.level + 1):
            if update[i].forward[i] != curr:
                break
            update[i].forward[i] = curr.forward[i]
        
        while self.level > 0 and self.head.forward[self.level] is None:
            self.level -= 1
        
        return True


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end