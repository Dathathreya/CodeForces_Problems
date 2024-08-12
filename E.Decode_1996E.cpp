https://codeforces.com/contest/1996/submission/275988373
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M (int)2e5+1
int prefix [M];
int main()
{
    // for each pair (l,r) , count number of pairs (x,y) where cnt(0)=cnt(1) where 1<=l<=x<=y<=r 
    // instead of counting above mentioned pairs in each interval of n we count contribution of valid substring 
    // valid substring is starting and ending with same value to make prefixSum equal 
    // prefix sum by considering 0 as -1 and 1 as +1 
    int i=0,t;
    ll mod=1000000000+7,ans =0;
    
    cin>>t;
    while(t--){
       
    string s;
        cin>>s;
        int n = s.size();
        vector<ll> prefix(n+1);
        s = "#"+s;
        ans = 0;
        map<ll,ll>SumOfCbt;
        for(i=1;i<=n;i++){
            prefix[i] = (s[i]=='0')?-1:+1;
            prefix[i] = prefix[i] +  prefix[i-1];
        }
        ans = 0;
        for(i=0;i<=n;i++){
            ll leftSm = prefix[i];
            ll left_contribution = SumOfCbt[leftSm]; // Sum of all substrings  which starts with L
            // that covers current substring
            ll right = n-i+1; // including current number finding R
            //printf("(%lli,%d)",left_contribution,right);  
            ans += (right*(left_contribution%mod));
            SumOfCbt[leftSm] += (i+1); 

                 // 1 2 3 4 5 6 7 8 9   
                 // 0 0 1 1 0 1 1 0 0 
                 //   _______
                 //       ___    
                 // LeftSum = (2 + 4)*5 = (L1 + L2)*R    

                // TC1 will give 0 as each time we get new sum but we want same sum which we got in past
                // Example 1: 
            //    0 1 2 3 4 5 6 7 8 
            //      0 1 0 1 0 1 0 1
            //     -1+0-1+0-1+0-1+0 // including 8 itself 
                //  2+3+4+5+6+7+8+ 
                // (key,value) - (-1,2+4+6+8) (0,1+3+5+7) // saving nextStartingPoint 
                // why we save  PrevStartingPoint in each case ?
                //  each prevstartingpoint  contains the valid starting L as its having a substring with c(0)==c(1)    
                // cnt =   1*7 + 2*6 + 4*5 + 6*4 + (1+3+5)*3 +  12*2  +  16*1
        }
        ans %= mod;
        // if(ans<0) ans += mod;
        cout<<ans<<endl;
        //printf("%d\n",ans);
    }
    return 0;
}


