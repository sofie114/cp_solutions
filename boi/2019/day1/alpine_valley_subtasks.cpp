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
int const inf = LLONG_MAX, mxn = 1e5+4;
int n, s, q, e, pref[mxn];
vo<vo<array<int, 3>>> adj;
 
int dist(int l, int r){
    // pr(l, r, pref[r], pref[l])
    return pref[r]-pref[l];
}
void line_graph_binary(){
    cin>>n>>s>>q>>e; e--;
    set<pii> inp; vo<pii> edgeToV(n-1);
    rep(i, 0, n-1){
        int a, b, w; cin>>a>>b>>w; a--, b--;
        edgeToV[i] = {min(a, b), max(a, b)};
        inp.insert({max(a, b), w});
    }
    for(auto [b, w]: inp) {
        pref[b] = pref[b-1]+w;
    }
    set<int> shops;
    rep(i, 0, s){
        int c; cin>>c; c--;
        shops.insert(c);
    }
 
    rep(i, 0, q){
        int edge, v, ans = inf; cin>>edge>>v; v--; edge--;
        auto [a, b] = edgeToV[edge];
        // pr(a, b, v, e)
        if((e<b && a < v) || (e>a && b>v)){
            auto it = shops.lower_bound(v);
            if(it!=shops.end()){
                if(*it < b || a < v) ans = dist(v, *it);
            }
            if(it!=shops.begin()){
                it--; 
                if(v < b || a < *it) ans = min(ans, dist(*it, v));
            }
            if(ans==inf) cout << "oo\n";
            else cout << ans << "\n";
        }
        else{
            cout << "escaped\n";
        }
    }
}
void line_graph(){
    cin>>n>>s>>q>>e; e--;
    vo<pii> edgeToV(n-1); vi wei(n, 0);
    rep(i, 0, n-1){
        int a, b, w; cin>>a>>b>>w; a--, b--;
        edgeToV[i] = {min(a, b), max(a, b)};
        wei[min(a, b)] = w;
    }
 
    vi shops(n, 0);
    rep(i, 0, s){
        int c; cin>>c; c--;
        shops[c] = 1;
    }
 
    rep(_, 0, q){
        int edge, v; cin>>edge>>v; v--; edge--;
        auto [a, b] = edgeToV[edge];
        if((v>a && e>a) || (v<b && e<b)){
            cout << "escaped\n";
        }
        else{
            int ans = inf, d = 0;
            rep(i, v, n){
                if(shops[i]){
                    ans = min(ans, d);
                    break;
                }
                if(i==a) break;
                d+=wei[i];
            }
            d=0;
            repd(i, 0, v){
                if(i==a) break;
                d+=wei[i];
                if(shops[i]){
                    ans = min(ans, d);
                    break;
                }
            }
 
            if(ans==inf) cout << "oo\n";
            else cout << ans << "\n";
        }
    }
}
void dijkstra_sol(){
    cin>>n>>s>>q>>e; e--; adj.resize(n);
    rep(i, 0, n-1){
        int a, b, w; cin>>a>>b>>w; a--, b--; 
        adj[a].pb({b, w, i}), adj[b].pb({a, w, i});
    }
 
    vi shops(n, 0);
    rep(i, 0, s){
        int c; cin>>c; c--;
        shops[c] = 1;
    }  
 
    rep(_, 0, q){
        int edge, v; cin>>edge>>v; edge--, v--;
        priority_queue<pii, vo<pii>, greater<pii>> pq;
        vi dist(n, inf); dist[v] = 0;
        pq.push({0, v});
        int ans = inf;
 
        while(pq.size()){
            auto [d, at] = pq.top(); pq.pop();
            if(at==e) {ans = -inf; break;}
            if(dist[at] < d) continue;
            if(shops[at]){
                ans = min(ans, d);
            }
            for(auto [x, w, edgeind]: adj[at]){
                if(edgeind == edge) continue;
                if(d+w < dist[x]){
                    dist[x] = d+w;
                    pq.push({dist[x], x});
                }
            }
        }
 
        if(ans==-inf) cout << "escaped\n";
        else if(ans==inf) cout << "oo\n";
        else cout << ans << "\n";
 
    }
}
 
 
int tin[mxn], tout[mxn], timer, dep[mxn];
void dfs(int at, int p, int depth){
    tin[at] = timer++; dep[at] = depth;
    for(auto [x, w, edgeind]: adj[at]){
        if(x!=p) dfs(x, at, depth+1); 
    }
    tout[at]=timer;
}
bool is_ancestor(int u, int v){
    return tin[u]<=tin[v]&&tout[u]>=tout[v];
}
void euler_sol(){
    cin>>n>>s>>q>>e; e--; adj.resize(n);
    vo<pii> edgetonode(n);
    rep(i, 0, n-1){
        int a, b, w; cin>>a>>b>>w; a--, b--; 
        adj[a].pb({b, w, i}), adj[b].pb({a, w, i});
        edgetonode[i] = {a, b};
    }
    vi shops(n, 0);
    rep(i, 0, s){
        int c; cin>>c; c--;
        shops[c] = 1;
    }  
    dfs(e, e, 0);
 
    rep(_, 0, q){
        int edge, v; cin>>edge>>v; edge--, v--;
        // check if escapable: push blocked edge to deeper node and check if it is ancestor to village r
        int node = edgetonode[edge].fi; if(dep[edgetonode[edge].se] > dep[node]) node = edgetonode[edge].se;
        if(is_ancestor(node, v)){
            cout << 0 << "\n";
        }
        else{
            cout << "escaped\n";
        }
    }
}
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // line_graph();
    // line_graph_binary();
    // dijkstra_sol();
    // euler_sol();
 
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
