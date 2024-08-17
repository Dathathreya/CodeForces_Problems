#include <bits\stdc++.h>

using namespace std;

vector<vector<int>>adj_list_rev;

vector<bool> visited,losing,winning; // mark visited , losing , winning vertex
vector<int> degree; // number of out going edges its connected to from this vertex v
// graph should be reversed

void dfs(int root){
	visited[root] = true;
	for(int neighbour : adj_list_rev[root]){
		if(!visited[neighbour]) // neighbour not visited
		{		
				if(losing[root]){ // check if parent or root node is a losing edge (with one outgoing edge alone)
					winning[neighbour] = true; // then neighbour node is  winning vertex
				}
				else if(--degree[neighbour]==0){ // we end up at neighbour which has only 1 outgoing edge
					losing[neighbour] = true; // we need to exclude it and mark curr index as losing because 
											  // we cannot 	
				}
				else continue;
				dfs(neighbour);
		}
	}
}

void solve(){

}

int main(){
	int tt;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
