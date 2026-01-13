#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#
# @lc code=start
import random

class Node:
    def __init__(self, val, level):
        self.val = val
        self.forward = [None] * (level + 1)

class Skiplist:

    def __init__(self):
        self.max_level = 16
        self.p = 0.5
        self.head = Node(-1, self.max_level)
        self.level = 0
    
    def _random_level(self):
        level = 0
        while random.random() < self.p and level < self.max_level:
            level += 1
        return level

    def search(self, target: int) -> bool:
        current = self.head
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].val < target:
                current = current.forward[i]
        current = current.forward[0]
        return current is not None and current.val == target

    def add(self, num: int) -> None:
        update = [None] * (self.max_level + 1)
        current = self.head
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].val < num:
                current = current.forward[i]
            update[i] = current
        
        new_level = self._random_level()
        
        if new_level > self.level:
            for i in range(self.level + 1, new_level + 1):
                update[i] = self.head
            self.level = new_level
        
        new_node = Node(num, new_level)
        
        for i in range(new_level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def erase(self, num: int) -> bool:
        update = [None] * (self.max_level + 1)
        current = self.head
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].val < num:
                current = current.forward[i]
            update[i] = current
        
        current = current.forward[0]
        
        if current is None or current.val != num:
            return False
        
        for i in range(self.level + 1):
            if update[i].forward[i] != current:
                break
            update[i].forward[i] = current.forward[i]
        
        while self.level > 0 and self.head.forward[self.level] is None:
            self.level -= 1
        
        return True


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end