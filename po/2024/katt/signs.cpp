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
int const inf = LLONG_MAX, mxn = 1e3+4, mxm = 204;
int n, m, vis[mxn], val[mxn];
vo<vi> adj, dp;
map<int, vi> signs;
vi ans;

void dfs(int at){
    vis[at] = inf;
    int sum = 0;
    for(auto x: adj[at]){
        if(vis[x] == -1) dfs(x);
        int tmp = val[x];
        if(tmp > sum){
            sum = tmp;
            vis[at] = x;
        }
    }
    sum++;
    val[at] = sum;
}

void check(int test){
    map<int, bitset<mxm>> bitsets; adj.clear(); adj.resize(n); 
    memset(vis, -1, sizeof(vis)); memset(val, 0, sizeof(val));

    rep(i, 0, n){
        vi tmp(m);
        rep(u, 0, m){
            tmp[u] = signs[i][u] - signs[test][u];  
        }
        int mn = *min_element(all(tmp)), ok=1;
        rep(u, 0, m){
            tmp[u] -= mn;
            if(tmp[u] > 1) {ok = 0; break;}
        }
        if(!ok) continue;
        bitset<mxm> bs;
        rep(u, 0, m){
            if(tmp[u]) bs.set(u);
        }
        bitsets[i] = bs;
    }

    for(auto [ind, vec]: bitsets){
        for(auto [i,  v]: bitsets){
            if(ind == i) continue;

            if((vec | v) == v){
                adj[ind].pb(i);
            }
        }
    }

    dfs(test);
    if(val[test] > ans.size()) {
        ans.clear();
        //construct path
        int cur = test;
        while(1){
            ans.pb(cur);
            cur = vis[cur];
            if(cur == inf) break;
        }
    }

}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;

    rep(i, 0, n){ //does normalizing work for random
        rep(u, 0, m){
            int a; cin>>a;
            signs[i].pb(a);
        }
    }

    vi v(n); iota(all(v), 0);
    random_shuffle(all(v));
    rep(test, 0, min(n, (int)40)){
        check(v[test]);
    }

    //answering
    cout << ans.size() << endl;
    vo<pii> op;
    rep(i, 0, ans.size()){
        op.pb({accumulate(all(signs[ans[i]]), 0), ans[i]});
    }
    sort(op.rbegin(), op.rend());
    rep(i, 0, ans.size()) cout << op[i].se+1 << " ";
}