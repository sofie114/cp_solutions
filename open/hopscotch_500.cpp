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
ll const inf = LLONG_MAX, mxn = 502;
int n, k, tbl[mxn][mxn];
vi dprow(mxn, inf), dpcol(mxn, inf);

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;  
    vo<pii> cells[k+1];

    rep(i, 0, n){
        rep(u, 0, n){
            cin>>tbl[i][u];

            cells[tbl[i][u]].pb({i, u});
            if(tbl[i][u]==1) {
                dprow[i] = 0;
                dpcol[u] = 0;
            }

        }
    }

    rep(w, 2, k+1){
        vi dpr(mxn, inf), dpc(mxn, inf);
        for(auto x: cells[w]){
            int r = x.fi, c = x.se;
            int mini = inf;

            rep(i, 0, n){
                if(dprow[i]==inf) continue;
                int d = pow(r-i, 2);
                mini = min(mini, dprow[i] + d); 
            }
            rep(i, 0, n){
                if(dpcol[i]==inf) continue;
                int d = pow(c-i, 2);
                mini = min(mini, dpcol[i] + d); 
            }

            dpr[r] = min(dpr[r], mini);
            dpc[c] = min(dpc[c], mini);

        }
        //setup
        dprow = dpr, dpcol = dpc;
    }

    ll ans = inf;
    for(auto x: cells[k]){
        ans = min(ans, ll(dprow[x.fi]));
    }

    if(ans == inf) cout << -1;
    else cout << ans;

}

/*
dp insight: dp val for each same k-val on same row/col is the same. 
*/
