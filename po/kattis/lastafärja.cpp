#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr2(x) cerr << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr1(x) {cerr << x << " ";} cerr << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
#define pr(...) {cerr << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cerr << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cerr << arg << ", ";
    print_vars(args...);
}
//go for outline with ;, then details
int const mxn = 210, mxl=63;
ll n, l, bilar[mxn], dp[mxl][mxl][mxl][mxl];
umap<ll, ll> pref;

ll antal(ll a, ll b, ll c, ll d){
    if(!pref.count(a+b+c+d)){
        if(a <= l && b <= l && c<=l && d <= l){
            return n-1;
        }   
        else return -2;
    }


    ll ans=-2, ind = pref[a+b+c+d];
    if(a > l || b > l || c > l || d > l){
        return -2;
    }  
    else{
        ans = max(ans, ind-1);
    }   

    rep(i, 0, 4){
        vo<ll> v = {a, b, c, d};
        ll ac[4] = {0, 0, 0, 0}; ac[i] = 1;
        rep(u, 0, 4){
            v[u] += ac[u]*(bilar[ind]+1);
        }
        sort(v.begin(), v.end());
        
        if(v[0] > l || v[1] > l || v[2] > l || v[3] > l){ continue;
        }

        if(dp[v[0]][v[1]][v[2]][v[3]] == -1) dp[v[0]][v[1]][v[2]][v[3]] = antal(v[0], v[1], v[2], v[3]);
        ans = max(ans, dp[v[0]][v[1]][v[2]][v[3]]);

    }

    return ans;
}

int main(){
    cin >> n >> l; l++;
    memset(dp, -1, sizeof(dp));
    dp[0][0][0][0] = 0;

    ll prev = 0;
    rep(i, 0, n) {
        pref[prev] = i;
        cin >> bilar[i];
        prev += bilar[i]+1;
    }

    cout << antal(0, 0, 0, 0)+1;
 
}
