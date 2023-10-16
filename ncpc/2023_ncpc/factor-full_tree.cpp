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
#define all(v) v.begin(), v.end()i
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto &item: arr)
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

int const mxn = 61;
ll n, vis[mxn], ans[mxn], dist[mxn], par[mxn], cov=0;
vo<ll> adj[mxn];

void dfs(int at){
    vis[at] = 1;

    for(auto x: adj[at]){
        if(vis[x]) continue;
        dfs(x);
        par[x]=at;
        dist[at] = max(dist[at], dist[x]+1);
    }
}

void label(ll at, ll prim){
    vis[at] = 1;

    ans[at]=1;
    if(at!=0) ans[at] = ans[par[at]]*prim;
    cov++;

    for(auto x: adj[at]){
        if(!vis[x] && dist[x]==dist[at]-1){
            label(x, prim);
            return;
        }
    }
}

int main(){
    cin >> n;
    rep(i, 0, n-1){
        ll a, b;
        cin >> a >> b; a--, b--;
        adj[a].pb(b); adj[b].pb(a);
    }
    vo<ll> prim = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};

    dfs(0);
    memset(vis, 0, sizeof(vis));
    ll u=0;
    // rep(i, 0, n) cout << dist[i] << " ";
    // cout << endl;
    while(cov<n){
        ll mxi=-1, mx=-1;

        rep(i, 0, n){
            if(dist[i]>mx&&!vis[i]){
                mx = dist[i]; mxi=i;
            }
        }

        if(mxi==0) label(mxi, prim[u]);
        else label(mxi, prim[u]); 
        u++;

    }
    
    rep(i, 0, n) cout << ans[i] << " ";

}