#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vo vector
#define pb push_back
#define se second
#define fi first
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define umap unordered_map
#define uset unordered_set
 
#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
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
ll const inf = LLONG_MAX, mxn = 1e5+4;
int r, c;
vo<vi> tbl;
vo<pii> kant;
 
int compress(int a, int b){
    return a*c + b;
}
 
struct dsu{
    vi par, siz;
    vo<priority_queue<pii>> nei;
    dsu(int n): par(n), siz(n){
        rep(i, 0, n) par[i] = i;
    }
    int findpar(int v){
        if(v==par[v]) return v;
        return par[v] = findpar(par[v]);
    }
    void unite(int a, int b){
        a = findpar(a), b = findpar(b);
        if(a!=b){
            if(siz[b] > siz[a]) swap(a, b);
            par[b] = a;
            siz[a] += siz[b]; siz[b] = 0;
            // for(auto v: nei[b]){
            //     nei.push(v);
            // }
        }
    }
};
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c;
}
bool walk(int a, int b, int val){
    priority_queue<array<int, 3>> pq;
    pq.push({tbl[a][b], a, b});
    int target = val;
    vo<vi> vis(r, vi(c, 0));
    while(pq.size()){
        auto [val, a, b] = pq.top(); pq.pop();
        if(vis[a][b]) continue;
        if(val < target) return 0;
 
        vis[a][b] = 1;
        target--;
        if(target<=0) return 1;
 
        for(auto x: dir){
            int nr = x[0]+a, nc = x[1]+b;
            if(ir(nr, nc) && !vis[nr][nc]){
                pq.push({tbl[nr][nc], nr, nc});
            }
        }
    }
    return 0;
}
 
bool f(int val){
    dsu g(r*c);
    for(auto [i, u]: kant){
        if(walk(i, u, val)) return 1;
    }
    return 0;
}
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c; 
    tbl.assign(r, vi(c, 0));
    rep(i, 0, r){
        rep(u, 0, c){
            cin>>tbl[i][u];
            if(u==0 || i==0 || u==c-1 || i==r-1) kant.pb({i, u});
        }
    }
 
    int lo = 0, hi = 2e5+4;
    while(hi-lo>1){
        int mid = (hi+lo)/2;
        if(f(mid)) lo = mid;
        else hi = mid;
    }
 
    cout << lo;
}
