// LeetCode 1203. Sort Items by Groups Respecting Dependencies
//In this problem, we are dealing with a more complex variation of the topological sorting algorithm
//Consequently, the objective is to achieve two levels of sorting:
// sorting the groups based on the group dependencies,
// sorting the items within each group according to the item dependencies.

#include<bits/stdc++.h>
using namespace std;


  vector<int> tSort(auto& graph, vector<int>& indegree, int n){
       
        queue<int> q;

        for(int i = 0; i< indegree.size(); i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }

        vector<int> ans;

        while(!q.empty()){
            int front = q.front();
            q.pop();
            ans.push_back(front);
            

            for(auto neigh : graph[front]){
                indegree[neigh]--;
                if(indegree[neigh] == 0){
                    q.push(neigh);
                }

            }
        }

        for(int i = 0 ;i <n; i++){
            if(indegree[i] > 0){
                return { };
            }
        }

        return ans;



    }


 vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {

        int group_id  = m;
        for(int i = 0; i<n; i++){
            if(group[i] == -1){
                group[i] = group_id;
                group_id++;
            }
        }
        unordered_map<int,vector<int>> iGraph;
        vector<int> iIndegree(n);

        unordered_map<int,unordered_set<int>> gGraph;
        vector<int> gIndegree(group_id);

        for(int curr= 0; curr < n; curr++){
            for(int& prev : beforeItems[curr]){
                iGraph[prev].push_back(curr);
                iIndegree[curr]++;

                if(group[curr] != group[prev] && gGraph[group[prev]].count(group[curr])== 0){
                    gGraph[group[prev]].insert(group[curr]);
                    gIndegree[group[curr]]++;
                }
            }
        }

        vector<int> iOrder = tSort(iGraph,iIndegree,n);
        vector<int> gOrder = tSort(gGraph,gIndegree,m);




        unordered_map<int,vector<int>> orderedGroups;

        for(int& i : iOrder){
            orderedGroups[group[i]].push_back(i);
        }

        vector<int> ans;
        for(int& gIdx : gOrder){
            for(int& ele : orderedGroups[gIdx]){
                ans.push_back(ele);
            }
        }

        return ans;





        
    }

  


int main(){

   int n = 8, m = 2;
   vector<int> group = {-1,-1,1,0,0,1,0,-1};
   vector<vector<int>>beforeItems = {{},{6},{5},{6},{3,6},{},{},{}};


   vector<int> ans =  sortItems(n,m,group,beforeItems);

   for(int& ele : ans){
    cout<<ele<<" ";
   }

   return 0;



    

}