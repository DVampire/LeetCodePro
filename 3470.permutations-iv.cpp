#
# @lc app=leetcode id=3470 lang=cpp
#
# [3470] Permutations IV
#
# @lc code=start
class Solution {
public:
    vector<int> permute(int n, long long k) {
        const long long INF = 2e15;
        
        // Precompute factorials with overflow protection
        vector<long long> fact(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (fact[i - 1] > INF / i) {
                fact[i] = INF;
            } else {
                fact[i] = fact[i - 1] * i;
            }
        }
        
        // Separate odd and even numbers into sets
        set<int> odd_set, even_set;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) odd_set.insert(i);
            else even_set.insert(i);
        }
        
        vector<int> result;
        int start_parity = -1; // -1: not determined, 0: even, 1: odd
        
        for (int pos = 0; pos < n; pos++) {
            vector<int> candidates;
            
            if (start_parity == -1) {
                // First position: try all numbers in sorted order
                for (int c : odd_set) candidates.push_back(c);
                for (int c : even_set) candidates.push_back(c);
                sort(candidates.begin(), candidates.end());
            } else {
                // Later positions: only try numbers with required parity
                int req_parity = (start_parity + pos) % 2;
                if (req_parity == 1) {
                    for (int c : odd_set) candidates.push_back(c);
                } else {
                    for (int c : even_set) candidates.push_back(c);
                }
            }
            
            bool found = false;
            for (int c : candidates) {
                int c_parity = c % 2;
                int sp = (pos == 0) ? c_parity : start_parity;
                
                // Calculate remaining counts after placing c
                int new_odd = (int)odd_set.size() - (c_parity == 1 ? 1 : 0);
                int new_even = (int)even_set.size() - (c_parity == 0 ? 1 : 0);
                
                // Count positions needing odd/even from pos+1 to n-1
                int odd_needed = 0, even_needed = 0;
                for (int i = pos + 1; i < n; i++) {
                    if ((sp + i) % 2 == 1) odd_needed++;
                    else even_needed++;
                }
                
                // Calculate number of valid permutations
                long long count = 0;
                if (odd_needed == new_odd && even_needed == new_even) {
                    long long a = fact[new_odd], b = fact[new_even];
                    if (a <= INF / b) {
                        count = a * b;
                    } else {
                        count = INF;
                    }
                }
                
                if (count >= k) {
                    result.push_back(c);
                    if (c_parity == 1) odd_set.erase(c);
                    else even_set.erase(c);
                    if (pos == 0) start_parity = c_parity;
                    found = true;
                    break;
                } else {
                    k -= count;
                }
            }
            
            if (!found) return {};
        }
        
        return result;
    }
};
# @lc code=end