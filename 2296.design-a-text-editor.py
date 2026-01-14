#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#
# @lc code=start
class TextEditor:

    def __init__(self):
        self.left = []  # Stack for characters to the left of cursor
        self.right = []  # Stack for characters to the right of cursor

    def addText(self, text: str) -> None:
        for c in text:
            self.left.append(c)

    def deleteText(self, k: int) -> int:
        deleted = 0
        while k > 0 and self.left:
            self.left.pop()
            k -= 1
            deleted += 1
        return deleted

    def cursorLeft(self, k: int) -> str:
        while k > 0 and self.left:
            self.right.append(self.left.pop())
            k -= 1
        return ''.join(self.left[-10:])

    def cursorRight(self, k: int) -> str:
        while k > 0 and self.right:
            self.left.append(self.right.pop())
            k -= 1
        return ''.join(self.left[-10:])


# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
# @lc code=end