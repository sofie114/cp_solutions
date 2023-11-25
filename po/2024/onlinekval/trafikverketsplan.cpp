#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr2(x) cerr << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr1(x) {cerr << x << " ";} cerr << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
#define pr(...) {cerr << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cerr << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cerr << arg << ", ";
    print_vars(args...);
}
//använd bitsets
int const mxn = 3*1e5+10, mxlog=25;
ll n, q, tin[mxn], tout[mxn], up[mxn][mxlog], timer, vis[mxn], dir[mxn][mxlog];
vo<ar<int, 2>> adj[mxn];

void dfs(int at, int par){
    tin[at] = timer++; 
    up[at][0] = par;  //could this be a problem?

    for(auto x: adj[at]){
        if(x[0]!=par){
            if(x[1]==x[0]) dir[x[0]][0] = -2;
            else dir[x[0]][0] = 2;

            dfs(x[0], at);
        }
    }

    tout[at] = timer++;
}   


bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

string lca(int u, int v, int des){ //des is desired direction first

    int anc;
    for (int i = mxlog-1; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)){ //om samma nod, returnerar också anc
            // pr(u, i, dir[u][i]);
            if(dir[u][i] != des && dir[u][i] != -1) return "nej";
            u = up[u][i];
        }
    }
    // pr(u, v, dir[u][0]);
    if(dir[u][0] != des && dir[u][0] != -1) return "nej";
    if(up[u][0]==v) return "ja";

    anc = up[u][0];
    for (int i = mxlog-1; i >= 0; --i) {
        if (!is_ancestor(up[v][i], anc)){
            // pr(v, i, dir[v][i])
            if(dir[v][i] != -des && dir[v][i] != -1) return "nej";
            v = up[v][i];
        }
    }
    if(dir[v][0] != -des && dir[v][0] != -1) return "nej";
    if(up[v][0]==anc) return "ja";

    return "ja";
}

int main(){
    cin >> n;
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb({b, b}), adj[b].pb({a, b});
    }

    memset(dir, -1, sizeof(dir)); //grovt misstag möjligen, checka om jag vill ändra -1, 0, 1, plus vad är relationen mellan en själv
    dfs(0, 0);

    rep(i, 1, mxlog){
        rep(u, 0, n){
            up[u][i] = up[up[u][i-1]][i-1];
        }
    }

    rep(i, 1, mxlog){
        rep(u, 0, n){
            // if(u==2) pr(i, u, dir[u][i-1], dir[up[u][i-1]][i-1]);
            if(dir[u][i-1] + dir[up[u][i-1]][i-1] == 0 || dir[u][i-1]==0 || dir[up[u][i-1]][i-1] == 0) dir[u][i] = 0;
            else dir[u][i] = dir[u][i-1];
        }
    }

    // rep(i, 0, n){
    //     rep(u, 0, mxlog){
    //         cout << dir[i][u] <<  " ";
    //     }cout << endl;
    // }

    cin >> q;
    rep(i, 0, q){
        int h, w; cin >> h >> w; h--, w--;
        if(h==w) cout << "ja" << endl;
        else if(is_ancestor(h, w)) cout << lca(w, h, -2) << endl;
        else cout << lca(h, w, 2) << endl;
    }
}

/*
root the tree, assign if root can reach v or v can reach root
find lca for each query, 
list with if you can reach 2^j nodes above you
not checking whether same node as oneself in each query
*/
