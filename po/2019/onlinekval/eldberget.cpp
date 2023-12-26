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
BFS där varje ruta har 0-k states: 
varje rutas kortaste distans från start för 0-k genomgångna flammor sparas i dist.
*/

int const mxn = 102, mxk=202;
ll r, c, k, tbl[mxn][mxn], dist[mxn][mxn][mxk];

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c; //maybe add not #
}

void bfs2d(){
    dist[0][0][0] = 0;
    queue<ar<int, 3>> q; q.push({0, 0, 0});  //r, c, k

    while(q.size()){
        ar<int, 3> v = q.front(); q.pop();
        int d = dist[v[0]][v[1]][v[2]];

        for(auto x: dir){
            int nr = v[0]+x[0], nc = v[1]+x[1], k1=v[2];

            if(!ir(nr, nc)) continue;
            if(tbl[nr][nc]==0) k1++;
            if(k1 > k) continue;

            if(dist[nr][nc][k1]==-1){
                dist[nr][nc][k1] = d+1;
                q.push({nr, nc, k1});
            }
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c>>k;
    rep(i, 0, r){
        rep(u, 0, c){
            char a;cin>>a;
            if(a=='.') tbl[i][u]=1;
        }
    }

    memset(dist, -1, sizeof(dist));
    bfs2d();

    ll ans = 1e9;
    rep(i, 0, k+1){
        if(dist[r-1][c-1][i]!=-1) ans = min(ans, dist[r-1][c-1][i]);
    }
    
    if(ans==1e9) cout << "nej";
    else cout << ans;

}
