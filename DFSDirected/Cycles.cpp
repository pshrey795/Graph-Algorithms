//This program checks if there is a cycle in a given directed graph

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> reverseGraph;
vector<int> labels;
int label=1;
vector<bool> preOrder;
vector<pair<int,int>> postOrder;
int postLabel=1;

void DFS(int n){
    labels[n]=label;
    for(int i=0;i<graph[n].size();i++){
        if(labels[graph[n][i]]==0){
            DFS(graph[n][i]);
        }
    }
}

void reverseDFS(int n){
    preOrder[n]=true;
    for(int i=0;i<reverseGraph[n].size();i++){
        if(!preOrder[reverseGraph[n][i]]){
            reverseDFS(reverseGraph[n][i]);
        }
    }
    postOrder[n].first = postLabel;postLabel++;
}

void assignSCC(){
    int j = 1;
    while(j<postOrder.size()){
        reverseDFS(j);
        while(j<postOrder.size()){
            if(postOrder[j].first!=0){
                j++;
            }else{
                break;
            }
        }
    }
    sort(postOrder.begin(),postOrder.end());
    int i = postOrder.size()-1;
    while(i>=1){
        int u = postOrder[i].second;
        DFS(u);
        label++;
        while(i>=1){
            if(labels[postOrder[i].second]!=0){
                i--;
            }else{
                break;
            }
        }
    }
    label = label - 1;
}

int main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++){
        vector<int> v;
        vector<int> w;
        graph.push_back(v);
        reverseGraph.push_back(w);
        labels.push_back(0);
        postOrder.push_back(make_pair(0,i));
        preOrder.push_back(false);
    }
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }
    assignSCC();
    if(label==n){
        cout<<0<<"\n";
    }else{
        cout<<1<<"\n";
    }
    return 0;
}
