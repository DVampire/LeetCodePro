class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m = len(grid)
        n = len(grid[0])
        
        row_sums = [sum(row) for row in grid]
        col_sums = [0] * n
        for r in range(m):
            for c in range(n):
                col_sums[c] += grid[r][c]
        
        total_sum = sum(row_sums)
        
        # Horizontal cuts
        s1 = 0
        prefix_vals = set()
        for r in range(m - 1):
            s1 += row_sums[r]
            for val in grid[r]:
                prefix_vals.add(val)
            s2 = total_sum - s1
            x = s1 - s2
            if x == 0: return True
            if x > 0:
                h, w = r + 1, n
                if h > 1 and w > 1:
                    if x in prefix_vals: return True
                elif h == 1 and w > 1:
                    if x == grid[0][0] or x == grid[0][n-1]: return True
                elif h > 1 and w == 1:
                    if x == grid[0][0] or x == grid[r][0]: return True
                elif h == 1 and w == 1:
                    if x == grid[0][0]: return True
        
        s2 = 0
        suffix_vals = set()
        for r in range(m - 1, 0, -1):
            s2 += row_sums[r]
            for val in grid[r]:
                suffix_vals.add(val)
            s1 = total_sum - s2
            y = s2 - s1
            if y > 0:
                h, w = m - r, n
                if h > 1 and w > 1:
                    if y in suffix_vals: return True
                elif h == 1 and w > 1:
                    if y == grid[m-1][0] or y == grid[m-1][n-1]: return True
                elif h > 1 and w == 1:
                    if y == grid[r][0] or y == grid[m-1][0]: return True
                elif h == 1 and w == 1:
                    if y == grid[m-1][0]: return True

        # Vertical cuts
        s1 = 0
        prefix_vals = set()
        for c in range(n - 1):
            s1 += col_sums[c]
            for r in range(m):
                prefix_vals.add(grid[r][c])
            s2 = total_sum - s1
            x = s1 - s2
            if x == 0: return True
            if x > 0:
                h, w = m, c + 1
                if h > 1 and w > 1:
                    if x in prefix_vals: return True
                elif h == 1 and w > 1:
                    if x == grid[0][0] or x == grid[0][c]: return True
                elif h > 1 and w == 1:
                    if x == grid[0][0] or x == grid[m-1][0]: return True
                elif h == 1 and w == 1:
                    if x == grid[0][0]: return True
        
        s2 = 0
        suffix_vals = set()
        for c in range(n - 1, 0, -1):
            s2 += col_sums[c]
            for r in range(m):
                suffix_vals.add(grid[r][c])
            s1 = total_sum - s2
            y = s2 - s1
            if y > 0:
                h, w = m, n - c
                if h > 1 and w > 1:
                    if y in suffix_vals: return True
                elif h == 1 and w > 1:
                    if y == grid[0][c] or y == grid[0][n-1]: return True
                elif h > 1 and w == 1:
                    if y == grid[0][n-1] or y == grid[m-1][n-1]: return True
                elif h == 1 and w == 1:
                    if y == grid[0][n-1]: return True
                    
        return False