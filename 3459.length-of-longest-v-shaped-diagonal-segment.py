#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

from typing import List

# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        # Directions: (dr, dc) for diagonal moves.
        # We have four diagonal directions:
        # 1. down-right: (1, 1)
        # 2. down-left: (1, -1)
        # 3. up-right: (-1, 1)
        # 4. up-left: (-1, -1)
        dirs = [(1,1), (1,-1), (-1,1), (-1,-1)]
        # For each direction, we can precompute longest straight segments that follow the sequence.
        # But we need to consider segments that can have at most one clockwise 90-degree turn.
        # A clockwise 90-degree turn from one diagonal direction to another:
        # Let's define mapping from current direction to possible next direction after a clockwise turn.
        # For example, from down-right (DR) turning clockwise 90 degrees gives down-left (DL) or up-right (UR)?
        # Actually, diagonal directions are at 45 degrees. A 90-degree turn (clockwise) changes both row and column signs?
        # Let's think: starting direction vector (dr, dc). Rotating 90 degrees clockwise gives (dc, -dr).
        # Because rotation matrix for 90 degrees clockwise is [0, 1; -1, 0]. So (dr, dc) -> (dc, -dr).
        # Check: DR (1,1) -> (1, -1) which is DL? Wait (dc, -dr) = (1, -1) indeed DL.
        # But DL is not necessarily a diagonal direction? Yes DL is (1,-1) which is one of our dirs.
        # Similarly, DL (1,-1) -> (-1,-1) which is UL? Actually (-dr? no: dc=-1, -dr=-(-? wait compute):
        # For DL: dr=1, dc=-1 => (dc,-dr)=(-1,-(??)) I think I made mistake: rotation matrix for 90 deg clockwise is [[0,1],[-1,0]]. So vector [dr;dc] becomes [dc; -dr]. So for DL=(1,-1): new dr = dc = -1, new dc = -dr = -(-?) wait dr=1 so -dr = -(-?) no dr= positive? Let's compute step by step:
        # Let v = [dr; dc]. R*v = [[0,1],[-1,0]] * [dr; dc] = [dc; -dr]. So new_dr = dc, new_dc = -dr.
        # For DR: dr=1,dc=1 => new_dr=1, new_dc=-(-?) Actually new_dc=-dr=-(-?) No new_dc=-dr => -(-?) I'm mixing signs.
        # Let's just compute with numbers:
        # DR: dr=+1, dc=+1 -> new_dr=+1? Wait new_dr=dc=+?, new_dc=-dr=-? I'm getting confused.

# Better approach: Instead of deriving formula manually for each direction mapping,
# we can enumerate the four diagonal directions and define clockwise turn mapping by checking which other diagonal direction is obtained by rotating the vector by 90 degrees clockwise.
# Since our directions are only diagonals with components ±±,
# we can compute the rotated vector and see which of the four it matches.
# But note that rotating a diagonal vector by 90 degrees gives a vector that is orthogonal to original and has same magnitude but not necessarily diagonal? Actually rotating a diagonal vector by 90 degrees yields a vector that is also diagonal? Let's test: DR=(+,+). Rotate clockwise 90 deg gives (+,-)? That's DL? Wait rotate (+ +) yields (+,-)? Actually rotation matrix [[0,1],[-2?, let's do proper math.
# Standard rotation matrix for +90° clockwise is [[0,-? Actually there are two conventions. In computer graphics with y-axis pointing down? In typical coordinate system where x increases to right and y increases down? LeetCode grid uses rows increasing downward and columns increasing right. That's like standard Cartesian but y flipped? We'll treat row as y and column as x. Then moving down increases row index. So vector components are (dy/dr?, dx/dc?). We'll keep as dr and dc.
# We can think of directions as vectors in row-col space. Clockwise rotation of a vector in this space corresponds to swapping components and changing sign of one depending on orientation. Since we only care about which of the four diagonal directions we end up with after rotation,
# we can manually define mapping:
# From DR(++): rotating clockwise gives DL(+-). Because turning right from a line at 45° slope downward right leads to downward left.
# From DL(+-): rotating clockwise gives UL(--). Because turning right from downward left leads to upward left.
# From UL(--): rotating clockwise gives UR(-+). Because turning right from upward left leads to upward right.
# From UR(-+): rotating clockwise gives DR(++). Because turning right from upward right leads to downward right.

    def get_next_dir_clockwise(self,d):
mapping = {"DR":"DL","DL":"UL","UL":"UR","UR":"DR"} but need indices.
dirs_indexed = [(+?,?), let's assign indices:
dirs[0]=(+ +)
dirs[2]=(- +)
dirs[3]=(- -)
dirs[4]=(+ ? wait we have four dirs list above but I didn't order them systematically. Let's define dirs list as:
dirs=[( + + ),( + - ),( - + ),( - -,)] in that order maybe DR,Dl?,UR?,UL?? Let's fix once."
def get_next_dir_idx(didx):
mapping={0:?, etc}" but easier to compute rotation formula programmatically: given dr/dc compute rotated dr'=dc , rotated dc'=-dr . Then see which index in dirs matches sign pattern exactly because magnitude remains sqrt2 but sign matters."
def rotate_clockwise(dr/dc): return dc,-dr . Then compare with dirs list."
i.e., new_dir=(dc,-dr). Then find index in dirs where pair equals that or maybe we need to allow both components non-zero but they will be ±± because original dr/dc are ±± so rotated also ±± indeed because swapping and negating one yields same set of signs."
e.g., DR=(+,+) => rotated=(+,+)??? Wait compute rotated:(+,+) -> new_dr=+=?? Actually rotate_clockwise(dr/+,dc/+) returns (+??? no dr=+,dc/+ so rotated dr'=+=?? I'm mixing numbers again. Let's do concrete numbers:
dr/+,dc/+ both equal + . Then rotated dr'=+=?? I'll use actual integers: dr/+,dc/+ both equal + . Then rotated dr'==??? No I'm thinking too much. Let me write python code later.