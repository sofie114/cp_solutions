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
ll const inf = LLONG_MAX, mxn = 505; 
int n, L;
vi rnk;
string stud[mxn];


signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>L; rnk.resize(n);
    vo<vi> rel(n, vi(L)), next1(n, vi(L));

    rep(i, 0, n){
        cin>>stud[i];
        if(i){
            rep(u, 0, L){
                if(stud[i][u] > stud[i-1][u]) rel[i][u] = 1; //correct relationship
                else if(stud[i][u] == stud[i-1][u]) rel[i][u] = 0;
                else rel[i][u] = -1;
            }

            int prev1 = -1;
            repd(u, 0, L){
                if(rel[i][u] == 1) prev1 = u;
                else if(rel[i][u] == -1) prev1 = -1;
                next1[i][u] = prev1;
            }
        }
    }

    int best = L; pii ans;
    rep(pos, 0, L){
        int maxi = -1;
        rep(i, 1, n){
            if(next1[i][pos] == -1) {maxi = -1; break;}
            maxi = max(maxi, next1[i][pos]);
        }

        if(maxi==-1) continue;
        int d = maxi - pos;
        if(d < best){
            best = d;
            ans = {pos, maxi};
        }
    }
    
    cout << ans.fi+1 << " " << ans.se+1;
}
