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
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
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
int const inf = LLONG_MAX, mxn = 1e3+10;
int n; 
set<int> general[mxn];

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(i, 1, n){
        rep(u, 0, i){
            int a; cin>>a;
            if(u < (i/2 + i%2)) general[i].insert(a);
        }
    }

    vi ans = {0};
    rep(i, 1, n){
        rep(u, 0, ans.size()){
            if(u==0){
                if(general[i].count(ans[0])){
                    auto it = ans.begin();
                    ans.insert(it, i);
                    break;
                }
            }
            else if(u==ans.size()-1){
                if(general[i].count(ans.back())){
                    ans.pb(i);
                    break;
                } 
            }
            else{
                if(general[i].count(ans[u]) && general[i].count(ans[u+1])){
                    auto it = ans.begin()+u+1;
                    ans.insert(it, i);
                    break;
                }
            }
        }
    }

    rep(i, 0, n) cout << ans[i] << " ";
}
