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

/*
Tree dp
Each time we move to neighbour node we increase the one we were standing on with their dist to leaf, 
and remove the donate of the neighbour we moved to. Everything else remains.

*/

//go for outline with ;, then details
int const mxn = 1e5+10;
ll n, a[mxn], vis[mxn], child[mxn];
ll ans, pers=0;
vo<ar<ll, 2>> adj[mxn];

void dfs(int at, int bef){

    for(auto &x: adj[at]){
        if(!vis[x[0]]){
            vis[x[0]] = 1; dfs(x[0], bef+1); 
            x[1] = child[x[0]];
            child[at] += x[1];
        }
        else{ //par
            x[1] = bef;
        }
        // pr(at, x[0], x[1]);
    }

}

void find_ans(int at, int par, ll tmp){

    for(auto &x: adj[at]){
        if(x[0] != par){
            ll newans = tmp + (n-x[1])*a[at] - x[1]*a[x[0]];
            // pr(at, par, newans, x[0], x[1]);
            if(newans > ans){
                ans = max(ans, newans);
                pers = x[0];
            }

            find_ans(x[0], at, newans);

        }
    }
}

int main(){
    cin >> n;
    rep(i, 0, n) {cin >> a[i]; child[i]=1;}
    rep(i, 0, n-1) {int v, u; cin >> v >> u; v--, u--; adj[u].pb({v, 0}); adj[v].pb({u, 0});}

    //from root dfs
    vis[0]=1;
    dfs(0, 0);

    // rep(i, 0, n) cout << child[i] << " ";
    // rep(i, 0, n) cout << bef[i]+1 << " ";

    rep(i, 0, n){
        if(i==0) ans += n*100;
        else ans += (child[i])*a[i];
    }
    // pr(ans);
    find_ans(0, -1, ans);
    cout << pers+1;
}
