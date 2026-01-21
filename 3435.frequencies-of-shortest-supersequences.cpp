#
# @lc app=leetcode id=3435 lang=cpp
#
# [3435] Frequencies of Shortest Supersequences
#
# @lc code=start
class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        int n = words.size();
        
        // Collect unique characters
        set<char> uniqueChars;
        for (const string& word : words) {
            for (char c : word) {
                uniqueChars.insert(c);
            }
        }
        
        // BFS level by level
        // Map from state (word progress) to set of frequency arrays
        map<vector<int>, set<vector<int>>> currentLevel;
        vector<int> initial(n, 0);
        vector<int> initialFreq(26, 0);
        currentLevel[initial].insert(initialFreq);
        
        while (!currentLevel.empty()) {
            // Check if any state is complete
            set<vector<int>> completeFreqs;
            for (const auto& [state, freqs] : currentLevel) {
                bool allComplete = true;
                for (int idx : state) {
                    if (idx < 2) {
                        allComplete = false;
                        break;
                    }
                }
                if (allComplete) {
                    for (const auto& freq : freqs) {
                        completeFreqs.insert(freq);
                    }
                }
            }
            
            if (!completeFreqs.empty()) {
                return vector<vector<int>>(completeFreqs.begin(), completeFreqs.end());
            }
            
            // Generate next level
            map<vector<int>, set<vector<int>>> nextLevel;
            for (const auto& [state, freqs] : currentLevel) {
                for (char c : uniqueChars) {
                    vector<int> newState = state;
                    for (int i = 0; i < n; i++) {
                        if (state[i] < 2 && words[i][state[i]] == c) {
                            newState[i]++;
                        }
                    }
                    
                    for (const auto& freq : freqs) {
                        vector<int> newFreq = freq;
                        newFreq[c - 'a']++;
                        nextLevel[newState].insert(newFreq);
                    }
                }
            }
            
            currentLevel = nextLevel;
        }
        
        return {};
    }
};
# @lc code=end