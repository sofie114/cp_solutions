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
int const inf = LLONG_MAX, mxn = 2e5+4;
int n, lef[mxn], rig[mxn];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(i, 0, n){
        cin>>lef[i]>>rig[i];
    }

    if(n<=1000){
        // subtask 3, n^3 solution: dp[i]=maximum tulips only taking tulips 0-i and taking i

        vi dp(n+1, 1); 
        rep(i, 0, n){
            int l = max((int)0, i-lef[i]);

            rep(u, 0, l){
                if(u+rig[u] < i) dp[i] = max(dp[i], dp[u]+1);
            }
        }
        cout << *max_element(all(dp));
    }
    else{
        // full solution: binary search to find rightmost index whose right wing does not cover currindex. 
        // then take the prefixdpmax of this ind
        vi dp(n+1, 1), maxi(n+1, 0); 
        rep(i, 0, n){
            int l = max((int)0, i-lef[i]); // first forbidden index

            //binary search
            int lo=-1, hi = l, mid=-1;
            while(lo+1<hi){
                mid = (lo+hi)/2;
                if(mid+rig[mid] < i) lo = mid;
                else hi = mid;
            }
            //mid gives last okay index
            if(mid!=-1) dp[i] = max(dp[i], maxi[mid]+1);

            if(i==0) maxi[i] = dp[i];
            else maxi[i] = max(dp[i], maxi[i-1]);
        }
        cout << *max_element(all(dp));  
    }

}
