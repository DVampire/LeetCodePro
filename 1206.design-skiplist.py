import random

#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
class Skiplist:

    MAX_LVL = 16
    P = 0.5

    class Node:
        def __init__(self, val: int, max_lvl: int):
            self.val = val
            self.next = [None] * max_lvl

    def __init__(self):
        self.head = self.Node(float('-inf'), self.MAX_LVL)

    def _random_level(self) -> int:
        lvl = 1
        while random.random() < self.P and lvl < self.MAX_LVL:
            lvl += 1
        return lvl

    def search(self, target: int) -> bool:
        cur = self.head
        for lvl in range(self.MAX_LVL - 1, -1, -1):
            while cur.next[lvl] is not None and cur.next[lvl].val < target:
                cur = cur.next[lvl]
        return cur.next[0] is not None and cur.next[0].val == target

    def add(self, num: int) -> None:
        lvl = self._random_level()
        new_node = self.Node(num, self.MAX_LVL)
        cur = self.head
        for i in range(self.MAX_LVL - 1, -1, -1):
            while cur.next[i] is not None and cur.next[i].val < num:
                cur = cur.next[i]
            if i < lvl:
                new_node.next[i] = cur.next[i]
                cur.next[i] = new_node

    def erase(self, num: int) -> bool:
        cur = self.head
        update = [None] * self.MAX_LVL
        for lvl in range(self.MAX_LVL - 1, -1, -1):
            while cur.next[lvl] is not None and cur.next[lvl].val < num:
                cur = cur.next[lvl]
            update[lvl] = cur
        if update[0].next[0] is None or update[0].next[0].val != num:
            return False
        node = update[0].next[0]
        for lvl in range(self.MAX_LVL):
            if update[lvl].next[lvl] == node:
                update[lvl].next[lvl] = node.next[lvl]
        return True


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end
