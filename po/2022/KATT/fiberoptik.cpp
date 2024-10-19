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

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define umap unordered_map
#define uset unordered_set
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
mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){return uniform_int_distribution<int>(l, r)(mt_rng);}

//go for outline with ;, then details
int const inf = 1e10, mxn = 1e5+4;
int n, k;
vo<vo<pii>> adj(mxn);

pair<pii, pii> dfs(int at, int p){  //best ans using k, best ans using k-1
    vo<pii> dp(k+1, pii{-inf, -inf}); dp[0] = {0, 0};
    pair<pii, pii> ret = {{0, 0}, {0, 0}};

    for(auto [x, w]: adj[at]){
        if(x!=p){
            pair<pii, pii> tmp = dfs(x, at); 

            repd(i, 0, k+1){
                dp[i] = max(dp[i], {dp[i].fi+tmp.fi.fi, dp[i].se+tmp.fi.se});
                if(i > 0) dp[i] = max(dp[i], {dp[i-1].fi+tmp.se.fi+1, dp[i-1].se+tmp.se.se+w});
            }
        }
    }
    ret.fi = *max_element(dp.begin(), dp.begin()+k+1);
    ret.se = *max_element(dp.begin(), dp.begin()+k);

    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    rep(i, 1, n){
        int v, w; cin>>v>>w; v--;
        adj[i].pb({v, -w}), adj[v].pb({i, -w});
    }
    pii op = dfs(0, 0).fi;
    cout << op.fi << " " << -op.se << endl;
}

/*
subtask 6: greedy tree dp - do dfs, place out as many edges as possible in subtree. 
full solution: 

uses a knapsack idea. 

perform a dfs and at each node return a two pairs for using k edges and k-1 edges: 
    ret = {{#edges using k edges for this node, min edgesum}, {#edges for max k-1 for this node, min edgesum}}
    dp[i] = max edges using i edges. 
        view the children as items and k as the knapsack capacity, pick k children such that the edgesum is minimized
        knapsack trick: iterate in reverse order 

new trick: we can maximize both #edges and edgesum by changing weights to negative. 
time complexity: n*k = 1e8 
*/
