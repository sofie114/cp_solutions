#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
#define rs(x, a) x.resize(a)
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
#define pren cerr << endl;
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define trav(item, arr) for (auto &item: arr)
void _pr(int x) {cerr << x;}
void _pr(long long x) {cerr << x;}
void _pr(unsigned long long x) {cerr << x;}
void _pr(double x) {cerr << x;}
void _pr(char x) {cerr << '\'' << x << '\'';}
void _pr(const char* x) {cerr << x;}
void _pr(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x) {cerr << "\e[95m" << "[ "; _pr(x.first); cerr << ", "; _pr(x.second); cerr << "\e[95m" << ']';}
template<typename T> void _pr(const T &x) {int f=0; cerr << "{"; for(auto &i: x) cerr << (f++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << endl;

/*
Solution: identify all cycles and view them as root with depth 0. Give depth to all nodes. 
Store component all nodes belong to, and distance between nodes in a cycle
For a query: if they belong to same component, find distance with depth + cycle dist 
*/
int const mxn=50100;
int n, q, vis[mxn], par[mxn], tin[mxn], tout[mxn], timer=0; //par stores first root of a tail
vo<vi> adj(mxn), radj(mxn); //reverse adj
umap<int, int> cycleind[mxn]; //for every root in comp, save an umap of (node, ind)
vi root, dep; //for every comp, one euler


ar<int, 2> dfs(int at){
    if(vis[at]==2){
        return {root[at], -1};
    }
    if(vis[at] == 1){
        // pr("root", at);
        root[at] = at; 
        dep[at]=0;
        cycleind[at][at] = 1;
        vis[at] = 2;
        return {at, 1}; //ind for this comp, ind of node in cycle
    }
    vis[at] = 1;

    for(auto x: adj[at]){
        ar<int, 2> ret = dfs(x);
        int source = ret[0];
        if(source!=-1){
            if(at==source){
                return {source, -1};
            }

            if(ret[1]==-1){
                vis[at] = 2; 
                root[at] = source; 
                dep[at] = dep[x]+1;
                return {root[at], -1};
            }
            
            //i am node in cycle
            root[at] = source;
            cycleind[source][at] = ret[1]+1;
            vis[at] = 2;
            return {source, ret[1]+1};
        }
    }
    vis[at] = 2;
    return {-1, -1};
}

void dfs2(int at, int source, int p){
    vis[at]=1;
    tin[at] = timer++;
    par[at] = p;

    for(auto x: radj[at]){
        if(vis[x]) continue;
        dfs2(x, source, p);
    }
    tout[at]=timer++;
}

int dist(int a, int b){
    if(dep[a] < dep[b] || root[a]!=root[b]) return -1;

    if(dep[a]>0 && dep[b]>0) {
        if(par[a]!=par[b]) return -1;

        if(tin[b]<=tin[a] && tout[b]>=tout[a]) return dep[a]-dep[b];
        else return -1;
    }

    if(dep[a]>0 && dep[b]==0){

        if(b==par[a]) return dep[a];
        int cycledist = cycleind[root[b]][par[a]] - cycleind[root[b]][b] ;
        if(cycledist < 0) cycledist+=sz(cycleind[root[b]]);
        return cycledist + dep[a];
    }

    int cycledist = cycleind[root[b]][par[a]] - cycleind[root[b]][b] ;
    if(cycledist < 0) cycledist+=sz(cycleind[root[b]]);
    return cycledist;
}

int main(){
    cin >> n; rs(root, n); rs(dep, n);

    rep(i, 0, n){
        int v; cin >> v; v--;
        adj[i].pb(v); 
        radj[v].pb(i);
    }

    rep(i, 0, n) if(!vis[i]) dfs(i);
    // pr(root) pr(dep) //perfekt det funkar!!

    memset(vis, 0, sizeof(vis));
    rep(i, 0, n){
        if(sz(cycleind[i])){
            // pr(cycleind[i])
            for(auto p:cycleind[i]){
                vis[p.first] = 1;
            }
            for(auto p: cycleind[i]) dfs2(p.first, i, p.first);
            // pr(i, euler[i])
        }
    }

    cin >> q;
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--, b--;
        cout << dist(a, b) << endl;
    }

}

/*

6
2 4 2 5 4 3

*/
