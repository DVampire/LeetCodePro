#
# @lc app=leetcode id=1670 lang=python3
#
# [1670] Design Front Middle Back Queue
#

# @lc code=start
from collections import deque

class FrontMiddleBackQueue:

    def __init__(self):
        # Maintain two deques such that len(left) == len(right) or len(right) == len(left) + 1
        self.left = deque()
        self.right = deque()

    def _balance(self):
        # Helper to maintain the size invariant
        if len(self.left) > len(self.right):
            self.right.appendleft(self.left.pop())
        elif len(self.right) > len(self.left) + 1:
            self.left.append(self.right.popleft())

    def pushFront(self, val: int) -> None:
        self.left.appendleft(val)
        self._balance()

    def pushMiddle(self, val: int) -> None:
        if len(self.left) == len(self.right):
            self.right.appendleft(val)
        else:
            self.left.append(val)
        # pushMiddle logic naturally maintains the invariant, but _balance() could be called safely

    def pushBack(self, val: int) -> None:
        self.right.append(val)
        self._balance()

    def popFront(self) -> int:
        if not self.right:
            return -1
        if not self.left:
            res = self.right.popleft()
        else:
            res = self.left.popleft()
        self._balance()
        return res

    def popMiddle(self) -> int:
        if not self.right:
            return -1
        if len(self.left) == len(self.right):
            res = self.left.pop()
        else:
            # If len(right) > len(left), the middle is the first element of right
            res = self.right.popleft()
        self._balance()
        return res

    def popBack(self) -> int:
        if not self.right:
            return -1
        res = self.right.pop()
        self._balance()
        return res


# Your FrontMiddleBackQueue object will be instantiated and called as such:
# obj = FrontMiddleBackQueue()
# obj.pushFront(val)
# obj.pushMiddle(val)
# obj.pushBack(val)
# param_4 = obj.popFront()
# param_5 = obj.popMiddle()
# param_6 = obj.popBack()
# @lc code=end