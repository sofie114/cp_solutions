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

//go for outline with ;, then details
int const inf = LLONG_MAX, mxn = 2e5+3, mxlog=20;
int n, q, arr[mxn], tin[mxn], tout[mxn], timer, seg[4*mxn];
vo<vi> adj(mxn);

void upd(int v, int l, int r, int pos, int newval){
    if(l==r){
        seg[v] = newval;
        return;
    }
    int mid = (l+r)/2;
    if(pos<=mid) upd(v*2+1, l, mid, pos, newval);
    else upd(v*2+2, mid+1, r, pos, newval);
    seg[v] = seg[v*2+1]+seg[v*2+2];
}

int qry(int v, int l, int r, int ql, int qr){
    if(l>=ql && r<=qr) return seg[v];
    else if(l>qr || r<ql) return 0;

    int mid = (l+r)/2;
    return qry(v*2+1, l, mid, ql, qr) + qry(v*2+2, mid+1, r, ql, qr);
}

void dfs(int at, int p){
    tin[at] = timer++; 

    for(auto x: adj[at]){
        if(x!=p){
            dfs(x, at);
        }
    }
    tout[at] = timer;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    rep(i, 0, n) cin>>arr[i];
    rep(i, 0, n-1){
        int a, b; cin>>a>>b; a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }

    dfs(0, 0);
    // initialize
    rep(i, 0, n){
        upd(0, 0, n-1, tin[i], arr[i]);
    }

    rep(_, 0, q){
        int type; cin>>type;
        if(type==1){
            int v, newval; cin>>v>>newval; v--;
            upd(0, 0, n-1, tin[v], newval);
        }
        else{
            int v; cin>>v; v--;
            cout << qry(0, 0, n-1, tin[v], tout[v]-1) << "\n";
        }
    }
}
