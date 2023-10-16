#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define ar array
#define umap unordered_map
#define pb push_back
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;
int const mxw = 250000, M=1000000007;

ll fib[mxw+1];
ll memo[mxw], accu[mxw];

int main(){
    int w, h;
    cin >> w >> h;
    fib[1] = 1, fib[2] = 2;
    memo[1] = 1;
    rep(i, 2, w+1){
        if(2!=fib[i]) fib[i] = (fib[i-1]+fib[i-2])%M;
        memo[i] = 1;
        rep(k, 0, h){
            memo[i]=(memo[i]*fib[i])%M;
        }
    }

    rep(i, 0, w+1) cout << fib[i] << " ";
    cout<<endl;
    rep(i, 0, w+1) cout << memo[i] << " ";
    cout << endl;
    rep(i, 0, w+1) cout << accu[i] << " ";
    
    ll ans = 1;
    rep(i, 0, h) ans = (ans*fib[w])%M; // might be wrong

    ll rem = 0;
    rep(i, 1, w){
        ll erl = 0, full = memo[i], ri=memo[w-i];
        rep(k, 1, i){
            erl+=memo[i-k]*memo[k];
            erl%=M;
        }
        pr(full, erl); 
        pr(ri, 1);
        if(erl>full) full+=M;
        rem+=(ri)*(full-erl);
        rem%=M;
    }

    pr(ans, rem);
    if(ans>rem) cout << ans-rem;
    else cout << ans+M-rem;
}

//81+240+

//lego ide
// for all 1 to n-1 cracks, find amount of ways by multply left and right. Use fibonacci precomputed.
// for cracks also subtract to not recompute, subtract fib(c (crack) - 1) from left*right.
// times 2 in the end?







