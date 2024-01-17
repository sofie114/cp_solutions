#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

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
template<typename T> void _pr(const T &x) {int f=0; cerr << '{'; for(auto &i: x) cerr << (f++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

//go for outline with ;, then details
int const mxn = 2e5+10;
ll n, m, sum[mxn], rsum[mxn];;
vi simon, nicole;
ll ans; 

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    simon.resize(m), nicole.resize(n);

    rep(i, 0, n) cin>>nicole[i];
    rep(i, 0, m) cin>>simon[i];
    sort(all(simon)), sort(all(nicole));

    if(n==m){
        rep(i, 0, n){
            ans+=abs(simon[i]-nicole[i]);
        }
    }
    else{
        ans = LLONG_MAX;
        
        rep(i, 0, n){
            sum[i] += abs(simon[i]-nicole[i]);
            if(i>0) sum[i]+=sum[i-1];
        }
        repd(i, 1, n+1){
            rsum[i] += abs(simon[i]-nicole[i-1]);
            if(i<n) rsum[i] += rsum[i+1];
        }

        rep(i, 0, n+1){
            ll a = 0, b=0;
            if(i>0) a = sum[i-1];
            if(i<n) b = rsum[i+1];
            ans = min(ans, a+b);
        }
    }

    cout << ans;
}
