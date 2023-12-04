#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
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
void _pr(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x) {cerr << "\e[95m" << "[ "; _pr(x.first); cerr << ", "; _pr(x.second); cerr << "\e[95m" << ']';}
template<typename T> void _pr(const T &x) {int f=0; cerr << '{'; for(auto &i: x) cerr << (f++ ? ", " : " "), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << endl;

//go for outline with ;, then details
//kahns algorithm topo sort and modify to make indegree initially half
int const mxn = 2e5+10;
int n, m, home, root, indeg[mxn];
vo<vi> adj(mxn);
vi stay(mxn, 1);


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> home >> root; root--, home--;

    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b), adj[b].pb(a);
        indeg[a]++, indeg[b]++;
    }

    rep(i, 0, n){
        indeg[i] = indeg[i]/2 + indeg[i]%2; //ceiledval
    }

    queue<int> q; q.push(root);
    while(sz(q)){
        int v = q.front(); q.pop();
        stay[v] = 0;

        for(auto x: adj[v]){
            if(stay[x]==0) continue;
            indeg[x]--;
            if(indeg[x]==0) q.push(x);
        }
    }

    if(stay[home]) cout << "stay";
    else cout << "leave";
}
