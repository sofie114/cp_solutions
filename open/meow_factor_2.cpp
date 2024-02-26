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
ll const inf = INT_MAX, mxn = 1e5+4;
string s, m = "meow";
umap<char, int> cat = {{'m', 0},{'e', 1},{'o', 2},{'w', 3}};
set<vi> exist;

int editDistance(string a, int p1, int p2){
    if(p1 == 4) return 0;
    if(p2 == 5) return inf;
    
    int ret = inf;
    if(m[p1] == a[p2]){
        return editDistance(a, p1+1, p2+1);
    }

    //replace
    ret = min(ret, editDistance(a, p1+1, p2+1));
    //remove
    ret = min(ret, editDistance(a, p1, p2+1));
    //insert
    ret = min(ret, editDistance(a, p1+1, p2));
    //swap
    rep(i, p1+1, 5){
        if(a[i] == m[p1]){
            string tmp = a; tmp[i] = a[p1];
            ret = min(ret, editDistance(tmp, p1+1, p2+1));
        }
    }

    return ret+1;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>s; s += "xxxxx";

    rep(i, 0, sz(s)){
        vi tmp = {-1, -1, -1, -1, -1};
        rep(u, 0, 5){
            if(cat.count(s[i+u])){
                tmp[u] = cat[s[i+u]];
            }
        }
        
        exist.insert(tmp);

    }

    int ans = inf;
    for(auto x: exist){
        string tmp; 
        rep(i, 0, 5){
            if(x[i] == -1) tmp.pb('x');
            else tmp.pb(m[x[i]]);
        }
        ans = min(ans, editDistance(tmp, 0, 0));
    }

    cout << ans;
    
}
