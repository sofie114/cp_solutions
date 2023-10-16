#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define umap unordered_map
#define vo vector
#define ar array
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;
int const mxn = 1e6, lg = 20;
int up[mxn][lg], tin[mxn], tout[mxn], height[mxn];
vo<int> adj[mxn];
int timer = 0, n;

void dfs(int at, int p, int h){
    tin[at] = timer; timer++; height[at] = h;
    up[at][0] = p;
    rep(i, 1, lg){
        up[at][i] = up[up[at][i-1]][i-1];
    }

    for(auto x: adj[at]){
        if(x!=p) dfs(x, at, h);
    }
    tout[at] = timer; timer++;
}

bool is_ancestor(int a, int c){ //ancestor child
    return tin[a]<tin[c]&&tout[a]>tout[c]; 
}

int lca(int x, int y){
    if(is_ancestor(x, y)) return height[y]-height[x];
    if(is_ancestor(y, x)) return height[x]-height[y];
    for(int i=lg; i>=0; i--){
        if(!is_ancestor(up[x][i], y)){
            x = up[x][i];
        }
    }
    return up[x][0];
}

int main(){
    cin >> n;
    rep(i, 0, n-1){
        int a, b;
        cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs(0, 0, 0);
    ll ct = 0;
    rep(i, 0, n){
        rep(k, 0, 10){
            cout << up[i][k] << " ";
        }
        cout << endl;
    }

    rep(x, 1, n){
        int i=2;
        for(int y=i*x; y<=n; i++){
                pr(i, ct);
                ct += lca(x, y);
        }
    }
    cout << ct;

}