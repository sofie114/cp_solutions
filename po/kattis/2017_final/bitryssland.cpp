#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()i
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
#define print(...) {cout << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cout << arg << ", ";
    print_vars(args...);
}

ll pro(ll b, ll e){
    ll x = 1;
    rep(i, 0, e) x*=b;
    return x;
}


int const mxn = 50;
ll n, m, coins[mxn], prod[mxn];
bool ans = 1;

int main(){
    cin >> n >> m;
    rep(i, 0, n) {
        cin >> coins[i];
        prod[i] = pro(2, i);
    }
    rep(i, 0, m){
        ll cost; cin >> cost;
        while(cost>0){
            ll wk=-1;
            rep(u, 0, n){
                if(prod[u]>cost) break;
                if(coins[u]>0) wk = u;
            }
            if(wk==-1) {ans = 0; break;}
            ll x = min(cost/prod[wk], coins[wk]);
            cost-=x*prod[wk];
            coins[wk]-=x;
        }

    }
    if(ans) cout << "ja";
    else cout << "nej";

}