#include <bits/stdc++.h>
using namespace std;
#include "simurgh.h"

#define vo vector
#define fi first 
#define se second 
#define all(x) x.begin(), x.end()
#define pb push_back

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr(x) cout << #x << " = " << x << endl;
ll const mxn = 1e5, inf = LLONG_MAX;
int n, ret;
vi qryset, vis, tested, ans, unfixed;
vo<pii> indToNode;
vo<vo<pii>> adj;

struct dsu{
    vi sz, par;
    dsu(int n): par(n), sz(n){
        iota(all(par), 0);
    }

    int find(int v){
        if(par[v]==v) return v;
        return par[v] = find(par[v]);
    }

    void uni(int a, int b){
        a = find(a), b=find(b);
        if(a!=b){
            if(sz[b] > sz[a]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
        }
    }
};

void tryremove(int ind, int baseline){
    if(ind == baseline) return;
    if(ans[ind] != -1 && ans[baseline] != -1) return;

    qryset.erase(find(all(qryset), ind));
    int tmp = count_common_roads(qryset);
    if(tmp > ret) {
        ans[baseline] = 1; ans[ind] = 0;
    }
    else if(tmp < ret){
        ans[baseline] = 0, ans[ind] = 1;
    }
    else{
        if(ans[ind] != -1) ans[baseline] = ans[ind];
        else if(ans[baseline] != -1) ans[ind] = ans[baseline];
        else unfixed[ind] = 1; 
    }
    qryset.pb(ind);
}

int dfs(int at, int p, int baseline){ // return start of cycle
    vis[at] = 1; int ct=0;
    for(auto [x, ind]: adj[at]){
        if(x!=p){
            if(vis[x]){
                //try remove this edge
                tryremove(ind, baseline);
                return x;
            }
            else{
                int tmp = dfs(x, at, baseline);
                if(tmp != -1){
                    tryremove(ind, baseline);

                    if(tmp == at) return -1;
                    else return tmp;
                }
            }
        }
    }
    
    return -1;
}

vi find_roads(int N, vi U, vi V){
    n = N;
    int m = U.size(); indToNode.resize(m); tested.assign(m, 0); ans.assign(m, -1); unfixed.assign(m, 0); adj.resize(n);
    //subtask 2+3
    rep(i, 0, m){
        indToNode[i] = {U[i], V[i]};
    }

    // gör ett första träd
    dsu g(n); vi notchosen;
    rep(i, 0, m){
        auto [a, b] = indToNode[i];
        if(g.find(a) != g.find(b)){
            g.uni(a, b);
            adj[a].pb({b, i}), adj[b].pb({a, i});
            qryset.pb(i);
        }
        else{
            notchosen.pb(i);
        }
    }
    ret = count_common_roads(qryset);
    if(ret == n-1) return qryset;
    
    //try swapping one and one
    for(auto edge: notchosen){
        //try using this edge
        qryset.pb(edge); vis.assign(n, 0); auto [a, b] = indToNode[edge];
        adj[a].pb({b, edge}), adj[b].pb({a, edge});
        dfs(a, a, edge);  
        qryset.erase(find(all(qryset), edge)); adj[a].pop_back(), adj[b].pop_back();

        rep(i, 0, m){
            if(unfixed[i]) {
                if(ans[edge] != -1) ans[i] = ans[edge];
                else ans[i] = 0;
                unfixed[i] = 0;
            }
        }
        if(ans[edge] == -1) ans[edge] = 0;
        
    }

    qryset.clear(); 
    rep(i, 0, m) {a
        if(ans[i]) qryset.pb(i);
    }
    return qryset;
}
