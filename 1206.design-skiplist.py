#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#
import random

# @lc code=start
class Skiplist:
    class Node:
        def __init__(self, val: int, level: int):
            """
            Create a skip list node.
            :param val: Value stored.
            :param level: Highest index this node participates in.
                          Number of forward pointers = level + 1.
            """
            self.val = val
            self.next = [None] * (level + 1)

    def __init__(self):
        """
        Initialize an empty skiplist.
        Maximum number of layers is set to 16,
        enough for up to ~65k elements.
        """
        self._MAX_LEVEL = 16
        # Head sentinel with maximum possible height
        self.head = self.__class__.Node(-1, self._MAX_LEVEL - 1)
        # Current highest used layer index
        self.level = 0

    def _random_level(self) -> int:
        """
        Generate a random height for a new node.
        Each additional layer has probability 0.5.
        Returns an integer between 0 and _MAX_LEVEL-1 inclusive.
        """
        lvl = 0
        while random.random() < 0.5 and lvl < self._MAX_LEVEL - 1:
            lvl += 1
        return lvl

    def search(self, target: int) -> bool:
        """
        Returns true if target exists in skiplist.
        """
        cur = self.head
        # Traverse from highest layer down to layer 0
        for i in range(self.level, -1, -1):
            # Move forward on current layer while next node's value < target
            while cur.next[i] and cur.next[i].val < target:
                cur = cur.next[i]
        # Now cur is largest node < target on layer 0
        cur = cur.next[0]
        return cur is not None and cur.val == target

    def add(self, num: int) -> None:
        """
        Insert a new element into skiplist.
        Duplicates are allowed.
        """
        # Predecessor nodes on each layer where insertion will happen
        prevs = [None] * self._MAX_LEVEL
        cur = self.head
        # Find predecessors on each layer
        for i in range(self.level, -1, -1):
            while cur.next[i] and cur.next[i].val < num:
                cur = cur.next[i]
            prevs[i] = cur
        
        # Generate random height for new node
        new_lvl = self._random_level()
        
        # If new height exceeds current highest used layer,
        # fill predecessors above old height with head
        if new_lvl > self.level:
            for i in range(self.level + 1, new_lvl + 1):
                prevs[i] = self.head
            self.level = new_lvl

        # Create new node
        newNode = self.__class__.Node(num, new_lvl)
        
        # Insert into all layers up to its own height
        for i in range(new_lvl + 1):
            newNode.next[i] = prevs[i].next[i]
            prevs[i].next[i] = newNode

    def erase(self, num: int) -> bool:
        """
        Remove one occurrence of `num`.
        Returns True if removed successfully,
        False otherwise.
        """
        prevs = [None] * self._MAX_LEVEL
        cur = self.head
        # Find predecessors on each layer
        for i in range(self.level, -1, -1):
            while cur.next[i] and cur.next[i].val < num:
                cur = cur.next[i]
            prevs[i] = cur

        # Candidate to delete – first occurrence >=num on layer0
        cand = cur.next[0]
        
        # If not found or not matching exactly
        if cand is None or cand.val != num:
            return False

        cand_lvl = len(cand.next) - 1   # Highest index where cand appears
        
        # Unlink cand from all layers where it exists
        for i in range(cand_lvl + 1):
            # Normally prevs[i].next[i] equals cand,
            # but just skip mismatch safely.
            if prevs[i].next[i] != cand:
                continue
            prevs[i].next[i] = cand.next[i]

        # Possibly reduce highest used layer
        while self.level > 0 and self.head.next[self.level] is None:
            self.level -= 1

        return True
# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end