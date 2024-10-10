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

//go for outline with ;, then details
int const inf = LLONG_MAX, mxn = 1e5+4;

/*
implementation 1: store dp values in a map and binary search for j such that b[j]<i. sort by b[i]
dp[i] = maximum reward finished on day i or earlier. 

implementation 2: bouquet style, only store one dpval, when finished processing index i, do not update dpval with it until 
b[i] is less than the current index
*/
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin>>n;
    vo<array<int, 3>> arr;
    rep(i, 0, n){
        int a, b, p;
        cin>>a>>b>>p; arr.pb({a, b, p});
        // cin>>a>>b>>p; arr.pb({b, a, p}); for implementation 1

    }
    sort(all(arr));

    // implementation 1
    // int mdp=0; //maxdp
    // map<int, int> dp = {{0, 0}}; //b,dpval
    // rep(i, 0, n){
    //     auto [b, a, p] = arr[i];
    //     auto it = dp.lower_bound(a);
    //     it--;
    //     mdp = max(mdp, (*it).se+p);
    //     dp[b] = mdp;
    // }
    // cout << mdp;

    // implementation 2 - took shorter time, maybe more intuitive?
    set<pii> pq;
    int dpval = 0;
    rep(i, 0, n){
        auto [a, b, p] = arr[i];
        while(pq.size() && (*pq.begin()).fi < a){
            dpval = max(dpval, (*pq.begin()).se);
            pq.erase(pq.begin());
        }
        int val = dpval+p;
        pq.insert({b, val});
    }
    while(pq.size()){
        dpval = max(dpval, (*pq.begin()).se);
        pq.erase(pq.begin());
    }
    cout << dpval;
}
