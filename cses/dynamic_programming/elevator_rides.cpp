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

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define umap unordered_map
#define uset unordered_set
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
mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){return uniform_int_distribution<int>(l, r)(mt_rng);}

//go for outline with ;, then details
int const inf = LLONG_MAX, mxn = 1e5+4;
int n, C, wei[mxn];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>C;
    rep(i, 0, n) cin>>wei[i];
    vo<pii> dp((1<<n)+5, {inf, inf}); dp[0] = {1, 0};

    rep(mask, 0, (1<<n)){
        rep(i, 0, n){
            if(mask & (1<<i)){
                int tmp = mask ^ (1<<i);
                auto [minrides, minW] = dp[tmp];

                if(minW+wei[i] <= C && minrides<=dp[mask].fi){
                    dp[mask].fi = minrides; dp[mask].se = min(dp[mask].se, minW+wei[i]);
                }
                else if(minrides+1<=dp[mask].fi){
                    dp[mask].fi = minrides+1; dp[mask].se = min(dp[mask].se, wei[i]);
                }
            }
        }
        // pr(mask, dp[mask])
    }
    cout << dp[(1<<n)-1].fi;
}

/*
dp[mask] = {minimum rows/rides, minimum columns last row / weight last ride} 
*/
