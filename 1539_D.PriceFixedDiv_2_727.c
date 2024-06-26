#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef long long int lli;
typedef struct pair{
    lli want; lli ask;
}pll;
#define FOR(i,a,n) for(i=a;i<=n-1;i++)
#define M (int)2e5+4
pll a[M],t[M];

typedef int (*comparator_t)(const void* frr,const void* arr,int fr,int sc);
typedef void (*swap_t)(const void* frr,const void* arr, int fr,int sc);
typedef int (*decide_t)(const void* list,int ind,lli up,lli offset,lli key);

lli min(lli a,lli b){return (a<=b)?(a):(b);}

int decide_pll(const void* arr,int ind,lli up,lli offset,lli key){
    pll* list = (pll*)arr;
    return (list[ind].want-up>=key-offset); 
}

void swapPairs(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
    if(t2==NULL){
        pll p1 = t1[fr];
        t1[fr] = t1[sc];
        t1[sc] = p1;
    }
    return;}

int comparePairWant(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
    
        if(t1[fr].want==t1[sc].want){
            return t1[fr].ask<=t1[sc].ask;
        }
        return t1[fr].want<t1[sc].want;}

int comparePairAsk(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
        if(t1[fr].ask==t1[sc].ask){
            return t1[fr].want<=t1[sc].want;
        }
        return t1[fr].ask<t1[sc].ask;}

void down_heapify(const void* arr,int root,int sz,comparator_t compfn,swap_t swapfn){
    int greatest = root;
    int left = (root*2)+1,right =(root*2)+2;
    if((left<sz)&&(compfn(arr,NULL,greatest,left))){
        greatest = left;
    }
    if((right<sz)&&(compfn(arr,NULL,greatest,right))){
        greatest = right;
    }
    if(greatest != root){
        swapfn(arr,NULL,greatest,root);
        down_heapify(arr,greatest,sz,compfn,swapfn);
    }
}

void up_heapify(const void* arr,int root,int child,comparator_t compfn,swap_t swapfn){
    int parent = (((child-1)/2)>=root)?(((child-1)/2)):(root);
    if((parent==child)||(!compfn(arr,NULL,parent,child))){

    }
    else{
        swapfn(arr,NULL,parent,child);
        up_heapify(arr,root,parent,compfn,swapfn);
    }
}

void Sort(const void* arr,int low,int high,swap_t swapfn,comparator_t compfn){
    for(int bottom=low;bottom<=high;bottom++){
        up_heapify(arr,low,bottom,compfn,swapfn);
    }
    for(int last=high;last>=low;last--){
        swapfn(arr,NULL,low,last);
        down_heapify(arr,low,last,compfn,swapfn);
    }
    return;}

// greedy , binary search , two pointers , sorting 

int lower_bound(const void* arr,int low,int high,lli key,lli up,lli offset,decide_t decide){
    int ret=high;int len=high;

    while(low<high){
        int mid = low + (high-low)/2;
        if(decide(arr,mid,up,offset,key)){   /* mid >= key */
            high = mid;
            ret = mid;
        }
        else{
            low = mid+1;
        }
    }
    return ret;
}

lli f (lli Want,lli Spend){
    return ((Want <=Spend)?(0):(Want-Spend));
}

