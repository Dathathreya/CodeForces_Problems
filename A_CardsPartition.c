#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//https://codeforces.com/contest/2018/problem/A
const int MOD = 998244353;
//int dp[300005],ans[300005],sum[300005];
typedef long long unsigned llu;
// 3 2 3
// 8 / 3 = 2
// total number of cards - 7 
// subset of size 1,2,3

llu min(llu a,llu b){
  return (a<=b)?(a):(b);
}

void solve(){
   llu k,maxi=0,sum=0,x=0,sumk=0; int n,i;
   fscanf(stdin,"%d %llu",&n,&k);
   for(i=0;i<n;i++){
      fscanf(stdin,"%llu",&x);
      if(maxi<x) maxi = x;
      sum += x;
   }
   sumk = sum + k; // buy k items along with existing sum 
   for(i=n;i>=1;i--){
      llu perfect = 1lu*(sumk/i)*i; // make total divisible by current group size (column_size) 
      if(perfect >= 1llu*maxi*i && perfect >= sum){
        // 1. check all columns in  group_size is complete
        //    maximum spans across entire column width  
        // 2. second check is done as we do  division 
        //    division is done so perfect_sum could be lesser  
          printf("%d\n",i);
          return;
      }
   }
   /*
   1) 
     1 S      1 S
     1 S      1 S
     1 S      1 S 
     X Y 
   perfect >= maxi*group_size
   2) 
      perfectsum >= completeSum
   */
}

int main()
{
  int tt;
  assert(fscanf(stdin,"%d",&tt)>0);
  while(tt--){
    solve();
  }
}
