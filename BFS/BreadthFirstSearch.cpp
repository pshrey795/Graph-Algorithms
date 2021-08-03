//Program to find the shortest path between two given nodes u and v using breadth first search(given a connected graph)

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> dist;

void BFS(int u){
    queue<int> q;
    q.push(u);
    dist[u]=0;
    while(!q.empty()){
        int n = q.front();
        q.pop();
        for(int i=0;i<graph[n].size();i++){
            int v=graph[n][i];
            if(dist[v]<0){
                dist[v]=dist[n]+1;
                q.push(v);
            }
        }
    }
}

int main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++){
        vector<int> v;
        graph.push_back(v);
        dist.push_back(-1);
    }
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int u,v;cin>>u>>v;
    BFS(u);
    cout<<dist[v]<<"\n";
    return 0;
}
