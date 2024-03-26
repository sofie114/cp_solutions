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
int const inf = LLONG_MAX, mxn = 3e3+4;
int n, m, ans, vis[mxn], siz[mxn];
vo<set<pii>> adj(mxn);
vo<pii> st; //ind and parnode

struct dsu{ 
    vi par, sz;
    dsu(int n): par(n), sz(n, 1){
        iota(all(par), 0);
    }

    int find(int v){
        if(v==par[v]) return v;
        return par[v] = find(par[v]);
    }
    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a!=b){
            if(sz[b] > sz[a]) swap(a, b);
            par[b] = a;
            sz[a]+=sz[b];
        }
    }
};

map<int, pii> ind;
int dfs(int at, int pi){ //edgeind or biggest edge
    for(auto [x, i]: adj[at]){
        if(i == pi) continue;
        if(vis[x]){
            int maxi = siz[i], ret = i;
            while(1){
                pii tmp = st.back(); st.pop_back();
                if(siz[tmp.fi] > maxi){
                    maxi = siz[tmp.fi]; ret = tmp.fi;
                }

                if(tmp.se == x) break; 
            }
            return ret;
        }
        else{
            vis[x] = 1;
            st.pb({i, at});
            int tmp = dfs(x, i);
            if(tmp != -1) return tmp;
            st.pop_back();
        }
    }

    return -1;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    map<int, vi> edg;

    rep(i, 0, m){
        int a, b, c; cin>>a>>b>>c; a--, --b;
        edg[c].pb(i); siz[i] = c; ind[i] = {a, b};

        if(i<n-1){
            adj[a].insert({b, i});
            adj[b].insert({a, i});
        }
    }

    vi dif; //dif edges in mst with max overlap
    dsu g(n); 
    for(auto [size, cont]: edg){
        for(auto v: cont){
            if(v < n-1){ //mitt träd
                auto [a, b] = ind[v];
                g.unite(a, b);
            }
        }
        for(auto v: cont){
            auto [a, b] = ind[v];
            if(g.find(a) != g.find(b)){
                g.unite(a, b);
                dif.pb(v);
            }
        }
    }

    vo<pii> swaps;
    for(auto v: dif){
        auto [a, b] = ind[v];
        adj[a].insert({b, v}); adj[b].insert({a, v});
        memset(vis, 0, sizeof(vis)); vis[a] = 1; st.clear();
        int big = dfs(a, a); 
        // remove 
        auto [a1, b1] = ind[big];
        adj[a1].erase({b1, big}), adj[b1].erase({a1, big});
        ans++; swaps.pb({v, big});
    }

    cout << ans << endl;
    rep(i, 0, ans) cout << swaps[i].se+1 << " " << swaps[i].fi+1 << "\n"; 
}

/*
find mst with closest resemblance
take different edges one by one: 
    add, find single cycle, remove biggest edge
*/
