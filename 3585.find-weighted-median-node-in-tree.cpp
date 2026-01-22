#
# @lc app=leetcode id=3585 lang=cpp
#
# [3585] Find Weighted Median Node in Tree
#

// @lc code=start
class Solution {
public:
    vector<int> findMedian(int n,
                           vector<vector<int>>& edges,
                           vector<vector<int>>& queries) {
        constexpr static const size_t LOG_MAX{20};
        
        /* Build adjacency list */
        vector<vector<pair<int,int>>> adj(n);
        const auto addEdge{[&](int const src,
                               int const dst,
                               int const w){
            adj[src].emplace_back(dst,w);
            adj[dst].emplace_back(src,w);
        }};
        
        size_t idx{edges.size()};
        while(idx--) {
            auto const& e{edges[idx]};
            addEdge(e[0],e[1],e[2]);
        }
        
        /* ----------- preprocessing ----------- */
        vector<int>         depth(n);
        vector<long long>   distRoot(n);
        vector<int>         parent(n,-1);
        
        /**
         * @brief Depth‑first search establishing
         *   ──▶ parents,
         *   ──▶ depths,
         *   ──▶ distances from root.
         */
        const std::function<void(int,int)> dfs{
          [&](int const curr,int const prev){
              for(auto const& [nxt,w]:adj[curr]) {
                  /* skip back‑edge */
                  if(nxt==prev)
                      continue;
                  
                  /* update structures */
                  parent[nxt]=curr;
                  depth[nxt]=depth[curr]+static_cast<int>(!!w); /* w≥¹ ⇒ +¹ */
                  /* safe cast w→long long */
                  long long const wLL{w};
                  distRoot[nxt]=distRoot[curr]+wLL;
                  
                  dfs(nxt,curr);
              }
          }
        };
        dfs(/*root*/0,-INT_MAX); /* any negative sentinel works */
        
        /* -------- Binary‑lifting tables -------- */
        /* Up‑pointers */
        vector<vector<int>>         uplink(n,
                                           vector<int>(LOG_MAX,-INT_MAX));
        /* Sums of weights over those pointers */
        vector<vector<long long>> upsmsum(n,
                                          vector<long long>(LOG_MAX));
                                          
        /* Initialise level‑zero */
        size_t i{n};
        while(i--) {
            uplink[i][static_cast<size_t>(!!i)] =
                static_cast<int>(i)
                    ?parent[i]
                    :-INT_MAX;
            
            upsmsum[i][static_cast<size_t>(!!i)] =
                static_cast<int>(i)
                    ?static_cast<long long>(distRoot[i]
                                            -distRoot[parent[i]])
                    :static_cast<long long>(/*root*/INT_MIN);
                                            /* sentinel */
                                            
            /* fill sentinel row */
            uplink[i][static_cast<size_t>(!!i)] =
                static_cast<int>(i)
                    ?parent[i]
                    :-INT_MAX;
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                            
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                        
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                    
                                
                                
                                
                                
                                
                                
                                
                                
                            
                            
                            
                            
                            
                        
                        
                        
                        
                    
                    
                
                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                                
                                            
                                            
                                            
                                            
                                        
                                       
                                       
                                       
                                       
                                   
                                   
                                   
                               
                               
                           
                           
                       
                       
                   
                   
               
               
           
           
       
       
       
       
       
       
       
       
       
       
       
       
       
       
      
      
      
      
      
      
      
      
      
      
      
      
     
     
     
     
     
     
     
     
     
     
    
    
    
    
    
    
    
    
    
    
   
   
   
   
   
   
   
   
   
   
  
  
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}}
}}
}}}
}}}}
}}}}}
}}}}}}
}}}}}}}
}}}}}}}}
}}}}}}}}}
}}}}}}}}}}
}}}}}}}}}}}
}}}}}}}}}}}}
}}}}}}}}}}}}}
}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}}
}}}}}}}}}}}}}}}}}}}}}}}
}}}
}}}
}}}
}}}
}}}
}}}
}}}
}}}
}}}
}}}
}}}