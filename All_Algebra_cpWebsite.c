#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
// https://codeforces.com/contest/630/problem/I
typedef long double ld;
typedef long long ll;
typedef long long unsigned llu;

int binPow(int base,int exponent,int mod){
	int res = 1;
	while(exponent){
		if(exponent&1) {
						res = ((res%mod)*(base%mod))%mod;
						if(res<=0) res+=mod;
						if(res>=mod) res-=mod;
						}
		base = ((base%mod)*(base%mod))%mod;
		if(base<=0) base+=mod;
		if(base>=mod) base-=mod;
		exponent >>= 1;
	}
	return res;
}

llu binPowM(llu base,llu exponent){
	llu res = 1llu;
	while(exponent){
		if(exponent&1){
			res *= base;
		}
		base *= base;
		exponent >>= 1;
	}
	return res;
}

int lastThreeDigits(int base,int exponent){
	int res = 1;
	base %= 1000L;
	while(exponent){
		if(exponent%2) res = (res*base)%1000L;
		base = (base*base)%1000L;
		exponent >>= 1L;
	}
	return res;
}

void printfirst3_last3(int base,int exponent){
	ld expo1 = (ld)exponent*log10(base);
	int first3digits = pow(10,expo1-floor(expo1))*100;
	printf("%d...%d\n",first3digits,lastThreeDigits(base,exponent));
}


// n=6 
// 2*n-2 = 12 - 2 = 10 
// ____MMMMMM = 3*4^3
// ____MMMMMM = 3*4^3
// __MMMMMM__ = ((3^2)*(4^2))*(repeat+1) times 
// ___MMMMMM_ 

void solve(){
	int n,repeat;
	assert(fscanf(stdin,"%d",&n)>0);
	repeat  = 2*n-2-n;
	llu answer = 1llu*2*3*4*((repeat>1)?(binPowM(4,repeat-1)):(0));	// first and last
	answer += (1llu*4*((n>3)?(9):(3))*((repeat>=2)?(1llu*(repeat+1-2)*binPowM(4,repeat-2)):(repeat+1)));
	printf("%llu\n",answer);
}

int main(int argc,char* argv[]){
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

// n = 5
// 2*n-2 = 10 - 2 = 8 
// ___MMMMM = 3*4^2
// __MMMMM_ = 3^2*4^1
// _MMMMM__ = 3^2*4^1
// MMMMM___ = 3*4^2
// _ _ _ _ _ _
//  G G G G G

// _ _ _ _

	// 1*2*4*3*4^(8-5-1) = 2*4*3*4^2 // mSSS,SSSm
	// SmSS,SSmS
    // 4*(3^2)*4*(8-5-2) = 
