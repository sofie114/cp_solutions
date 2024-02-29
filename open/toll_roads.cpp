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

/*
Find MST. Answer first question off all queries with binary jumping with storing max edge.
Then answer all second questions offline, start with an empty graph and add edges in increasing order.
Then, check connectivity.
*/
ll const inf = LLONG_MAX, mxlog = 25, mxn = 2e5+4;
int N, M, Q, depth[mxn];
vo<vi> adj(mxn);
multiset<array<int, 3>> edges; //val, a, b
map<pii, int> edgeval;
vo<vi> up(mxn, vi(mxlog)), maxi(mxn, vi(mxlog));
vo<pair<int, pii>> queries;
vo<pii> ans(mxn);
set<array<int, 3>> treeedges;

struct DSU{
    vi par, siz;
    DSU(int n): par(n), siz(n, 1){
        rep(i, 0, n) par[i] = i;
    }

    int findpar(int v){
        if(v==par[v]) return v;
        return par[v] = findpar(par[v]);
    }

    void unite(int a, int b){
        a = findpar(a), b = findpar(b);
        if(a!=b){
            if(siz[a] < siz[b]) swap(a, b);
            par[b] = a;
            siz[a] += siz[b];
        }
    }
};

void dfs(int at, int p){
    int a, b; tie(a, b) = minmax(at, p);
    up[at][0] = p; maxi[at][0] = edgeval[{a, b}]; //what if zero

    rep(k, 1, mxlog){
        up[at][k] = up[up[at][k-1]][k-1];
        maxi[at][k] = max(maxi[up[at][k-1]][k-1], maxi[at][k-1]);
    }

    for(auto x: adj[at]){
        if(x!=p){
            depth[x] = depth[at]+1;
            dfs(x, at);
        }
    }
}
pii jump(int v, int d){ //node and maxi
    int mx = 0;
    rep(i, 0, mxlog){
        if((d>>i) & 1) {
            mx = max(mx, maxi[v][i]);
            v = up[v][i];
        }
    }
    // pr(d, v, mx)
    return {v, mx};
}
int LCA(int a, int b){ //return max in path from a to b
    if(depth[a] > depth[b]) swap(a, b);
    // pr(depth[a], depth[b])

    int mx = 0;
    tie(b, mx) = jump(b, depth[b]-depth[a]);
    if(a==b) return mx;

    repd(k, 0, mxlog){
        if(up[a][k] != up[b][k]){
            mx = max(mx, maxi[a][k]);
            mx = max(mx, maxi[b][k]);
            a = up[a][k], b = up[b][k];
            // pr(a, b, mx)
        }
    }
    // pr(a, b, mx)
    mx = max(mx, maxi[a][0]); mx = max(mx, maxi[b][0]);
    return mx;
}

void fixanswer(){
    sort(all(queries));
    DSU solve(N);
    auto it = treeedges.begin();

    int i = 0;
    while(i < Q){
        auto x = (*it); int qryind = queries[i].se.fi;
        if(x[0] > queries[i].fi || it==treeedges.end()){
            int source = solve.findpar(queries[i].se.se);
            ans[qryind].se = solve.siz[source];
            // pr(i, qryind, solve.siz[source]);
            i++;
        }
        else{
            solve.unite(x[1], x[2]);
            it++;
        }
    }
}
 

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M>>Q;

    rep(i, 0, M){
        int A, B, C; cin>>A>>B>>C; A--, B--;
        edges.insert({C, A, B});
    }

    //find mst
    DSU MST(N);
    for(auto x: edges){
        if(MST.findpar(x[1]) != MST.findpar(x[2])){
            MST.unite(x[1], x[2]);
            adj[x[1]].pb(x[2]), adj[x[2]].pb(x[1]);
            treeedges.insert(x);

            //add edges to edgeval
            if(x[1] > x[2]) swap(x[1], x[2]);
            edgeval[{x[1], x[2]}] = x[0];
        }
    }
    
    edgeval[{0, 0}] = 0;
    dfs(0, 0);

    rep(i, 0, Q){
        int a, b; cin>>a>>b;
        a--, b--;
        int mx = LCA(a, b);
        queries.pb({mx, {i, a}});
        ans[i].fi = mx;
    }

    fixanswer();
    rep(i, 0, Q) cout << ans[i].fi << " " << ans[i].se << "\n";
}
