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
int const inf = LLONG_MAX, mxn = 2e5+4;
int n, d, ans;
vo<vi> adj(mxn);

int dfs(int at, int p){ //returns distance
    int ret = inf; //min dist to one placed
    vi vec;
    for(auto x: adj[at]){
        if(x!=p){
            int tmp = dfs(x, at);
            vec.pb(tmp);
        }
    }
    
    sort(all(vec)); reverse(all(vec));
    int prev = -1;
    for(auto val: vec){
        if(prev==-1 || prev+val>=d){
            prev = val;
            ret = min(ret, val);
        }
        else{
            ans--;
        }
    }

    if(ret >= d) {
        ret=0; ans++;
    }
    ret++;
    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>d;
    rep(i, 1, n){
        int a; cin>>a;
        adj[a].pb(i), adj[i].pb(a);
    }

    dfs(0, 0);
    cout << ans;
}

/*
full solution: greedy + graph search. save minimum distance to marked child-nodes. 
*/
