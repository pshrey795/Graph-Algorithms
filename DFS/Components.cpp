//This program outputs the number of connected components of a given undirected graph

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;

void DFS(int u,vector<int> &labels,int k){
    labels[u]=k;
    for(int i=0;i<graph[u].size();i++){
        if(labels[graph[u][i]]==0){
            DFS(graph[u][i],labels,k);
        }
    }
    return;
}

vector<int> findComponents(){
    vector<int> labels;
    for(int i=0;i<=graph.size();i++){
        labels.push_back(0);
    }
    int k=1;
    int i=1;
    while(i<graph.size()){
        if(labels[i]==0){
            DFS(i,labels,k);
            k++;
        }
        i++;
    }
    return labels; 
}

int main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++){
        vector<int> v;
        graph.push_back(v);
    }
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> labels = findComponents();
    int k = 0;
    for(int i=1;i<labels.size();i++){
        k = max(labels[i],k);
    }
    cout<<k<<endl;
    return 0;
}
