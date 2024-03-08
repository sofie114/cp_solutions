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
ll const inf = LLONG_MAX, mxn = 1e5+4;
int n, r, m, vis[mxn], label[mxn];
vo<vi> adj(mxn), radj(mxn); //node and edgetype
vi order;
vo<vi> comps; 
map<pii, int> edges, redges; //edge to edgetype

struct DSU{
    vi par, rnk;
    DSU(int n): par(n), rnk(n, 0){
        rep(i, 0, n) par[i] = i;
    }

    int findpar(int v){
        if(par[v]==v) return v;
        return par[v] = findpar(par[v]);
    }

    void unite(int a, int b){
        a = findpar(a), b = findpar(b);

        if(a!=b){
            if(rnk[a] < rnk[b]) swap(a, b);
            par[b] = a;
            if(rnk[a]==rnk[b]) rnk[a]++;
        }
    }
};

void dfs(int at){
    vis[at] = 1;
    for(auto x: adj[at]){
        if(!vis[x])
            dfs(x);
    }
    order.pb(at);
}

void fail(){
    cout << -1; exit(0);
}
void dfs2(int at){
    vis[at] = 1;
    comps.back().pb(at);
    for(auto x: radj[at]){
        if(!vis[x]){
            dfs2(x);
            int edgetype = redges[{at, x}];
            if(edgetype == 1) fail();
        }
            
    }
}

int dfs3(int at, struct DSU &g){
    vis[at] = 1;

    int mini = r;
    for(auto x: adj[at]){
        int tmp;
        if(!vis[x]) tmp = dfs3(x, g);
        else tmp = label[x];

        int edgetype = edges[{at, x}];
        if(edgetype==1){
            mini = min(mini, tmp-1);
        }
        else{
            mini = min(mini, tmp);
        }

    }

    if(mini < 1) fail();
    label[at] = mini;
    return mini;
}


signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>r>>m; //oops blandade ihop r och m
    DSU g(n);
    vo<array<int, 3>> tmpedges;
    rep(i, 0, m){
        int a, b; string c; 
        cin>>a>>c>>b;
        a--, b--;
        if(c=="<"){
            tmpedges.pb({a, b, 1});
        }
        else if(c=="<="){
            tmpedges.pb({a, b, 2});
        }
        else{
            g.unite(a, b);
        }
    }

    for(auto [a, b, edgetype]: tmpedges){
        a = g.findpar(a), b = g.findpar(b);
        if(a!=b){
            if(edges.count({a, b})){
                if(edges[{a, b}] == 2) {
                    edges[{a, b}] = edgetype;
                    redges[{b, a}] = edgetype;
                }
            }
            else {
                edges[{a, b}] = edgetype;
                redges[{b, a}] = edgetype;     
            }
            adj[a].pb(b);
            radj[b].pb(a);
        }
    }


    //find SCC
    rep(i, 0, n){
        int v = g.findpar(i);
        if(!vis[v]) dfs(v);
    }
    reverse(all(order));

    memset(vis, 0, sizeof(vis));
    rep(i, 0, sz(order)){
        int v = g.findpar(order[i]);
        if(!vis[v]){
            comps.pb({});
            dfs2(v);
        }
    }
    //kolla om scc bara är <= kanter
    rep(i, 0, sz(comps)){
        if(sz(comps[i]) == 1) continue;
        int N = sz(comps[i]);
        rep(u, 1, N){
            g.unite(comps[i][0], comps[i][u]);
        }
    }

    //new adj
    adj.clear(); adj.resize(n); edges.clear(); 
    for(auto [a, b, edgetype]: tmpedges){
        a = g.findpar(a), b = g.findpar(b);
        if(a!=b){
            if(edges.count({a, b})){
                if(edges[{a, b}] == 2) {
                    edges[{a, b}] = edgetype;
                }
            }
            else {
                edges[{a, b}] = edgetype;
            }
            adj[a].pb(b);
        }
    }

    memset(vis, 0, sizeof(vis));
    rep(i, 0, n){
        int v = g.findpar(i);
        if(!vis[v]) dfs3(v, g);
    }

    rep(i, 0, n){
        int v = g.findpar(i);
        cout << label[v] << " ";
    }

}



