#include<bits/stdc++.h>
using namespace std;


  




class UnionbyRank {
public:
    UnionbyRank(int sz) : root(sz), rank(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
            rank[i] = 1;
        }
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
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
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

// Test Case
int main() {
    
    UnionbyRank d1 = UnionbyRank(9);

    d1.Union(0,2);
    d1.Union(1,3);
    d1.Union(2,3);

    cout<<d1.isConnected(0,3)<<" "<< d1.find(0)<<" "<< d1.find(1) << " " << d1.find(2) << " " << d1.find(3);
    cout<<endl;

    d1.Union(4,6);
    d1.Union(6,8);

    cout<<d1.isConnected(3,6)<<" "<< d1.find(8) << endl;

    d1.Union(0,8);

    cout<<d1.isConnected(3,6)<<" "<< d1.find(8) << endl;
    return 0;
}