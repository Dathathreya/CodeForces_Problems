#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define  SZ (int)3e5+4
char s[SZ];int sgt[SZ];

// void update(int idx,int value){
// 	// iterative segment tree 
// }

// int query(int idx){
// 	// iterative segment tree
// }
int min(int a,int b){return (a<=b)?(a):(b);}
void update(int idx){

}

void solve(){
	int n,q;
	assert(fscanf(stdin,"%d %d",&n,&q)>0);
	int value=1,cnt=0,mask=0,i=0,b=0,total=0;
	int answer[25];
	memset(answer,0,sizeof(answer));
	
		b=0;
		cnt=0;int cmask=0,maxi=0;
		for(mask=(1<<b);mask<q;b+=1,mask|=(1<<b)){
			answer[cnt++]=(1<<b);
			cmask=mask;

			total+=(1<<b);
		}
		
		answer[cnt++]=q-1-total; // number uptil/immediate_before q
		answer[cnt++]=q+1;  // next number after q 
		answer[cnt++]=q+1+cmask+1; // next number after q with mask+1 added
		
		for(cmask=(cmask+1)*2;cmask<=(1<<25);cmask*=2){
			answer[cnt++]=cmask;
		}

	printf("%d\n",25);	
	for(i=0;i<25;i++){
			printf("%d ",answer[i]);
	}
	printf("\n");
}
int main(int argc,char* argv[]){
	int tt=1;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

// https://codeforces.com/contest/1966/problem/D

// 1 2 4 2 8+3 8+8+3

// reach till 18
// 19+1
// 19+2
// 19+3 
// 19+4,+5,+6,+7,+8,+9(28),+10(29==16+11+2),+11,+12
