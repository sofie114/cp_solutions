#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define pb push_back
#define umap unordered_map
typedef long long ll;

#define rep(i, a, b) for(ll i = (a); i<b; i++)
#define pr(a, b) cout << #a << ", " << #b << "=" << a << ", " << b << endl
ll const mxn = 500010;
int n;
vo<int> rcv;
umap<ll, ll> memo;


int main(){
    cin >> n;
    rep(i, 0, 101){
        rep(t, i*n, i*n+n) cout << t << " ";
        cout << endl;

        ll cookie;
        cin >> cookie;
        rep(i, 0, rcv.size()){
            if(memo.count(cookie+rcv[i])){
                //literally solve question
            }else{
                dp[rcv[i]+cookie] = 1;
            }
        }         
        rcv.pb(cookie);
    }
}