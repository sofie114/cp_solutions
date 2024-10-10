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
int n;
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n; 
    vi arr(n);
    rep(i, 0, n) cin>>arr[i];
 
    //find LIS in nlogn
    vi dp(n+1, 0), minval(n+1, inf); //maps dp value to minimum value holding that
    rep(i, 0, n){
        if(i==0){
            dp[0] = 1;
            minval[1] = arr[i];
            minval[0] = 0;
        }
        else{
            //find biggest dp val for small enough val from before
            int lo=0, hi = n+1;
            while(lo+1<hi){
                int mid = (lo+hi)/2;
                if(minval[mid] < arr[i]) lo = mid;
                else hi = mid;
            }
            
            dp[i] = lo+1;
            minval[dp[i]] = min(minval[dp[i]], arr[i]);
        }
    }
 
    cout << *max_element(all(dp));
}
