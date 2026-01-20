#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor:

    def __init__(self):
        # Stores characters to the left of the cursor
        self.left_stack = []
        # Stores characters to the right of the cursor in reverse order
        # Example: if text is "abc|def", left=['a','b','c'], right=['f','e','d']
        self.right_stack = []

    def addText(self, text: str) -> None:
        # Add characters to the left stack
        for char in text:
            self.left_stack.append(char)

    def deleteText(self, k: int) -> int:
        # Delete up to k characters from the left stack
        count = 0
        while k > 0 and self.left_stack:
            self.left_stack.pop()
            count += 1
            k -= 1
        return count

    def cursorLeft(self, k: int) -> str:
        # Move k characters from left stack to right stack
        while k > 0 and self.left_stack:
            self.right_stack.append(self.left_stack.pop())
            k -= 1
        return self._get_last_10()

    def cursorRight(self, k: int) -> str:
        # Move k characters from right stack to left stack
        while k > 0 and self.right_stack:
            self.left_stack.append(self.right_stack.pop())
            k -= 1
        return self._get_last_10()

    def _get_last_10(self) -> str:
        # Helper to return the last min(10, len) characters from left stack
        # Since slicing handles out of bounds gracefully, we can just slice.
        # The slice [-10:] takes the last 10 elements. If fewer than 10, it takes all.
        return "".join(self.left_stack[-10:])

# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
# @lc code=end