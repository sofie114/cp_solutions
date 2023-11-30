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
template<typename T> void print_vars(T arg) {cerr << arg << endl;}
template<typename T, typename... Args> void print_vars(T arg, Args... args) {cerr << arg << ", "; print_vars(args...);}

//go for outline with ;, then details
int const mxn = 2e6;
int n, p, vis[mxn], to[mxn], dep[mxn];
vo<vi> adj(mxn);

int longestpathDFS(int at){
    if(vis[at]) return dep[at];
    vis[at] = 1;

    int mx=0;
    for(auto x: adj[at]){
        int tmp = longestpathDFS(x);
        if(tmp > mx){
            mx = tmp;
            to[at] = x;
        }
    }
    dep[at] = mx+1;
    return dep[at];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> p;
    memset(to, -1, sizeof(to));
    rep(i, 0, p){
        int ant, prev; cin >> ant;
        rep(u, 0, ant){
            int a; cin >> a;
            if(u>0) adj[prev].pb(a);
            prev = a;
        }
    }

    int ans = 0, node;
    rep(i, 0, n){
        if(!vis[i]) {
            int tmp = longestpathDFS(i);
            if(tmp > ans){
                ans = tmp;
                node = i;
            }
        }
    }

    vi seq;
    while(1){
        seq.pb(node);
        node = to[node];
        if(node == -1) break;
    }
    cout << ans << endl;
    rep(i, 0, len(seq)) cout << seq[i] << " ";
}
