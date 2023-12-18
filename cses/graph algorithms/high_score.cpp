#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
#define rs(x, a) x.resize(a); 
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
#define pren cerr << endl;
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define trav(item, arr) for (auto &item: arr)
void _pr(int x) {cerr << x;}
void _pr(long long x) {cerr << x;}
void _pr(unsigned long long x) {cerr << x;}
void _pr(double x) {cerr << x;}
void _pr(char x) {cerr << '\'' << x << '\'';}
void _pr(const char* x) {cerr << x;}
void _pr(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x) {cerr << "\e[95m" << "[ "; _pr(x.first); cerr << ", "; _pr(x.second); cerr << "\e[95m" << ']';}
template<typename T> void _pr(const T &x) {int f=0; cerr << '{'; for(auto &i: x) cerr << (f++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

//go for outline with ;, then details
/*
Reverse bellman ford
Let all distances be -inf and update n-1 rounds to find longest path from 1 to n
Only update a nodes distance to something greater if the node its coming from is not -inf, else its ATM unreachable
When cycle found on the n:th round, make that dist inf. Later, go through all edges n-1 times again and make:
if dist[a] = inf: dist[b] = inf

Anther idea: make positive edges negative and vice versa and then 
do normal bellman ford
*/
int const mxn = 1e6;
int n, m;
ll inf = LLONG_MAX;
vo<pair<ll, pair<int, int>>> edg;

ll bellmanFord(){
    vll dist(n, -inf);
    dist[0]=0;

    rep(i, 0, n){
        for(auto ed: edg){
            ll d = ed.first; 
            int u = ed.second.first, v = ed.second.second;

            if(dist[u]==-inf) continue; //kan du inte öka dist om inte reachable

            if(dist[u]+d > dist[v]){

                dist[v]= dist[u]+d;

                if(i>=n-1){
                    dist[v]=inf;
                }
            }
        }
    }

    //mark all nodes of cycles
    rep(i, 0, n-1){
        for(auto ed: edg){
            int u = ed.second.first, v = ed.second.second;
            if(dist[u] == inf) dist[v] = inf;
        }
    }

    if(dist[n-1]==inf) return -1;
    return dist[n-1];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    rep(i, 0, m){
        ll a, b, x;
        cin>>a>>b>>x; a--, b--;
        edg.pb({x, {a, b}});
    }

    cout << bellmanFord();

}
