//This program checks if the given undirected graph is bipartite or not

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> color;

bool isBipartite(){
    int i=1;
    queue<int> q;
    while(i<graph.size()){
        q.push(i);
        color[i]=0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int j=0;j<graph[u].size();j++){
                int v = graph[u][j];
                if(color[v]>=0){
                    if(color[u]==color[v]){
                        return false;
                    }
                }else{
                    q.push(v);
                    if(color[u]==0){
                        color[v]=1;
                    }else{
                        color[v]=0;
                    }
                }
            }
        }
        while(i<graph.size()){
            if(color[i]>=0){
                i++;
            }else{
                break;
            }
        }
    }
    return true;
}   

int main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++){
        vector<int> v;
        graph.push_back(v);
        color.push_back(-1);
    }
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    if(isBipartite()){
        cout<<1<<"\n";
    }else{
        cout<<0<<"\n";
    }
    return 0;
}
