#include <stdio.h>
#include <string.h>
#include <limits.h>
#define N ((int)2e5+4)
typedef long long ll;
ll a[N],b[N];
 
ll min(ll a,ll b){return (a<=b)?(a):(b); }
ll max(ll a,ll b){return (a>=b)?(a):(b); }

void solve(){
     int n;
        scanf("%d",&n);
        for(int i = 0;i<n;i++){
            scanf("%lld",&a[i]);
        }
        ll mx = LLONG_MIN,mn = LLONG_MAX;
        for(int i = 0;i<n;i++){
            mx = max(a[i],mx);
            mn = min(a[i],mn);
        }
        // problem a[i] -= x , a[i+1] +=x;
        ll mxlow = -1,mxhigh = mx;
        while((mxlow+1)<mxhigh){
            ll mid = mxlow + (mxhigh-mxlow)/2LL;
            // checker 
            for(int i=0;i<n;i++){
                b[i] = a[i];
            }
            // if current is more , we tried to maximize next
            for(int i=0;i<(n-1);i++){
                // a[i] > a[i+1]
                // problem a[i] -= x(consider this and make it current) , a[i+1] +=x;
                if(b[i] > mid){
                      ll diff = b[i]- mid;
                      b[i+1] +=  diff;
                      b[i] = mid;
                }
            }
            ll localmaxi = b[0];
            for(int i=0;i<n;i++){
                localmaxi = max(localmaxi,b[i]);
            }
            if(localmaxi <= mid){ 
                mxhigh = mid; // answer
            }
            else{ // current maxi strictly greater than mid , 
                mxlow = mid;
            }
        }
        ll mnlow = mn,mnhigh = ((ll)(1e12));
        while((mnlow+1)<mnhigh){
            ll mid = mnlow + (mnhigh-mnlow)/2LL;
            // checker func 
            for(int i = 0;i<n;i++){
                b[i]=a[i];
            }
            // a[i] -= x , a[i+1] += x 
            //   19 9
                //  |
                //  mid         
                //  x
                // if current is lesser we tried to make it high by removing prev
                // reverse order
            for(int i = n-1;i>0;i--){
                if(b[i]<mid)
                {
                    ll diff = mid-b[i];
                    b[i-1] -= diff;
                    b[i] = mid;
                } 
            }
            ll localmini = b[0];
            for(int i = 0;i<n;i++){
                localmini = min(localmini,b[i]);
            }
            if(localmini >= mid){
                mnlow = mid; // answer
            }
            else{
                mnhigh = mid;
            }
        }
        printf("%lld\n",mxhigh-mnlow);
        return;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
       solve();
    }
    return 0;
}
