//For a given directed graph, this program outputs a topological ordering of the nodes

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> reverseGraph;
vector<bool> preOrder;
vector<pair<int,int>> postOrder;
int postLabel=1;

void reverseDFS(int n){
    preOrder[n]=true;
    for(int i=0;i<reverseGraph[n].size();i++){
        if(!preOrder[reverseGraph[n][i]]){
            reverseDFS(reverseGraph[n][i]);
        }
    }
    postOrder[n].first = postLabel;postLabel++;
}

int main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<=n;i++){
        vector<int> v;
        vector<int> w;
        graph.push_back(v);
        reverseGraph.push_back(w);
        postOrder.push_back(make_pair(0,i));
        preOrder.push_back(false);
    }
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }
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
    for(int i=1;i<postOrder.size();i++){
        cout<<postOrder[i].second<<" ";
    }
    cout<<"\n";
    return 0;
}
