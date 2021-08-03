//Given a weighted graph, this program uses Bellman-Ford algorithm to check if there is a shortest path between two given nodes u and v, and outputs accordingly:
// Outputs '*' if v is not reachable from u
// Outputs '-' if there is a negative cycle on the path between u and v.
// Otherwise outputs the length of the shortest path.

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,long long>>> graph;
vector<long long> dist;
vector<int> prevNode;
vector<bool> isVisited;
vector<bool> isNegative;

void assignNegative(int u){
	if(!isNegative[u]){
		isNegative[u] = true;
		for(auto k: graph[u]){
			assignNegative(k.first);
		}	
	}
}

void DFS(vector<int> negatives){
	for(int i=0;i<negatives.size();i++){
		if(!isNegative[negatives[i]]){7
			assignNegative(negatives[i]);
		}
	}
}

void findNegatives(){
	vector<int> negatives;
	for(int j=1;j<dist.size();j++){
		if(isVisited[j]){
			for(auto k:graph[j]){
				if(isVisited[k.first]){
					if(dist[k.first] > dist[j] + k.second){
						negatives.push_back(k.first);
						dist[k.first] = dist[j] + k.second;
						prevNode[k.first] = j;
					}
				}	
			}
		}
	}
	DFS(negatives);
}

void traverse(int u){
	dist[u]=0;
	isVisited[u]=true;
	int n = dist.size()-1;
	for(int i=0;i<n-1;i++){
		for(int j=1;j<=n;j++){
			if(isVisited[j]){
				for(auto k:graph[j]){
					if(!isVisited[k.first]){
						dist[k.first] = dist[j] + k.second;
						prevNode[k.first] = j;
						isVisited[k.first] = true;
					}else if(dist[k.first] > dist[j] + k.second){
						dist[k.first] = dist[j] + k.second;
						prevNode[k.first] = j;
					}
				}
			}
		}
	}
	findNegatives();
}

int main(){
	int n,m;cin>>n>>m;
	for(int i=0;i<=n;i++){
		vector<pair<int,long long>> v;
		graph.push_back(v);
		prevNode.push_back(-1);
		dist.push_back(0);
		isNegative.push_back(false);
		isVisited.push_back(false);
	}
	for(int i=0;i<m;i++){
		int a,b;long long c;cin>>a>>b>>c;
		graph[a].push_back(make_pair(b,c));
	}
	int u;cin>>u;
	traverse(u);
	for(int i=1;i<=n;i++){
		if(isVisited[i]){
			if(isNegative[i]){
				cout<<"-";
			}else{
				cout<<dist[i];
			}
		}else{
			cout<<"*";
		}
		cout<<"\n";
	}
	return 0;
}
