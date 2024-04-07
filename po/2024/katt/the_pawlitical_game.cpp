#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vo vector
#define pb push_back
#define se second
#define fi first
#define ar array
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
int const inf = LLONG_MAX, sub = 204, mxn = 1e6+4;
int n, ans=inf, inp[mxn];
int dp[sub][sub], dp2[sub][sub], vis[mxn];

struct dsu{
    vi par, sz, val;
    dsu(int n): par(n), sz(n, 1), val(n, 0){
        iota(all(par), 0);
        rep(i, 0, n) val[i] = inp[i];
    }

    int find(int v){
        if(par[v]==v) return v;
        return par[v] = find(par[v]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a!=b){
            if(sz[a]<sz[b]) swap(a, b);
            par[b] = a;
            sz[a]+=sz[b];sz[b]=0;
            val[a]++;
        }
    }
};

pii sol1(int l, int r){ //min comps and value 
    if(dp[l][r] != 0) return {dp[l][r], dp2[l][r]};
    if(l==r){
        dp[l][r] = 1; dp2[l][r] = inp[l];
        return {1, inp[l]};
    }

    pii ret = {inf, -1};
    rep(lef, l, r){
        pii a = sol1(l, lef), b = sol1(lef+1, r); 
        if(a.fi == b.fi && a.fi == 1 && a.se == b.se){
            dp[l][r] = 1;
            dp2[l][r] = a.se+1;
            return {1, a.se+1};
        }
        else if(ret.fi > a.fi+b.fi){
            ret.fi = a.fi+b.fi;
        }
    }

    dp[l][r] = ret.fi; dp2[l][r] = ret.se;
    return ret;
}

void dfs(int pos, vo<vi>& adj){
    if(pos == n) return; 
    int mn = inf;
    for(auto x: adj[pos]){
        if(!vis[x]) dfs(x, adj);
        mn = min(mn, vis[x]);
    }
    vis[pos] = mn+1;
    return;
}

void sol2(){
    //find all good intervals
    vo<vi> adj(n); //points to all pos you can move to using good intervals
    vi nex(n+4, -1), nex2(n+4, -1);
    vo<array<int, 3>> order; //val and left ind
    rep(i, 0, n){
        order.pb({inp[i], i, i});    
    }
    sort(all(order));

    vo<pii> interval; //left to right
    int val = -1, i = 0;
    while(interval.size() || i < n){
        vo<pii> interval2;
        if(val == -1 && i<n) val = order[i][0];
        while(i < n && order[i][0] == val){
            auto [v, l, r] = order[i++]; //will this assign val 
            nex[l] = r;
            interval.pb({l, r});
        }

        int newval = -1;
        swap(interval, interval2);
        for(auto [l, r]: interval2){
            if(nex[r+1] != -1){
                interval.pb({l, nex[r+1]});
                nex2[l] = nex[r+1];
                newval = val+1;
            }
            else nex2[l] = -1;
            adj[l].pb(r+1);
        }
        for(auto [l, r]: interval2){
            nex[l] = nex2[l]; nex2[l] = -1;
        }
        val = newval;
    }

    dfs(0, adj);
    ans = vis[0];
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(i, 0, n) cin>>inp[i];
    if(n<=0){
        vi arr(n-1); iota(all(arr), 0);
        do{ 
            dsu g(n);
            int ct = n;
            rep(i, 0, n-1){
                int u1 = arr[i], u2 = arr[i]+1;
                int val1 = g.val[g.find(u1)], val2 = g.val[g.find(u2)];
                if(val1 == val2){
                    g.unite(u1, u2);
                    ct--;
                }
            }
            ans = min(ans, ct);
        } while(next_permutation(all(arr)));
    }
    else if(n<=0){
        sol1(0, n-1);
        ans = dp[0][n-1];
    }
    else{
        sol2();

    }
    cout << ans;
}

/*
kolla lösning här:
https://docs.google.com/presentation/d/1mYwPhdEZT8Hgx0mPZZkCODMgT8NMOYid/edit#slide=id.g2c8344d48c7_0_36

*/
