#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vo vector
#define pb push_back
#define se second
#define fi first
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
void _pr(signed x) {cerr << x;}
void _pr(long long x) {cerr << x;}
void _pr(unsigned long long x) {cerr << x;}
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
ll const inf = 1e10, mxn = 5e4;
int n, arr[mxn];
vo<vi> adj(mxn);

pii dfs(int at){ //with and without

    pii ret = {arr[at], 0};
    for(auto x: adj[at]){
        pii tmp = dfs(x);
        ret.fi += max(-inf, max(tmp.fi-2*arr[x], tmp.se));
        ret.se += max(-inf, max(tmp.se, tmp.fi));
    }
    // pr(at, ret, adj[at])
    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>arr[0];
    rep(i, 1, n){
        int p;
        cin>>arr[i]>>p;
        adj[p].pb(i);
    }

    pii ans = dfs(0);
    cout << max(ans.fi,  ans.se);
}