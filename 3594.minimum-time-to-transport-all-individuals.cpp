#
# @lc app=leetcode id=3594 lang=cpp
#
# [3594] Minimum Time to Transport All Individuals
#

#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <cfloat>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    double minTime(int n, int k, int m,
                   vector<int>& time,
                   vector<double>& mul) {
        const int ALL_MASK = (1 << n) - 1;
        const int STATE_COUNT = (ALL_MASK + 1) * 2 * m;
        vector<double> dist(STATE_COUNT, DBL_MAX);
        
        auto encode = [&](int mask,
                          int boat,
                          int stage) {
            return ((mask << 1) | boat) * m + stage;
        };
        auto decode =
            [&](int idx,
                int& mask,
                int& boat,
                int& stage) {
                stage = idx % m;
                int temp = idx / m;
                boat   = temp &  1;
                mask   = temp >>  1;
            };
        
        // Pre‑compute maximum rowing strength per subset
        vector<double> maxTime(ALL_MASK +  1);
        for(int msk =  1; msk <= ALL_MASK; ++msk){
            int lb      = msk & -msk;
            int i       = __builtin_ctz(lb);
            maxTime[msk] =
                max(maxTime[msk ^ lb],
                    static_cast<double>(time[i]));
        }
        
        priority_queue<pair<double,int>,
                       vector<pair<double,int>>,
                       greater<pair<double,int>>> pq;
        
        int startIdx    = encode(0 ,  0 ,  0);
        dist[startIdx]   =  0 .   ;
        pq.push({  0 . , startIdx});
        
        while(!pq.empty()){
            auto top    = pq.top();
            pq.pop();
            double curTime      = top.first;
            int    curIdx       = top.second;
            
            if(curTime > dist[curIdx]) continue;
            
            int mask , boat , stage;
            decode(curIdx ,
                   mask ,
                   boat ,
                   stage);
            
            // Goal reached ?
            if(mask == ALL_MASK &&
               boat ==   ){
                return curTime;
            }
            
            if(boat ==   ){ // Boat at base camp
                const int remMask =
                    ALL_MASK ^ mask;
                
                // Enumerate non‑empty subsets
                // whose size ≤ k
                for(int subMask =
                        remMask;
                    subMask >   ;
                    subMask =
                        (subMask - ) &
                        remMask){
                    
                    const int cnt =
                        __builtin_popcount(subMask);
                    
                    if(cnt > k)
                        continue;
                    
                    const double crossTime =
                        maxTime[subMask]
                        * mul[stage];
                    
                    const int advance =
                        static_cast<int>(
                            floor(crossTime));
                    
                    const int newStage =
                        (stage + advance)
                        % m;
                    
                    const int newMask =
                        mask | subMask;
                    
                    constexpr bool NEW_BOAT =
                         ;
                    
                    const double newTime =
                        curTime +
                        crossTime;
                    
                    const int newIdx =
                        encode(newMask ,
                               NEW_BOAT ,
                               newStage);
                    
                    
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                      
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                       
                         
                         
                         
                         
                         
                         
                         
                         
                         
                         
                         
                         
                          
                          
                          
                          
                          
                          
                          
                           
                           
                           
                           
                           
                           
                           
                            
                            
                            
                             
                             
                              
                              
                               
                                
                                 
                                  
                                   
                                    
                                     
                                      
                                       
                                        
                                         
                                          
                                           
                                            
                                             
                                              
                                               
                                                
                                                 
                                                  
                                                   
                                                    
                                                     
                                                      
                                                       
                                                        
                                                         
                                                          
                                                           
                                                            
                                                             
                                                              
                                                               
                                                                
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                