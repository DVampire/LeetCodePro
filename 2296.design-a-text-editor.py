#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor:

    def __init__(self):
        # Stores characters to the left of the cursor
        self.left = []
        # Stores characters to the right of the cursor in reverse order
        # (top of stack is the character immediately to the right of cursor)
        self.right = []

    def addText(self, text: str) -> None:
        # Appending text to the left of the cursor
        for char in text:
            self.left.append(char)

    def deleteText(self, k: int) -> int:
        # Delete up to k characters from the left of the cursor
        num_to_delete = min(k, len(self.left))
        for _ in range(num_to_delete):
            self.left.pop()
        return num_to_delete

    def cursorLeft(self, k: int) -> str:
        # Move cursor left by moving chars from left stack to right stack
        num_to_move = min(k, len(self.left))
        for _ in range(num_to_move):
            self.right.append(self.left.pop())
        # Return up to 10 characters to the left of the cursor
        return "".join(self.left[-10:])

    def cursorRight(self, k: int) -> str:
        # Move cursor right by moving chars from right stack to left stack
        num_to_move = min(k, len(self.right))
        for _ in range(num_to_move):
            self.left.append(self.right.pop())
        # Return up to 10 characters to the left of the cursor
        return "".join(self.left[-10:])


# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
# @lc code=end