#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define se second
#define fi first
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<int, int> pii;

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

int const mxn = 1e5+4;
ll n, k, treepos[mxn], branchnum[mxn], branchsum[mxn], rigsave[mxn], lefsave[mxn];
vo<pii> lef[mxn], rig[mxn]; //height and wid
vo<ar<double, 2>> dp; vo<vi> dpk(mxn, vi(2));
ll ans;
ll numk;

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

    for(auto x: tmp){
        if(x[2] == 1){ l = min(l, x[1]); }
        else ret += max(ll(0), x[1]-l + 1);
    }
    return ret;
}

pair<double, int> solve(ll treeind, ll use, double penalty){ //return sum and number of k
    if(dp[treeind][use] != -1){
        return {dp[treeind][use], dpk[treeind][use]};
    }
    if(treeind == 0) {
        return {use*(branchsum[0] + rigsave[0] - penalty), use};
    }

    pair<double, int> ret1 = solve(treeind-1, 1, penalty), ret2 = solve(treeind-1, 0, penalty);
    if(use){
        double add1 = rigsave[treeind] + branchsum[treeind], add2 = branchsum[treeind] + rigsave[treeind] + lefsave[treeind];
        if(treeind>0) add1 -= rigsave[treeind-1];
        ret1.fi += add1 - penalty; ret2.fi += add2 - penalty;
        ret1.se++; ret2.se++;
    }

    if(ret1.fi > ret2.fi) { dp[treeind][use] = ret1.fi, dpk[treeind][use] = ret1.se; return ret1;}
    else { dp[treeind][use] = ret2.fi; dpk[treeind][use] = ret2.se; return ret2; }
}


int main(){
    cin.tie(0)->sync_with_stdio(0); 
    cin>>n>>k; 
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
        ll lo = 0, hi = 1e11, mid;
        rep(i, 0, 150){
            mid = (hi+lo)/2;
            dp.assign(n+1, {-1, -1});
            pair<double, int> tmp = solve(n, 0, mid);

            // pr(lo, hi, mid, tmp)
            if(tmp.se >= k) lo = mid;
            else hi = mid;
        }
        ans = round(solve(n, 0, lo).fi + lo*k);

    }

    cout << ans;

}

/*
dp[i][kused][use] = maximum gain from i to n-1 having used k and using the next one
alien trick: binary search over penalty
*/
