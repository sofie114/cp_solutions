#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vo vector
#define pb push_back
#define se second
#define fi first
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef pair<int, int> pii;
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define repd(i, a, b) for(int i=(b-1); i >= a; i--)
void _pr(signed x) {cerr << x;}
void _pr(long long x) {cerr << x;}
void _pr(size_t x) {cerr << x;}
void _pr(double x) {cerr << x;}
void _pr(char x) {cerr << '\'' << x << '\'';}
void _pr(const char* x) {cerr << x;}
void _pr(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x) {cerr << "\e[95m" << "[ "; _pr(x.first); cerr << ", "; _pr(x.second); cerr << "\e[95m" << ']';}
template<typename T> void _pr(const T &x) {int F=0; cerr << '{'; for(auto &i: x) cerr << (F++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

//go for outline with ;, then details
int const inf = LLONG_MAX, mxn = 2e5+4;
int n, m;
vo<vo<pii>> adj(mxn);
vo<pair<int, double>> dp;

pair<int, double> test(double val, int at){
    if(at==n-1) return {1, 0};
    if(dp[at].fi != -1) return dp[at];

    pair<int, double> ret = {0, -1e6};
    for(auto [x, d]: adj[at]){
        auto [yes, trevlig] = test(val, x); 
        if(yes){
            ret.fi = 1;
            ret.se = max(ret.se, trevlig+d-val);
        } 
    }
    dp[at] = ret;

    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    rep(i, 0, m){
        int a, b, c; cin>>a>>b>>c;
        a--, b--;
        adj[a].pb({b, c});
    }

    double lo=0, hi=2e6+2;
    rep(i, 0, 50){
        double mid = (lo+hi)/2;
        dp.assign(n, {-1, 0});
        auto [a, ret] = test(mid, 0);

        if(ret >= (double)0) lo = mid;
        else hi = mid;
    }

    cout << fixed << setprecision(7) << lo;
}
