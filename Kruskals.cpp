// LeetCode 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
#include<bits/stdc++.h>
using namespace std;

class UnionbyRank {
public:
 int maxSize;
    UnionbyRank(int sz) : root(sz), rank(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
            rank[i] = 1;
        }
        maxSize = 1;
    }

    int find(int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void Union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
                rank[rootX] += rank[rootY];
                maxSize = max(maxSize,rank[rootX]);
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
                rank[rootY] += rank[rootX];
                maxSize = max(maxSize,rank[rootY]);
            } else {
                root[rootY] = rootX;
                rank[rootX] += rank[rootY];
                maxSize = max(maxSize,rank[rootX]);
            }
           
        }

       
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }

private:
    vector<int> root;
    vector<int> rank;
   
};
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        auto newEdges = edges;
        int m = newEdges.size();

for (int i = 0; i < m; i++) {
            newEdges[i].push_back(i);
        }

        sort(newEdges.begin(), newEdges.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });

        UnionbyRank ds(n);
        int min_weight = 0;

        for(const auto& e : newEdges){
            if(!ds.isConnected(e[0],e[1])){
                ds.Union(e[0],e[1]);
                
                min_weight += e[2];
               
            }
        }

        

        vector<vector<int>> ans(2);
        

        for(int i = 0; i<m; i++){
            UnionbyRank ds2(n);
            int weight = 0;

            for(int j = 0; j<m; j++){
                if(i != j && !ds2.isConnected(newEdges[j][0],newEdges[j][1])){
                    weight += newEdges[j][2];
                    ds2.Union(newEdges[j][0],newEdges[j][1]);
                   

                }
            }

            if(ds2.maxSize < n || weight > min_weight){
                ans[0].push_back(newEdges[i][3]);
            }else{
                UnionbyRank ds3(n);
                ds3.Union(newEdges[i][0],newEdges[i][1]);
                int f_weight = newEdges[i][2];
                for(int j = 0; j< m; j++){
                    if(i != j && !ds3.isConnected(newEdges[j][0],newEdges[j][1])){
                        f_weight += newEdges[j][2];
                        ds3.Union(newEdges[j][0],newEdges[j][1]);
                        
                        
                    }
                }
                if(f_weight == min_weight){
                ans[1].push_back(newEdges[i][3]);
              }
            }


        }

        return ans;
        
    }

    int main(){

        //Example Test Case below
        vector<vector<int>> edges = {{0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,4,3},{3,4,3},{1,4,6}};
        vector<vector<int>> ans = findCriticalAndPseudoCriticalEdges(5, edges);

        cout<<"Critical Points are: ";
        for(int& e : ans[0]){
            cout<<e<<" ";
        }

        cout<<endl;

        cout<<"Pseudo Critical Points are: ";
        for(int& e : ans[1]){
            cout<<e<<" ";
        }

        cout<<endl;

        return 0;
    }

