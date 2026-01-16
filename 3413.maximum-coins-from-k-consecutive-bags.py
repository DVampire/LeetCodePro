#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
from typing import List

class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        # Step 1: Sort the segments by left coordinate
        coins.sort(key=lambda x: x[0])
        n = len(coins)
        
        # Step 2: Precompute prefix sums of coins and lengths
        prefix_coins = [0] * (n + 1)  # total coins up to i-th segment (exclusive)
        prefix_len = [0] * (n + 1)    # total length up to i-th segment (exclusive)
        for i in range(n):
            l, r, c = coins[i]
            seg_len = r - l + 1
            prefix_coins[i+1] = prefix_coins[i] + seg_len * c
            prefix_len[i+1] = prefix_len[i] + seg_len
        
        # Step 3: Use two pointers to find maximum coins for a window of length k
        ans = 0
        j = 0  # right pointer for the window start segment
        left_offset = 0  # how many bags from the left segment are included in the window
        
        # We will slide a window of length k over the line.
        # Represent window by its start position x, and end at x + k - 1.
        # We iterate over possible start positions at segment boundaries and within segments.
        # However, we can note that optimal window will start at some segment start or end at some segment end.
        # Actually, we can consider all events: segment starts and ends.
        # But simpler: we can slide the window by moving the left boundary across segments.
        # Use two pointers to maintain the set of segments intersected by the window.
        
        # We'll iterate over each segment as the leftmost segment that the window touches.
        for i in range(n):
            l_i, r_i, c_i = coins[i]
            # The window start can be anywhere from l_i to r_i (but also before if previous segments).
            # However, we consider that the window starts at some position s, and we want to maximize coins.
            # We can think of moving s from l_i to r_i, but we only need to consider s such that window ends at some critical point.
            # Instead, we can use two pointers to maintain a sliding window of length k over the continuous line.
            
            # We'll maintain a pointer j for the leftmost segment fully or partially included.
            # We'll also maintain a variable cur_coins for the current window.
            
            # Actually, let's implement a different approach:
            # Since segments are non-overlapping, we can think of the line as intervals with coin density ci.
            # The total coins in a window is sum over intersected segments of (min(r, window_end) - max(l, window_start) + 1) * c.
            # We can slide the window by moving start across all interesting points: segment boundaries and positions k away from boundaries.
            
            # However, with constraints up to 1e9 positions, we cannot iterate over positions.
            # We need to consider events where the set of intersected segments changes. That happens when window start or end crosses a segment boundary.
            
            # Let’s define events at each li and ri+1 (since when start passes li, the segment starts contributing; when start passes ri+1, it stops contributing).
            # Similarly for end. But it's easier to think of sliding the start and using two pointers to maintain which segments are intersected.
            
            # Let’s implement a two-pointer sliding window on segments:
            # For each possible leftmost segment i, we expand right until the total length from l_i to current right segment's end >= k,
            # then calculate coins for that window starting at l_i. Then we move i forward and adjust.
            
            # However, the optimal window may not start exactly at l_i. It could start inside a segment. But note that if we shift the window within a segment without crossing boundaries,\\nthe coin count changes linearly. The maximum for a given set of intersected segments occurs when either as much as possible of high-coin segments are included or as little as low-coin segments are included? Actually, since each bag within a segment has same coin value,
