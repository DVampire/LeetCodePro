#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor:

    def __init__(self):
        # Stack to store characters to the left of the cursor
        self.left = []
        # Stack to store characters to the right of the cursor (top is closest to cursor)
        self.right = []

    def addText(self, text: str) -> None:
        # O(len(text)) - Add characters to the left stack
        self.left.extend(list(text))

    def deleteText(self, k: int) -> int:
        # O(k) - Remove characters from the left stack
        count = 0
        while k > 0 and self.left:
            self.left.pop()
            k -= 1
            count += 1
        return count

    def cursorLeft(self, k: int) -> str:
        # O(k) - Move cursor left by shifting characters from left stack to right stack
        while k > 0 and self.left:
            self.right.append(self.left.pop())
            k -= 1
        # Return last min(10, len) characters to the left of the cursor
        return "".join(self.left[-10:])

    def cursorRight(self, k: int) -> str:
        # O(k) - Move cursor right by shifting characters from right stack to left stack
        while k > 0 and self.right:
            self.left.append(self.right.pop())
            k -= 1
        # Return last min(10, len) characters to the left of the cursor
        return "".join(self.left[-10:])


# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
# @lc code=end