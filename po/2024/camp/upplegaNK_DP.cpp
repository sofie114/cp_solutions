#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define s second
#define f first
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<ll, ll> pii;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define pren cerr << endl;
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
template<typename T> void _pr(const T &x) {int F=0; cerr << '{'; for(auto &i: x) cerr << (F++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

//go for outline with ;, then details
int const mxn = 1e5+4;
ll n, k, treepos[mxn], branchnum[mxn], branchsum[mxn], rigsave[mxn], lefsave[mxn];
vo<pii> lef[mxn], rig[mxn]; //height and wid
vo<vo<ar<ll, 2>>> dp;
ll ans;

ll findsaved1(int saving, int saved){
    ll r=0, ret=0;
    vo<ar<ll, 3>> tmp;
    for(auto x: rig[saving]){
        tmp.pb({x.first, treepos[saving] + x.second, 1});
    }
    for(auto x: lef[saved]){
        tmp.pb({x.first, treepos[saved] + x.second, 2});
    }
    sort(all(tmp));
    // pr(tmp)

    for(auto x: tmp){
        if(x[2] == 1){ r = max(r, x[1]); }
        else ret += max(ll(0), r-x[1] + 1);
    }
    return ret;
}

ll findsaved2(int saved, int saving){
    ll l=1e9+2, ret=0;
    vo<ar<ll, 3>> tmp;
    for(auto x: lef[saving]){
        tmp.pb({x.first, treepos[saving] + x.second, 1});
    }
    for(auto x: rig[saved]){
        tmp.pb({x.first, treepos[saved] + x.second, 2});
    }
    sort(all(tmp));
    // pr(tmp)

    for(auto x: tmp){
        if(x[2] == 1){ l = min(l, x[1]); }
        else ret += max(ll(0), x[1]-l + 1);
    }
    return ret;
}

ll solve(ll treeind, ll kused, ll use){ //use is for prev one
    if(kused==-1 || treeind==n){
        return 0;
    }
    if(dp[treeind][kused][use] != -1){
        return dp[treeind][kused][use];
    }

    ll sum1 = 0, sum2 = 0;
    if(use){
        sum1 += branchsum[treeind] - lefsave[treeind+1] + lefsave[treeind];
        sum2 += branchsum[treeind] + rigsave[treeind] + lefsave[treeind];
    }
    
    ll ret = max(solve(treeind+1, kused-1, 1) + sum1, solve(treeind+1, kused, 0) + sum2);
    dp[treeind][kused][use] = ret;
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0); 
    cin>>n>>k; dp.resize(n+1, vo<ar<ll, 2>>(k+1, {-1, -1}));
    rep(i, 0, n) cin>>treepos[i];
    rep(i, 0, n) cin>>branchnum[i];
    rep(i, 0, n){
        vo<pii> anoy(branchnum[i]);
        rep(u, 0, branchnum[i]){
            cin>>anoy[u].first;
        }
        rep(u, 0, branchnum[i]){
            cin>>anoy[u].second;
            branchsum[i] += abs(anoy[u].second);
        }
        for(auto x: anoy){
            if(x.second < 0){
                lef[i].pb(x);
            }
            else rig[i].pb(x);
        }
    }

    rep(i, 0, n-1){
        rigsave[i] = findsaved1(i, i+1);
    }
    rep(i, 1, n) lefsave[i] = findsaved2(i-1, i);

    if(k==1){
        rep(i, 0, n) ans = max(ans, branchsum[i]+rigsave[i]+lefsave[i]);
    }
    else{
        ans = max(solve(0, k, 0), solve(0, k-1, 1));
    }
    cout << ans;
}

/*
dp[i][kused][use] = maximum gain from i to n-1 having used k and using the next one
Alien trick: binary search with penalty.
*/
