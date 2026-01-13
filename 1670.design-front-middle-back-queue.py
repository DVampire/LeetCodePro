#
# @lc app=leetcode id=1670 lang=python3
#
# [1670] Design Front Middle Back Queue
#
# @lc code=start
from collections import deque

class FrontMiddleBackQueue:

    def __init__(self):
        self.left = deque()
        self.right = deque()

    def _rebalance(self) -> None:
        # Ensure: len(left) == len(right) or len(left) == len(right) + 1
        while len(self.left) < len(self.right):
            self.left.append(self.right.popleft())
        while len(self.left) > len(self.right) + 1:
            self.right.appendleft(self.left.pop())

    def pushFront(self, val: int) -> None:
        self.left.appendleft(val)
        self._rebalance()

    def pushMiddle(self, val: int) -> None:
        # If left has one extra, shift its last to right so insertion becomes frontmost middle
        if len(self.left) > len(self.right):
            self.right.appendleft(self.left.pop())
        self.left.append(val)
        self._rebalance()

    def pushBack(self, val: int) -> None:
        self.right.append(val)
        self._rebalance()

    def popFront(self) -> int:
        if not self.left and not self.right:
            return -1
        if self.left:
            res = self.left.popleft()
        else:
            res = self.right.popleft()
        self._rebalance()
        return res

    def popMiddle(self) -> int:
        if not self.left and not self.right:
            return -1
        res = self.left.pop()  # frontmost middle
        self._rebalance()
        return res

    def popBack(self) -> int:
        if not self.left and not self.right:
            return -1
        if self.right:
            res = self.right.pop()
        else:
            res = self.left.pop()
        self._rebalance()
        return res


# @lc code=end
