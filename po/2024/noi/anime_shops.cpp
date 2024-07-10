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
int const inf = LLONG_MAX, mxn = 1e5+__DBL_MAX_10_EXP__;
int n, m, k, anime[mxn], from[mxn];
vo<vi> adj(mxn);
vi dist(mxn, inf);
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
 
    queue<array<int, 3>> qu; //dist and node coming from 
    rep(i, 0, k) { int a; cin>>a; qu.push({0, a, a}); anime[a] = 1;}
    rep(i, 0, m) {
        int a, b; cin>>a>>b; adj[a].pb(b), adj[b].pb(a);
    }
 
    while(qu.size()){
        auto [d, v, root] = qu.front(); qu.pop();
        
        for(auto x: adj[v]){
            if(x == root || from[x] == root) continue;
            else if(anime[x]){
                if(d+1 < dist[x]) {dist[x] = d+1; from[x] = root;}
                if(d+1 < dist[root]) {dist[root] = d+1; from[root] = x;}
            }
            else if(dist[x] == inf){
                dist[x] = d+1; from[x] = root;
                qu.push({d+1, x, root});
            }
            else{
                if(dist[x]+d+1 < dist[from[x]]) {dist[from[x]] = dist[x]+d+1; from[from[x]] = root;}
                if(dist[x]+d+1 < dist[root]) {dist[root] = dist[x]+d+1; from[root] = from[x];}
            }
        }
    }
    
    rep(i, 1, n+1) if(dist[i]==inf) dist[i] = -1;
    rep(i, 1, n+1) cout << dist[i] << " ";
}
