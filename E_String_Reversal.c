#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//2193. Minimum Number of Moves to Make Palindrome
//https://codeforces.com/problemset/problem/1430/E 
//using namespace std;
typedef long long int lli;
lli ftree[200000];
char str[200000];
int _2d[26][200000]; // list of positions for each letter in string // queue
int range[26][2]; // start and end position of each characters in 2d list // front , size

void update(lli* ft,int idx,int n,lli val){
	while(idx<n){
		ft[idx] += val;
		idx |= (idx+1);
	}
	return;
}

lli query(lli* ft,int idx){
	lli sum = 0;
	while(idx>=0){
		sum += ft[idx];
		idx &= (idx+1);
		idx--;
	}
	return sum;
}

void solve(){
	int n,i,j;
	lli swaps=0;
	assert(fscanf(stdin,"%d",&n)>0);
	assert(fscanf(stdin,"%s",&str)>0);
	
	memset(ftree,0,sizeof(ftree));
	memset(_2d,0,sizeof(_2d));
	memset(range,-1,sizeof(range));

	for(i=0;i<n;i++){
		int l = str[i]-'a';
		if(range[l][1]==-1){
			range[l][0]= 0;
			range[l][1]= 1;
			_2d[l][0] = i;
		}
		else{
			int curr = (range[l][1])++;
			_2d[l][curr] =  i;
		}
		update(ftree,i,n,1);
	}
	// reverse the string
	for(i=0;i<(n+1)/2;i++){
		char s = str[n-1-i]; str[n-1-i] = str[i]; str[i] = s;
	}	
	// to process the string 
	for(i=0;i<n;i++){
		int letter = str[i]-'a';
		int pos = _2d[letter][range[letter][0]++]; // for that letter  give first number
		swaps += (query(ftree,pos)-1);
		update(ftree,pos,n,-1);
	}
	printf("%lld ",swaps);
	// for(i=0;i<26;i++){
	// 	if(range[i][1]!=-1){
	// 		printf("(%c,%d)",i+'a',range[i][1]);
	// 		for(j=0;j<range[i][1];j++){
	// 			printf("%d,",_2d[i][j]);
	// 		}
	// 		putchar('\n');
	// 	}
	// }
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
