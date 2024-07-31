#include <assert.h>
#include <stdio.h>

int parityShouldMatch(int x,int p_x){
    return ((x==p_x)?(1):(0));
}

// we keep removing bit set at large position if its not set then previous bit will be set
// which can be cleared by next move which clears the previous set bit. 

void solve(){
    int n,i,x,all_true=1,p_x=0;
    assert(fscanf(stdin,"%d",&n)>0);
    for(i=0;i<n;i++){
        assert(fscanf(stdin,"%d",&x)>0);
        all_true &= ((parityShouldMatch(x&1,p_x))||(i==0));
        p_x = (x%2);
    }
    if(all_true){ /*all elements have matching parity*/
        printf("%d\n",30+(!p_x)); // if all elements are even parity ends with 0 so we need extra one 
        for(i=29;i>=0;i--){ /*total operation that has to be performed is 30 [0-29]*/
            printf("%d ",(1<<i));
        }
        if(!p_x){/*extra one for even parity case*/
            printf("1");
        }
        printf("\n");
    }
    else{
        printf("-1\n"); /* not all elements have same parity*/
    }
    return;
}

int main()
{
    int tt=1;
    assert(fscanf(stdin,"%d",&tt)>0);    
    while(tt--){
        solve();
    }
    return 0;
}
