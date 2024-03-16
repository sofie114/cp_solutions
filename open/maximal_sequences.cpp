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
ll const inf = LLONG_MAX, mxn = 1e5+4;
int n, arr[mxn], q, k, v;
umap<int, set<pii>> val;

bool f(int l, int r, vi& set){
    int sum = 0;
    rep(i, 0, k){
        v = set[i];
        auto it = val[v].lower_bound({l, -1}); //?

        int leftind, rightind;
        if(it==val[v].begin()) leftind = 0;
        else {it--; leftind = (*it).se;}

        auto it2 = val[v].upper_bound({r, inf});
        if(it2==val[v].begin()) rightind = 0;
        else {it2--; rightind = (*it2).se; }

        // pr(r, v, rightind, leftind)
        sum += rightind - leftind;

    }
    if(sum == r-l+1) return 1;
    else return 0;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(i, 0, n){
        cin>>arr[i];
        val[arr[i]].insert({i, 0});
    }
    for(auto kv: val){
        int i = 1;
        vo<pii> add;
        for(auto x: kv.se){
            add.pb({x.fi, i});
            i++;
        }
        val[kv.fi].clear();

        for(pii x: add){
            val[kv.fi].insert(x);
        }
    }
    cin>>q;
    rep(_, 0, q){
        int i;
        cin>>i>>k; i--;
        vi set;
        rep(u, 0, k) {cin>>v; set.pb(v);}

        int lo = i-1, hi=n;
        while(hi-lo>1){
            int mid = (hi+lo)/2;
            if(f(i, mid, set)) lo = mid;
            else hi = mid;
        }
        // pr(lo-i+1, lo)    
        cout << lo-i+1 << "\n";

    }
}
