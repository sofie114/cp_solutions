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
int const inf = 1e15, mxn = 1e5+4, mxlog=20;
int n, q, s, e, tin[mxn], tout[mxn], dep[mxn], timer, up[mxn][mxlog], shops[mxn];
int dist[mxn]; //from root
vi dp; //stores (distance to closest shop in subtree) + (distance to root, aka e)
int liftdp[mxn][mxlog];
vo<vo<array<int, 3>>> adj;

int dfs(int at, int p, int depth, int d){ // return distance to closest shop
    tin[at] = timer++; dep[at] = depth; dist[at] = d;
    up[at][0] = p;
    rep(k, 1, mxlog){
        up[at][k] = up[up[at][k-1]][k-1];
    }

    int ret = inf;
    for(auto [x, w, edgeind]: adj[at]){
        if(x!=p){
            ret = min(ret, w+dfs(x, at, depth+1, d+w)); 
        }
    }
    tout[at]=timer;
    if(shops[at]) ret = 0;
    
    if(ret==inf) dp[at] = inf;
    else dp[at] = ret - dist[at];
    return ret;
}
void dfsDP(int at, int p){
    liftdp[at][0] = dp[p];
    rep(k, 1, mxlog){
        liftdp[at][k] = min(liftdp[at][k-1], liftdp[up[at][k-1]][k-1]);
    }

    for(auto [x, w, edgeind]: adj[at]){
        if(x!=p) dfsDP(x, at);
    }
}
bool is_ancestor(int u, int v){
    return tin[u]<=tin[v]&&tout[u]>=tout[v];
}
int binary_lift(int v, int d){
    int ret = dp[v];
    rep(i, 0, mxlog){
        if((d>>i) & 1){
            ret = min(ret, liftdp[v][i]);
            v = up[v][i];
        }
    }

    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>s>>q>>e; e--;
    adj.resize(n); vo<pii> edgetonode(n); dp.resize(n);
    rep(i, 0, n-1){
        int a, b, w; cin>>a>>b>>w; a--, --b;
        adj[a].pb({b, w, i}), adj[b].pb({a, w, i});
        edgetonode[i] = {a, b};
    }

    rep(i, 0, s){
        int c; cin>>c; c--;
        shops[c] = 1;
    }  

    // preprocess
    dfs(e, e, 0, 0);
    dfsDP(e, e);

    // process queries
    rep(_, 0, q){
        int edge, v; cin>>edge>>v; edge--, v--;
        // check if escapable: push blocked edge to deeper node and check if it is ancestor to village r
        auto [a, b] = edgetonode[edge]; if(dep[a] > dep[b]) swap(a, b);
        if(is_ancestor(b, v)){
            int ret = binary_lift(v, dep[v]-dep[b]); 

            if(ret==inf) cout << "oo\n";
            else cout << ret + dist[v] << "\n";
        }
        else{
            cout << "escaped\n";
        }
    }
}
/*
subtask 1: line graph, store index of root (escape), note the restraints, binary search is overkill but i used it to practice
subtask 2: perform dijkstra, realize that this solves subtask 1 as well (really important)
subtask 3: there is a shop on every node, we only need to quickly check if we can escape, root tree by exit and 
push down blocked edge to deeper node and check if this deeper node is an ancestor to our query node v. use euler tour tin, tout.
 
full solution: 
b = the deeper node of the blocked edge. if we cannot escape, v is in the subtree of b and we want to check for a shop
within the same subtree. 
the distance to a shop w from v is: dist[b] + dist[w] - 2*dist[lca(b, w)] where dist[i]=distance from root e to node i.
for each node we store dp[node] = distance to closest shop in subtree of node. 

now we want to a node on the path between v and b that has the smallest dp[node]. it is a common algorithm to find the minimum value of something
on a path in a tree - binary lifting.
*/
