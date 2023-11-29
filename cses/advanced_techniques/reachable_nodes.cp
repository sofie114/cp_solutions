#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;
typedef vector<int> vi;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << "=" << x << " ";
#define pren cerr << endl;
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define trav(item, arr) for (auto &item: arr)
#define prar(arr, n) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
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

//go for outline with ;, then details
int const mxn = 5e4+10;
int n, m, vis[mxn], ans[mxn];
vo<vi> adj;
bitset<mxn> reach[mxn];

bitset<mxn> dfs(int at){
    if(vis[at]) return reach[at];
    vis[at] = 1;

    reach[at].set(at, 1);

    for(auto x: adj[at]){
        reach[at] |= dfs(x);
    }

    ans[at] = reach[at].count();
    return reach[at];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    adj.resize(n);

    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
    }

    rep(i, 0, n){
        if(!vis[i]) dfs(i);
    }

    rep(i, 0, n) cout << ans[i] << " ";
}
