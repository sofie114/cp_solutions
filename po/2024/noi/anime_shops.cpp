#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define vo vector
#define pb push_back
#define sz(x) x.size()
#define fi first 
#define se second
 
typedef long long ll;
typedef pair<int ,int> pii;
typedef vo<int> vi;
 
#define rep(i, a, b) for(ll i=(a); i<(b); i++)
#define pr(x) cerr << #x << " " << x << endl;
 
ll const inf = 1e9; 
ll const mxn = 1e5+4;
int n, m, k, anime[mxn], vis[mxn];
vo<vi> adj(mxn);
// vi dist(mxn, inf);
 
int bfs(int source){
    queue<int> qu; qu.push(source);
    vi dist(n, inf); dist[source] = 0;
 
    while(sz(qu)){
        int v = qu.front(); qu.pop();
 
        for(auto x: adj[v]){
            if(dist[x] == inf){
                dist[x] = dist[v] + 1;
                if(anime[x]) return dist[x];
                qu.push(x);
            }
        }
 
    }
    return -1;
}
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    vi dist(n, inf), par(n, -1);
    queue<array<int, 3>> qu; // node, source animenode, dist
 
    rep(i, 0, k){
        int a; cin>>a;a--;
        anime[a] = 1;
        qu.push({a, a, 0});
    }
    rep(i, 0, m){
        int a, b; cin>>a>>b; a--, b--;
        adj[a].pb(b); adj[b].pb(a);
    }
 
    while(sz(qu)){
        array<int, 3> v = qu.front(); qu.pop();
        int d = v[2], p = v[1];
        // pr(v[0])
 
        for(auto x: adj[v[0]]){
            if(x == p) continue;
            // pr(x)
            if(dist[x] == inf){
 
                dist[x] = d+1;
                par[x] = p;
                qu.push({x, p, dist[x]});
            }
            else if(anime[x]){
                dist[p] = min(dist[p], d+1);
                dist[x] = min(dist[x], d+1);
            }
            else{
 
                if(par[x] != p){
                    if(par[x] == -1) continue;
                    // pr(par[x])
                    // pr(p)
 
                    // pr(dist[p])
                    dist[p] = min(dist[p], d+1 + dist[x]);
                    dist[par[x]] = min(dist[par[x]], d+1+dist[x]);
                    // pr(dist[p])
                }
            }
        }
    }
 
    rep(i, 0, n){
        if(dist[i] == inf) cout << -1 << " ";
        else cout << dist[i] << " ";
    }
}
