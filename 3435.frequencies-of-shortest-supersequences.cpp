#
# @lc app=leetcode id=3435 lang=cpp
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        // Step 1: Map unique characters to IDs 0..N-1
        vector<int> char_to_id(26, -1);
        vector<char> id_to_char;
        int n = 0;
        for (const string& w : words) {
            for (char c : w) {
                if (char_to_id[c - 'a'] == -1) {
                    char_to_id[c - 'a'] = n++;
                    id_to_char.push_back(c);
                }
            }
        }

        // Step 2: Build the graph and identify mandatory doubled chars (self-loops)
        // adj[i] contains j if there is a word "uv" where u->i, v->j
        // We only care about edges between distinct characters for the DAG check.
        vector<vector<int>> adj(n);
        int req_mask = 0;
        
        // To avoid duplicate edges which slow down checking
        vector<vector<bool>> has_edge(n, vector<bool>(n, false));

        for (const string& w : words) {
            int u = char_to_id[w[0] - 'a'];
            int v = char_to_id[w[1] - 'a'];
            if (u == v) {
                req_mask |= (1 << u);
            } else {
                if (!has_edge[u][v]) {
                    adj[u].push_back(v);
                    has_edge[u][v] = true;
                }
            }
        }

        vector<vector<int>> results;
        int min_popcount = 30; // Initialize with a value larger than max possible (16)

        // We iterate through all subsets of vertices that we choose to DOUBLE.
        // Let S be the mask of doubled vertices.
        // S must include req_mask.
        // The vertices NOT in S (U = full_mask ^ S) must form a DAG.
        
        // We can group masks by popcount to find shortest ones first.
        // Or just iterate 0..2^N, check validity, and keep track of min_popcount.
        
        int limit = 1 << n;
        // Group masks by popcount for efficiency? 
        // Since N <= 16, iterating all 65536 is fast. We can just store valid ones and filter min size later.
        // Or better: iterate size k from popcount(req_mask) to n.
        
        // Let's iterate all masks, check validity. If valid, update global min and store.
        
        for (int mask = 0; mask < limit; ++mask) {
            // Constraint: Must double self-loop chars
            if ((mask & req_mask) != req_mask) continue;

            int current_popcount = 0;
            // __builtin_popcount is efficient
            current_popcount = __builtin_popcount(mask);

            if (current_popcount > min_popcount) continue;

            // Check if U = (nodes NOT in mask) forms a DAG
            // Nodes in U are those where (mask >> i) & 1 == 0
            
            // Simple Topological Sort / Cycle Check on induced subgraph of U
            // We can use Kahn's algorithm or DFS.
            // Since N is small, let's use a simple DFS or in-degree check.
            
            // Let's implement Kahn's algorithm for the subgraph
            vector<int> in_degree(n, 0);
            int nodes_in_u_count = 0;
            
            for(int i=0; i<n; ++i) {
                if (!((mask >> i) & 1)) {
                    nodes_in_u_count++;
                    for (int neighbor : adj[i]) {
                        if (!((mask >> neighbor) & 1)) {
                            in_degree[neighbor]++;
                        }
                    }
                }
            }
            
            vector<int> q;
            for(int i=0; i<n; ++i) {
                if (!((mask >> i) & 1)) {
                    if (in_degree[i] == 0) {
                        q.push_back(i);
                    }
                }
            }
            
            int visited_count = 0;
            int head = 0;
            while(head < q.size()){
                int u = q[head++];
                visited_count++;
                for(int v : adj[u]) {
                    if (!((mask >> v) & 1)) {
                        in_degree[v]--;
                        if (in_degree[v] == 0) {
                            q.push_back(v);
                        }
                    }
                }
            }
            
            if (visited_count == nodes_in_u_count) {
                // It is a DAG
                if (current_popcount < min_popcount) {
                    min_popcount = current_popcount;
                    results.clear();
                }
                // Construct the frequency array
                vector<int> freq(26, 0);
                for(int i=0; i<n; ++i) {
                    char c = id_to_char[i];
                    if ((mask >> i) & 1) {
                        freq[c - 'a'] = 2;
                    } else {
                        freq[c - 'a'] = 1;
                    }
                }
                results.push_back(freq);
            }
        }

        return results;
    }
};
# @lc code=end