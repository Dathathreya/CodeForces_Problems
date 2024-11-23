//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  
  public:
    // Function to count inversions in the array.
        typedef int compare_self_t(const void* ar,int fr,int sc);
        typedef void swap_self_t(const void* ar,int fr,int sc);
        int cnt = 0,tot_sz=0,mxvalue=-1;
        #define N ((int)1e5+4)
        typedef struct pair{
            int value,position;
        }pii;
        pii arr1[N];int ft[N];
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
        static int compare_self_pair(const void* arr,int f,int s){
            pii* a1 =(pii*)arr;
            if((a1[f].value)==(a1[s].value)){
                return (a1[f].position)<(a1[s].position);
            }
            return (a1[f].value)<(a1[s].value);
        }
        
        static  void swap_self_pair(const void *arr,int f,int s){
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
                cnt += _cnt; 
                swapfn(arr,low,end);    
                fwk_update(pos,-1,tot_sz);
                heapify(arr,low,end,compfn,swapfn);    
            }
        }
    int inversionCount(vector<int> &arr) {
        // Your Code Here
        int sz = arr.size();
        tot_sz = sz;
        cnt = 0;
        memset(ft,0,sizeof(ft));
        for(int i=0;i<sz;i++){
            arr1[i].value=arr[i];
            arr1[i].position=i;
            fwk_update(i,1,tot_sz);
        }
        heapSort(arr1,0,tot_sz-1,compare_self_pair,swap_self_pair);
        return  cnt;
    }
};

//{ Driver Code Starts.

int main() {

    int T;
    cin >> T;
    cin.ignore();
    while (T--) {
        int n;
        vector<int> a;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int num;
        while (ss >> num)
            a.push_back(num);
        Solution obj;
        cout << obj.inversionCount(a) << endl;
        cout << "~" << endl;
    }

    return 0;
}

// } Driver Code Ends
