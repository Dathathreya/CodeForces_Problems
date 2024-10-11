// https://codeforces.com/problemset/problem/2020/D
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N ((int)2e5+8)
int parent[N],size[N];

int min(int a,int b){return (a<=b)?(a):(b); }
int max(int a,int b){return (a>=b)?(a):(b); }
int components;

void dsu_init(int n){

	for(int i=1;i<=n;i++){
		parent[i] = i;
		size[i] = 1;
	}
	return;
}

int find_parent(int node){
	if(parent[node]==node){
		return node;
	}
	return parent[node]=find_parent(parent[node]);
}

void unite(int a,int b){
	int parent_a = find_parent(a);
	int parent_b = find_parent(b);
	if(parent_a == parent_b){ 
		return;
	}
		components--;
		// not united
		if(size[parent_a] < size[parent_b]){
			int t = parent_a ; parent_a = parent_b ; parent_b = t;
		}
		parent[parent_b] = parent_a ;
		size[parent_a] += size[parent_b];
	
	return;
}

void solve(){
	int n,m,k,a,d,i;
	assert(fscanf(stdin,"%d%d",&n,&m)>0);	
	static int  prefixSum[N][11];
	memset(prefixSum,0,n*sizeof(int)*11);
	components = n;
	dsu_init(n);
	for(i=0;i<m;i++){
		assert(fscanf(stdin,"%d%d%d",&a,&d,&k)>0);	
								// start,how_much_far,how_many_times
		prefixSum[a][d]++;
		prefixSum[min(n,a+d*k)][d]--;
	}
	for(int start=1;start<=n;start++){
		for(int d1=1;d1<=10;d1++){
			prefixSum[start][d1] += prefixSum[max(0,start-d1)][d1];
			if((prefixSum[start][d1]>0)&&((start+d1)<=n)){
				unite(start,start+d1);
			}
		}
	}
	
	//for(i=1;i<=n;i++){ if(parent[i]==i) {components++;} }
	printf("%d\n",components);
// mistakes 
// didnt solve problem on own inspite of knowing prefixsum + dsu unite + find_parent technique
// bad indexing 
// wrong value for total no. of operations used number of points instead.
	return;
}

int main(){
	int tt;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
