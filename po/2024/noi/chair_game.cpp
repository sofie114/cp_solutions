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
ll const inf = LLONG_MAX, mxn = 105;
int t, n;

void solve(){
    cin>>n; 
    vi a(n), b(n, 0), c(n), arr(n), posA(n); int sum = 0;
    iota(all(a), 0); iota(all(c), 0); iota(all(posA), 0);
    rep(i, 0, n) {
        cin>>arr[i]; 
        sum+=arr[i]; 
    }
    
    if(sum % n) {cout << "NO\n"; return;}

    rep(i, 0, n-1){ //introduce new b
        //hitta ledig
        int f = 0;
        while(b[f]) f++; //no 0 input
        b[f] = arr[i];

        b[n-1] += n-(arr[i]%n); 
        b[n-1]%=n;
        assert(b[n-1] >= 0);

        while((a[f]+b[f])%n != c[f]){
            if((a[f]+b[f])%n == c[n-1]){
                swap(c[f], c[n-1]);
            }
            else if((a[f]+b[n-1])%n == c[n-1]){
                swap(posA[a[f]], posA[a[n-1]]);
                swap(a[f], a[n-1]);
            }
            else if((a[f]+b[n-1])%n == c[f]){
                swap(posA[a[f]], posA[a[n-1]]);
                swap(a[f], a[n-1]);
                swap(c[f], c[n-1]);
            }
            else{
                int newpos = posA[(c[f]-b[f]+n)%n]; //kan ej vara n-1 pga tidigare check

                swap(b[f], b[newpos]);
                swap(c[f], c[newpos]);
                swap(c[f], c[n-1]);
            }
        }
    }

    cout << "YES\n";
    vi ans(n);
    rep(i, 0, n) {
        if(!b[i]) b[i] = n;
        ans[a[i]] = b[i];
    }
    rep(i, 0, n){
        cout << ans[i] << " \n"[i==n-1];
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>t;
    rep(_, 0, t){
        solve();
    }
}
