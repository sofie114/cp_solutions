#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto item: arr)
#define prar(n, arr) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
#define print(...) {cout << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}

template<typename T>
void print_vars(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cout << arg << ", ";
    print_vars(args...);
}

int const mxn = 1e5+10;
vo<int> adj[mxn];
vo<int> grenar;
int n;

int dfs(int at, int par){
    if(len(adj[at])==1&&at!=0) return 1;
    
    vo<int> curr;
    for(auto node: adj[at]){
        if(node!=par){
            curr.pb(dfs(node, at));
        }
    }
    sort(all(curr));
    rep(i, 0, len(curr)-1) grenar.pb(curr[i]);
    if(at==0) return curr.back();
    return curr.back()+1;
}

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    rep(i, 0, n-1){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }

    grenar.pb(dfs(0, 0));
    sort(all(grenar), greater<int>());
    // repv(x, grenar) pr(x)
    int ans = 1;
    for(auto x: grenar){
        rep(i, 0, x) cout << ans << " ";
        ans++;
    }
}