the total coins is linear in the number of bags taken from each segment. So for a fixed set of intersected segments,
the total coins is linear in start position; thus maximum occurs at one of the boundaries where either start aligns with a segment boundary or end aligns with a segment boundary.\\\\Therefore optimal solution can be found by considering windows that start at each li and windows that end at each ri. Also windows that are completely inside one segment (start anywhere) but since ci constant within segment,
the maximum for that single segment is min(k, seg_len) * ci. So we need to consider windows that span multiple segments too.\\\\\\\\We can use sweep line: consider events when start crosses li or ri+1. But I think two-pointer approach on segments is feasible:\We maintain pointers i and j such that we have a contiguous block of segments from i to j (inclusive) that intersect with current window. Let’s define current_window_start = s. Then current_window_end = s + k - 1. We want to maximize total coins over s.\\\\\\\We can iterate over s being each li and also s being each ri - k + 1 (so that end aligns with ri). However there are O(n) such positions. For each candidate s,\we need compute total coins quickly using binary search and prefix sums. That's O(n log n). Acceptable given n <= 1e5.\\\\\\\So algorithm:\- Sort segments by li.\- Build prefix sums as above.\- For each candidate start s:\   * Find index i such that li <= s <= ri? Actually s may not be inside any segment; it could be in gap.\   * We need sum over all segments that intersect [s, s+k-1]. \   * Using binary search find first segment with ri >= s (i.e., intersects or after). And last segment with li <= e (e=s+k-1).\   * Then compute sum for partial overlaps on ends and full overlaps in between using prefix sums.\\\\\\\But there are many possible s? We only consider s where either s is some li or e is some ri because optimal will have either start aligned with a boundary or end aligned with a boundary. Also possibly s such that both are not boundaries but then shifting slightly won't change set? Actually if neither boundary aligns,
then shifting slightly left or right won't change which bags are included until hitting a boundary; meanwhile coin count changes linearly? Let's examine: suppose we have two adjacent segments with different ci values; if our window includes parts from both,
moving towards higher ci increases total? So maximum occurs when including as much high-coin as possible; thus optimal will align either start or end with a boundary between different ci values? Yes because if you have partial inclusion of two adjacent segments with different ci,
moving towards higher ci will increase total until you hit boundary where you lose low-coin bag and gain high-coin bag? Actually suppose left segment has ci=a, right has ci=b>a; moving right increases inclusion from right (b) and decreases from left (a), so net positive if b>a; so you would move until you cannot move further because you hit boundaries: either you lose left entirely or gain entire right? So optimal indeed at boundaries. Thus candidate starts: each li and each max(li, ri - k + 1)? Wait e must be within some interval? Actually if you want end aligned with ri: then s = ri - k + 1 must be considered if >=li? But it might be less than li? Anyway candidate starts include:
s = li for all i,
s = max(li, ri - k + 1) for all i (so that e=ri),
s = max(li, lj - k) maybe? Not needed because moving within same set only matters when crossing boundaries between different ci values; but crossing between gap (ci=0) also matters – shifting across gap changes nothing because both sides zero? Actually gap has zero coins so moving across gap doesn't affect total unless you shift into/out of a coin-containing region. So candidate starts also include positions where e equals some li-1? That's similar to aligning end with boundary before a coin region? But since gap has zero value,
it doesn't matter aligning there because coin count same before/after crossing? However crossing into coin region matters; so aligning start exactly at li ensures you capture as many coin bags as possible from that region if moving earlier would include more gap?
e.g., example where gap before high-value region – best may be starting exactly at li to include entire region without including extra zeros. So yes aligning start at li is important. Similarly aligning end at ri is important because after ri there is zero value region; so best may be ending exactly at ri to avoid zeros after. Therefore candidate starts are all li and all max(li?, actually any position where e=ri). Since e=ri => s=ri-k+1 . So candidate starts are all li and all ri-k+1 . However note that these could be many duplicates but O(2*n). Also note that these candidates might not fall within any particular interval but they might be less than min(li) etc.; however windows starting before first bag still valid because zeros before first bag don't matter but they reduce total? Starting earlier includes zeros reduces total so not optimal unless necessary to reach k bags beyond last coin bag? But if there are gaps before first coin bag,
then starting earlier reduces total because includes zeros; so optimal won't include extra zeros unless needed to fill k bags beyond last coin bag – but then starting later would reduce zeros?
e.g., if total coin bags < k then you have no choice but include zeros; but then best is maximize coin bags by aligning as much coin region as possible – which again suggests aligning boundaries with region edges. So candidate starts also include positions where e equals last coin bag's ri if needed? Already covered by e=ri candidates.\\\\\\\\\\\\Let’s implement candidate generation:
candidates = set()
candidates.add(coins[0][0]) maybe also add max(coins[0][0], coins[0][1]-k+1)? We'll generate for each i:
candidates.add(li)
candidates.add(max(li?, actually let’s add both:
candidates.add(li)
candidates.add(max(li?, maybe just compute s_start = max(li?, but ensure integer >= any valid position?
s_end_candidate = max(li?, Actually e must be integer position >=li?? Not necessarily – e could be beyond ri.) Let's compute candidates for e aligning with ri:
s_e_candidate = max(li?, actually ensure s_e_candidate <= ri? Because otherwise e > ri ? Wait e=ri => s_e_candidate = ri - k + 1 . This value may be less than li . If it's less than li , then starting there means part of window before li includes zeros (gap). That's fine because we still align end with ri . That could be optimal if there's high-value region ending at ri . So add candidate anyway even if <li . Also need ensure integer positions valid on number line (any integer). So add both:
candidates.add(l_i)
candidates.add(r_i - k + 1)\\\\\\\\\\\\But also consider windows fully inside gaps – they give zero so ignore.\\\\\\\\\\\\Now after generating candidates up to O(2*n), compute answer via function get_coins(s): return total coins in [s,s+k-1]. Need efficient computation via binary search on sorted intervals list plus prefix sums.\\\\\\\\\\\\Implementation details:
def get_coins(s): \    e=s+k-1 \    find idx_left = first index where r_i >= s \    find idx_right = last index where l_i <= e \    if idx_left > idx_right: return 0 \    ans=0 \    For idx_left..idx_right:\       compute intersection length etc using min(r_i,e)-max(l_i,s)+1 multiplied by c_i \   But doing per query O(n) worst-case leads O(n^2). Need faster via prefix sums plus handling partial ends separately via formulas using prefix sums only works for full intervals; partial ends need special handling anyway but only two ends affected per query – others full intervals sum via precomputed prefix sums of seg_len*c . However note that partial overlaps only happen on first and last intersecting interval possibly also single interval case where both partial overlaps same interval. So overall per query O(log n).\\\\\\\\\\\\How compute quickly:
i_left -> first interval intersecting [s,e]. If none return 0.
i_right -> last interval intersecting [s,e]. If none return 0 though shouldn't happen given condition above.
ow compute:
total_coins_full_intervals_sum : sum_{i=i_left+1}^{i_right-1} seg_len*c . Use prefix_coins array prefixed_sum_of_ci*seg_len already computed earlier called prefix_coins[i_right] - prefix_coins[i_left+1]. Note careful indices offset due to inclusive/exclusive definition above: prefix_coins[i] sum up to i-th interval exclusive meaning sum of intervals before index i . Since our arrays have size n+1 , prefix_coins[j] includes intervals up to j-1 inclusive . So sum from index p inclusive q inclusive is prefix_coins[q+1]-prefix_coins[p]. Good! Now handle partial intersections on left interval index=i_left : intersection length Lleft=max(l_{i_left},s), Rleft=min(r_{i_left},e); contribution Lleft* c_{i_left} ... wait actually contribution c_{i_left} per bag -> multiply by intersection length len_left=Rleft-Lleft+1 provided positive else zero similarly for right interval index=i_right : len_right=Rright-Lright+1 . Note if i_left == i_right then handle only this single interval similarly len_single intersection multiply c .\\\\\\\\\\\\\\\\Now get idx_left via binary search on sorted intervals list on r values , find first index where r>=s . get idx_right via binary search on sorted intervals list on l values , find last index where l<=e . Use bisect_left etc careful implementation\\\\\\\\\\\\\\\\Now complexity O(n log n). n up to 100k fine\\\\\\\\\\\\\\\\One more nuance: candidates may produce same answer multiple times fine\\\\\\\\\\\\\\\\Edge Cases: large numbers up to 109 use int64 ok\\\\\\\\\\\\\\\\Let’s implement now\\\\\\\\\\\\\\\\Potential issue: candidates generation may produce duplicate values outside range like negative or too large – still fine just clamp? Starting position must be integer>=?? Since coordinates positive integers starting from min coordinate maybe zero allowed?? Problem says infinite bags on number line – presumably integer coordinates infinite both directions but given constraints li>=1 so positive coordinates assume non-negative ok but zero allowed maybe not used but anyway just treat negative candidates as valid though they represent positions leftmost coordinate negative which has zero coins always because no defined coin there – okay still valid mathematically though infinite zeros beyond defined regions; however negative coordinates might lead large numbers but Python handles big ints fine however computing intersection lengths negative may cause issues like if s negative , l_i positive , intersection length computed correctly using max(l,s)-min(r,e)+... No need clamp just compute normally\\\\\\\\\\\\\\\\But better restrict candidates meaningful ones near existing intervals since far away yields zero anyway not needed\\\\\\\\\\\\\\\\So implement generate candidates list L_candidates containing all l_i and all r_i-k+1 ; then deduplicate sort maybe\\\\\\\\\\\\\\\\Then answer max(get_coins(s) for s in L_candidates ) also need consider possibility optimal windows entirely inside one big interval not aligned edges?? For example single big interval length >k ; moving within interval doesn't change number of bags taken always k bags each with same ci => constant value ; any alignment yields same answer ; thus our candidate set includes any alignment?? Not necessarily since our candidate set includes only edges ; inside interval no edge ; however any interior point yields same value as edge because constant density ; so picking edge works fine ; thus answer covers this case\\\\\\\\\\\\\\\\Also possibility windows spanning multiple intervals without aligning edges exactly ; example two intervals separated by gap ; optimal might align edge somewhere interior?? Suppose high value small interval surrounded by low value long intervals ; maybe best is center high value interval fully covered while sacrificing low value partially ; this alignment likely aligns edges with boundaries between high/low regions because otherwise shifting towards high increases profit until hitting boundary ; thus again edge alignment works\\\\\\\\\\\\\\\\Thus solution stands\\\\\\\\Now code accordingly\\\\\\\\Note import List from typing\\\\\\\\Let’s write code stepwise