void solve(){
    int n,i;lli answer=0;
    assert(fscanf(stdin,"%d",&n)>0);
    FOR(i,0,n)     assert(fscanf(stdin,"%lli %lli",&a[i].want,&a[i].ask)>0);

    // Sort by CountOfItems needed for discount to buy items wanted by guy
    Sort(a,0,n-1,swapPairs,comparePairAsk);
    
    // from end compute prefix sum
    FOR(i,1,n) a[n-1-i].want += a[n-i].want ;

    // reverse the array so that element with least want and most ask comes first 
    // element with least ask comes at end to pick wanted element of that item type 
    // in a greedy approach
    FOR(i,0,(n/2)){
        swapPairs(a,NULL,i,n-1-i);
    }
 
    lli bought_cnt=0,up=0,down=0;
    int fr=0,ls=n-1;

    for(;ls>=fr;)
    {
        if(bought_cnt>=a[ls].ask) // last item ask is met 
        {
            lli prev = bought_cnt;
            // if two pointers meet then add difference between CountOfBoughtItemsFromTop and CurrentWant
            bought_cnt += ((ls>fr)?(a[ls].want-a[ls-1].want):(a[ls].want-up));
            answer  +=  (bought_cnt-prev);
            ls-=1;
        }
        else{
                // search for least number which need to be bought at $2 to buy wantNumberOfItems at $1 
                // in range first to last using CountFromTopWithTwoDollarSpent as Up and totalCount - bought_cnt 
                fr = lower_bound(a,fr,ls,a[ls].ask,up,bought_cnt,decide_pll);
                
                lli prev = up;
                answer += (2*min(a[ls].ask - bought_cnt,a[fr].want-prev));
                answer += ((ls>fr)?(a[ls].want-a[ls-1].want):(f(a[ls].want-prev,a[fr].ask-bought_cnt)));

                up     += (1*min(a[ls].ask - bought_cnt,a[fr].want-prev));
                down    = ((ls>fr)?(a[ls].want-a[ls-1].want):(0));

                bought_cnt += (up-prev);
                bought_cnt += (down);
                
                ls-=1;
        }
    }
    printf("%lli\n",answer);
}
int main()
{
    int tt=1;
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0){
        solve();
    }
    return 0;
}

// /* practice with Dukkha */
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define N   2000000
// #define M   1000000

// struct L {
//     struct L *next;
//     int j;
// } aa[N];

// int ab[M + M], ii[M + M], xx[N], dd[N], dd_[N], stack[N];
// char visited[N];

// int compare(const void *a, const void *b) {
//     int i = *(int *) a;
//     int j = *(int *) b;

//     return ab[i] - ab[j];
// }

// void link(int i, int j) {
//     static struct L l91[M * 2], *l = l91;

//     l->j = j;
//     l->next = aa[i].next; aa[i].next = l++;
// }

// int dfs(int p, int i) {
//     struct L *l;

//     if (visited[i])
//         return 0;
//     visited[i] = 1;
//     for (l = aa[i].next; l; l = l->next)
//         if (l->j != p && !dfs(i, l->j))
//             return 0;
//     return 1;
// }

// int check(int n, int n_) {
//     int i, cnt;

//     memset(visited, 0, n * sizeof *visited);
//     for (i = n_; i < n; i++)
//         if (!dfs(-1, i))
//             return 0;
//     cnt = 0;
//     for (i = 0; i < n_; i++)
//         if (!visited[i] && (dd_[i] = dd[i]) == 1)
//             stack[cnt++] = i;
//     while (cnt) {
//         struct L *l;

//         i = stack[--cnt];
//         if (dd_[i] < 1)
//             continue;
//         dd_[i] = 0;
//         for (l = aa[i].next; l; l = l->next)
//             if (--dd_[l->j] == 1)
//                 stack[cnt++] = l->j;
//     }
//     for (i = 0; i < n_; i++)
//         if (!visited[i] && dd_[i] > 2)
//             return 0;
//     return 1;
// }

// int main() {
//     int n, m, h, i, j, a, b, lower, upper;

//     scanf("%d", &m);
//     for (h = 0; h < m; h++) {
//         scanf("%d%d", &a, &b);
//         ab[h * 2 + 0] = a;
//         ab[h * 2 + 1] = b;
//     }
//     for (h = 0; h < m + m; h++)
//         ii[h] = h;
//     qsort(ii, m + m, sizeof *ii, compare);
//     n = 0;
//     for (h = 0; h < m + m; h++)
//         if (h + 1 == m + m || ab[ii[h]] != ab[ii[h + 1]]) {
//             xx[n] = ab[ii[h]];
//             ab[ii[h]] = n++;
//         } else
//             ab[ii[h]] = n;
//     for (h = 0; h < m; h++) {
//         i = ab[h * 2 + 0], j = ab[h * 2 + 1];
//         link(i, j), link(j, i);
//         dd[i]++, dd[j]++;
//     }
//     lower = 0, upper = n + 1;
//     while (upper - lower > 1) {
//         int n_ = (lower + upper) / 2;

//         if (check(n, n_))
//             upper = n_;
//         else
//             lower = n_;
//     }
//     printf("%d\n", upper == n + 1 ? -1 : xx[upper - 1]);
//     return 0;
// }
// https://codeforces.com/problemset/problem/1567/C
// https://codeforces.com/contest/1567
