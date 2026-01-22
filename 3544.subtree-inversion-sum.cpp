#
# @lc app=leetcode id=3544 lang=cpp
#
# [3544] Subtree Inversion Sum
#

// @lc code=start
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges,
                                  vector<int>& nums,
                                  int k) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        
        // Build adjacency list
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Rooted tree structure
        vector<int> parent(n,-2);
        vector<vector<int>> children(n);
        queue<int> q;
        q.push(0);
        parent[0] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if(parent[v] != -2)
                    continue;
                parent[v] = u;
                children[u].push_back(v);
                q.push(v);
            }
        }

        // Get bottom-up order
        queue<int> bfsq;
        bfsq.push(0);
        vector<int> bfs_order;
        
        while (!bfsq.empty()) {
            int u = bfsq.front();
            bfsq.pop();
            bfs_order.push_back(u);
            
            for (int v : children[u]) {
                bfsq.push(v);
            }
        }
        reverse(bfs_order.begin(), bfs_order.end());

        const int K = k;
        const int Nstates = 2 * (K + 1);
        
        // DP table
        vector<vector<long long>> dp(n);

        // Bottom-up processing
        
        

       

       

       

       

       

       

       

       

       

       

       

      

      

      

      

      

      

      

      

      

      

      

      

      

      

      

      

     

     

     

     

     

     

     

     

     

     

     

     

     

     

     

     

    

    

    

    

    

    

    

    

    

    

    

    

    

   

   

   

   

   

   

   

   

   

   

   

   

   

         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
             
             
             
             
             
             
             
             
             
             
             
             
              
              
              
              
              
              
              
              
               
               
               
               
               
               
               
               
               
               
               
               
                
                
                
                
                 
                 
                 
                 
                 
                 
                 
                 
                  
                  
                  
                  
                  
                  
                  
                   
                   
                   
                   
                   
                   
                   
                    
                    
                    
                    
                    
                     
                     
                     
                     
                      
                      
                      
                       
                       
                        
                         
                          
                           
                            
                             
                              
                               
                                
                                 
                                  
                                   
                                    
                                     
                                      
                                       
                                        
                                         
                                          
                                           
                                            
                                             
                                              
                                               
                                                
                                                 
                                                  
                                                   
                                                    
                                                     
                                                      
                                                       
                                                        
                                                         
                                                          
                                                           
                                                            
                                                             
                                                              
                                                               
                                                                
                                                                 
                                                                  
                                                                   
                                                                    
                                                                     
                                                                      
                                                                       
                                                                        
                                                                         
                                                                          
                                                                           
                                                                            
                                                                             
                                                                              
                                                                               
                                                                                
                                                                                 
                                                                                  
                                                                                   
                                                                                    
                                                                                     
                                                                                      
                                                                                       
                                                                                        
                                                                                         
                                                                                          
                                                                                           
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
}
// @lc code=end