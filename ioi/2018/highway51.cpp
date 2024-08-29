#include <bits/stdc++.h>
#include "highway.h"
using namespace std;

#define int long long
#define vo vector
#define pb push_back
#define fi first 
#define se second 

typedef vector<int> vi;
typedef pair<int, int> pii;

#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define pr(x) cout << #x << " = " << x << endl;
int const mxn = 9e4;
vo<vo<pii>> adj;
vo<signed> ans;
int n, m, dist;
vo<pii> indToNode;

void dfs(int at, int p, int forbidden, vi& edges){
    for(auto [x, ind]: adj[at]){
        if(x!=p && ind!=forbidden){
            indToNode[ind] = {at, x};
            dfs(x, at, forbidden, edges);
            edges.pb(ind);
        }   
    }
}

int binary_search(vi& potential, int A){
    bool change = 0;
    int lo = -1, hi = potential.size(); //maybe -1
    while(lo+1<hi){
        int mid = (lo+hi)/2;
        ans.assign(m, 0);

        rep(i, 0, mid+1) ans[potential[i]] = 1;
        int ret = ask(ans);
        if(ret > dist*A) {hi = mid; change=1;}
        else lo = mid;
    }

    if(!change) return -1;
    return hi;
}

void find_pair(signed N, vo<signed> U, vo<signed> V, signed A, signed B){
    n = N; m = U.size(); 
    indToNode.resize(m); adj.resize(n); 
    rep(i, 0, m){
        adj[U[i]].pb({V[i], i});
        adj[V[i]].pb({U[i], i});
        indToNode[i] = {U[i], V[i]};
    }
    ans.assign(m, 0); 
    int ret = ask(ans); dist=ret/A;

    //rota trädet vid en kant
    vi tmp(m); iota(tmp.begin(), tmp.end(), 0);
    int hi = binary_search(tmp, A);
    // pr(hi)


    if(dist == 1){
        answer(indToNode[hi].fi, indToNode[hi].se);
    }
    else{ 
        auto [a, b] = indToNode[hi];
        vi edges; pii op;

        //find one node
        dfs(a, a, hi, edges);
        if(edges.size()==0) op.fi = a;
        else{
            int ret = binary_search(edges, A);
            if(ret==-1) op.fi = a;
            else op.fi = indToNode[edges[ret]].se;
        }

        //find another node
        edges.clear();
        dfs(b, b, hi, edges);
        // for(auto edge: edges) pr(edge);
        if(edges.size()==0) op.se = b;
        else{
            int ret = binary_search(edges, A);
            if(ret==-1) op.se = b;
            else op.se = indToNode[edges[ret]].se;
        };

        // pr(op.fi) pr(op.se)
        answer(op.fi, op.se);
    }
}

/*
5 4 1 2 4 3
0 1
0 2
1 3
4 2

4 3 1 2 3 1
0 1
1 2
0 3
*/
