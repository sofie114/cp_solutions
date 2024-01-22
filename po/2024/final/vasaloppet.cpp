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
template<typename T> void _pr(const T &x) {int f=0; cerr << '{'; for(auto &i: x) cerr << (f++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

//go for outline with ;, then details
int const mxn = 1e5+4;
int n, t, s, ans;
vo<pii> breaks;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>t>>s;
    rep(i, 0, n){
        int l, r; cin>>l>>r;
        breaks.pb({l, r});
    }
    breaks.pb({t+1, t+1});

    int p1 = 0, p2 = 0, curr=0;
    while(p2 < n){
        int pil = breaks[p1].first + s;
        if(pil >= breaks[p2].second){
            curr += breaks[p2].second - breaks[p2].first;
            p2++;
        }
        else if(pil <= breaks[p2].second && pil >= breaks[p2].first) {
            ans = max(ans, curr + pil-breaks[p2].first);

            curr -= breaks[p1].second-breaks[p1].first;
            p1++;
        }
        else{
            curr -= breaks[p1].second-breaks[p1].first;
            p1++;
        }
        // pr(pil, curr, p1, p2)
        ans = max(ans, curr);
    }

    cout << s-ans;
}
