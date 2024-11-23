#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define N 300001

static void io_init() 
{
#ifdef  LocalStreetLampsLitOnFire
	assert(freopen("input.txt", "r", stdin) > 0);
	assert(freopen("output.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}

typedef int compare_self_t(const void* ar,int fr,int sc);
typedef void swap_self_t(const void* ar,int fr,int sc);
int cnt = 0,tot_sz=0,mxvalue=-1;
int _max(int a,int b){
    return (a>=b)?(a):(b); 
}
typedef struct pair{
    int value,position;
}pii;

pii arr[N];int ft[N];
void fwk_update(int pos,int val,int sz){
    while(pos<sz){
        ft[pos]+=val;
        pos |= (pos+1);
    }    
    return;
}
int fwk_query(int pos){
        int ans=0;
        while(pos>=0){
            ans += ft[pos];
            pos &= (pos+1);
            pos--;
        }
        return ans;
}

int compare_self_pair(const void* arr,int f,int s){
    pii* a1 =(pii*)arr;
    if((a1[f].value)==(a1[s].value)){
        return (a1[f].position)<(a1[s].position);
    }
    return (a1[f].value)<(a1[s].value);
}

void swap_self_pair(const void *arr,int f,int s){
    pii* a1 =(pii*)arr; 
    pii t=a1[f];
    a1[f]=a1[s];
    a1[s]=t;
    return;
}
    
void heapify(const void* arr,int root,int sz,compare_self_t compfn,swap_self_t swapfn){
    int greatest = root,left=2*root+1,right=2*root+2;
    if((left<sz)&&(compfn(arr,greatest,left))){
        greatest = left;    
    }
    if((right<sz)&&(compfn(arr,greatest,right))){
        greatest = right;    
    }
    if(greatest!=root){
        swapfn(arr,greatest,root);
        heapify(arr,greatest,sz,compfn,swapfn);
    }
}

void heapSort(const void* arr,int low,int high,compare_self_t compfn,swap_self_t swapfn){
    for(int z=(low+(high-low)/2);z>=low;z--){
        heapify(arr,z,high+1,compfn,swapfn);    
    }
    for(int end=high;end>=low;end--)
    {
        pii* lst = (pii*)arr; 
        int pos = lst[0].position;
        int _cnt = fwk_query(tot_sz-1)-fwk_query(pos);
        cnt = _max(cnt,_cnt);
        lst[0].position = _cnt;
        swapfn(arr,low,end);    
        fwk_update(pos,-1,tot_sz);
        heapify(arr,low,end,compfn,swapfn);    
    }
}


void solve(){
    int n,i;
    cnt = 0;
    assert(fscanf(stdin,"%d",&n)>0);
    memset(ft,0,sizeof(ft));
    tot_sz = n;
    for(i=0;i<n;i++){
        assert(fscanf(stdin,"%d",&arr[i].value)>0);
        fwk_update(i,+1,tot_sz);
        arr[i].position=i;
    }
    heapSort(arr,0,tot_sz-1,compare_self_pair,swap_self_pair);
    int last = arr[0].value,f_cnt=0;
    for(i=0;i<n;){
        int nxt = i+1,f_max=arr[i].position;
        cnt = 1;
        f_cnt = _max(f_cnt,cnt+f_max);
        for(;(nxt<n)&&(arr[nxt].value==arr[i].value);){
            f_max= _max(f_max,arr[nxt].position);
            cnt++;
            f_cnt = _max(f_cnt,cnt+f_max);
            nxt++;
        }
        i=nxt;
    }
    printf("%d\n",n-f_cnt);
    return;
}

int main(){
    io_init();
    int tt;
    assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    }
}
