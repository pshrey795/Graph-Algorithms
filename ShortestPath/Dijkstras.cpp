//Given a directed graph with positive weights, this program finds the shortest path between two given nodes u and v using Dijkstras' Algorithm

#include<bits/stdc++.h>
using namespace std;

vector<unordered_map<int,long long>> graph;
vector<long long> dist;
unordered_set<int> done;
vector<int> pending;
int size=0;

void push(int u){
	size++;
	pending[size]=u;
	int i=size;
	while(i>1){
		if(dist[pending[i/2]]>dist[u]){
			pending[i]=pending[i/2];
			i=i/2;
		}else{
			break;
		}
	}
	pending[i]=u;
}

int pop(){
	int v = pending[1];
	int a = pending[size];
	pending[size]=0;
	size--;
	if(size>0){
		int i=1;
		pending[i]=a;
		while(2*i<=size){
			if(2*i+1<=size){
				if(dist[pending[2*i]]<dist[pending[2*i+1]]){
					if(dist[pending[2*i]]<dist[a]){
						pending[i]=pending[2*i];
						i=2*i;
					}else{
						break;
					}	
				}else{
					if(dist[pending[2*i+1]]<dist[a]){
						pending[i]=pending[2*i+1];
						i=2*i+1;
					}else{
						break;
					}
				}
			}else{
				if(dist[pending[2*i]]>dist[a]){
					pending[i]=pending[2*i];
					i=2*i;
				}else{
					break;
				}
			}
		}
		pending[i]=a;
	}
	return v;
}

void update(int v){
	int i=1;
	while(i<=size){
		if(pending[i]==v){
			break;
		}else{
			i++;
		}
	}
	while(i>1){
		if(dist[pending[i/2]]>dist[v]){
			pending[i]=pending[i/2];
			i=i/2;
		}else{
			break;
		}
	}
	pending[i]=v;
}

void weightedDFS(int u){
	done.insert(u);
	for(auto x:graph[u]){
		int v = x.first;
		if(done.find(v)==done.end()){
			int w = x.second;
			if(dist[v]==-1){
				dist[v]=dist[u]+w;
				push(v);
			}else if(dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				update(v);
			}
		}
	}
	if(size==0){
		return;
	}else{
		int v = pop();
		weightedDFS(v);
	}
}

void weightedTraversal(int u){
	dist[u]=0;
	weightedDFS(u);
}

int main(){
	int n,m;cin>>n>>m;
	for(int i=0;i<=n;i++){
		unordered_map<int,long long> k;
		graph.push_back(k);
		dist.push_back(-1);
		pending.push_back(0);
	}
	for(int i=0;i<m;i++){
		int a,b;
		long long c;
		cin>>a>>b>>c;
		graph[a][b]=c;
	}
	int u,v;cin>>u>>v;               
	weightedTraversal(u);
	cout<<dist[v]<<"\n";
	return 0;
}
