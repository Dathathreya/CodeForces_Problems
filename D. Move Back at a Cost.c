#include <stdio.h>
#include <assert.h>

#define N 100011
#define sz(ar1) (sizeof(ar1)/sizeof(ar1[0]))

typedef struct pair{
	int fr,sc;
}pii;

pii a[N];

static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
assert(freopen("input.txt", "r", stdin) );
assert(freopen("output.txt", "w", stdout));
#endif //  LocalStreetLampsLitOnFire
}

typedef int compare_self_t(const void* ar,int fr,int sc);
typedef void swap_self_t(const void* ar,int fr,int sc);

int compare_self_pii(const void* arr,int f,int s){
    pii* a1 =(pii*)arr;
    if(a1[f].fr!=a1[s].fr){
    	return (a1[f].fr>a1[s].fr);
    }
    return ((a1[f].sc<a1[s].sc)?(1):(0));
}

void swap_self_pii(const void *arr,int f,int s){
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
    for(int end=high;end>=low;end--){
        swapfn(arr,low,end);    
        heapify(arr,low,end,compfn,swapfn);    
    }
}
void solve()
{
  int n,i,cnt=0;
  assert(fscanf(stdin,"%d",&n)>0);
  for(i=0;i<n;i++)
  {
     assert(fscanf(stdin,"%d",&a[i].fr)>0);    
     a[i].sc = i;
  } 
  heapSort(a,0,n-1,compare_self_pii,swap_self_pii);
  // traverse from last part of list 
  int prev_max_ind = -1,curr=0,prev=0,next_max_ind = -1,break_point=-1,ibp=-1;
  for(i=n-1;i>=0;i--){
  		curr = a[i].fr;
  		if(prev!=curr){
  			prev_max_ind = next_max_ind;
  		}
  		if(a[i].sc>prev_max_ind){
  			printf("%d ",curr);
  		}
  		else{
  			ibp=i;
  			break_point=curr+1;
  			break;  			
  		}
  		if(next_max_ind<a[i].sc){
  			next_max_ind = a[i].sc;
  		}
  		prev = curr;

  }
  if(break_point!=-1){
  	for(i=ibp;i>=0;i--){
  		if(break_point==a[i].fr){
  			if(next_max_ind<a[i].sc){
  				printf("%d ",a[i].fr);
  			}
  			else{
  				printf("%d ",a[i].fr+1);
  			}
  		}
  		else{
  			printf("%d ",a[i].fr+1);
  		}
  	}
  }
  putchar('\n');
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
