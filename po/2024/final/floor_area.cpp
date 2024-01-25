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
int n, r, c, rig, lef, up, down;
string s;

ll pos1(ll lim){
    ll curr =0;
    rep(i, 0, n){
        if(s[i] == 'v') curr = min(curr+1, lim);
        else if(s[i]=='^') curr = max(ll(0), curr-1);
    }
    return curr;
}

ll pos2(ll lim){
    ll curr =0;
    rep(i, 0, n){
        if(s[i] == '>') curr = min(curr+1, lim);
        else if(s[i]=='<') curr = max(ll(0), curr-1);
    }
    return curr;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>s>>r>>c;

    rep(i, 0, n){
        if(s[i]=='>') rig++;
        else if(s[i]=='<') lef++;
        else if(s[i]=='v') down++;
        else up++;
    }

    //handle vertical
    ll lo = -1, hi = 3e5+2;
    while(hi-lo>1){
        ll mid = (hi+lo)/2;
        // pr(mid, pos1(mid))
        if(pos1(mid) >= r) hi = mid;
        else lo = mid;
    }


    ll lo2 = -1, hi2 = 3e5+2;
    while(hi2-lo2>1){
        ll mid = (hi2+lo2)/2;
        if(pos2(mid) >= c) hi2 = mid;
        else lo2 = mid;
    }

    // pr(hi, hi2)
    if(hi2==3e5+2 || hi==3e5+2) {cout << -1; exit(0);}

    cout << (hi+1)*(hi2+1);
}
