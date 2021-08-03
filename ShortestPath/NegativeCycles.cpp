//Given a weighted graph(directed), this program uses the Bellman-Ford Algorithm to check the existence of a negative cycle in the graph.

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,long long>>> graph;
vector<long long> dist;
vector<vector<int>> reverseGraph;
vector<int> labels;
int label=1;
vector<bool> preOrder;
vector<pair<int,int>> postOrder;
int postLabel=1;
vector<int> startingPoints;

void DFS(int n){
    labels[n]=label;
    for(int i=0;i<graph[n].size();i++){
        if(labels[graph[n][i].first]==0){
            DFS(graph[n][i].first);
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
    startingPoints.push_back(j);
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
        startingPoints.push_back(u);
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

bool hasNegativeCycle(){
	bool isAltered = false;
	int n = dist.size()-1;
	for(auto i:startingPoints){
		dist[i]=0;
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<=n;j++){
			for(auto k:graph[j]){
				if(dist[j]!=(-1)){
					if(dist[k.first]==(-1)){
						dist[k.first] = dist[j] + k.second;	
					}else if(dist[k.first] > dist[j] + k.second){
						dist[k.first] = dist[j] + k.second;
						if(i==n-1){
							isAltered = true;
						}
					}
				}else{
					if(dist[k.first]!=(-1)){
						dist[j] = dist[k.first] - k.second;
					}
				}
			}
		}
	}
	return isAltered;
}

int main(){
	int n,m;cin>>n>>m;
	for(int i=0;i<=n;i++){
		vector<pair<int,long long>> v;
		vector<int> w;
		graph.push_back(v);
		dist.push_back(-1);
		reverseGraph.push_back(w);
		labels.push_back(0);
		postOrder.push_back(make_pair(0,i));
		preOrder.push_back(false);
	}
	for(int i=0;i<m;i++){
		int a,b;long long c;
		cin>>a>>b>>c;
		graph[a].push_back(make_pair(b,c));
		reverseGraph[b].push_back(a);
	}
	assignSCC();
	if(hasNegativeCycle()){
		cout<<1<<"\n";
	}else{
		cout<<0<<"\n";
	}
	return 0;
}
