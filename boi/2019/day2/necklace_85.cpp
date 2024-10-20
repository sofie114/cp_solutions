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
int const inf = LLONG_MAX, mxn = 3005;
pii op;
int n, ans, m; 

void solve(string sa, string sb, int rev){
    vo<vi> LSP(n+1, vi(m+1, 0)), LPS(n+1, vi(m+1, 0)), LSS(n+1, vi(m+1, 0));
    // find LSS
    rep(i, 0, n){
        rep(u, 0, m){
            if(i==0 || u==0) LSS[i][u] = (sa[i]==sb[u]);
            else LSS[i][u] = (sa[i]==sb[u]) ? LSS[i-1][u-1]+1 : 0;
        }
    }
    // zxyabcd
    // ztcdabxy

    // find LSP, LPS
    rep(i, 0, n){
        rep(u, 0, m){
            int len = LSS[i][u]; 
            LSP[i][u-max(len-1, (int)0)] = max(LSP[i][u-max(len-1, (int)0)], len); 
            if(u>0) LSP[i][u] = max(LSP[i][u], LSP[i][u-1]-1);

            LPS[i-max(len-1, (int)0)][u] = max(LPS[i-max(len-1, (int)0)][u], len);
            if(i>0) LPS[i][u] = max(LPS[i][u], LPS[i-1][u]-1);
        }
    }

    // find max length
    rep(i, 0, n){
        rep(u, 0, m){
            int len = LSP[i][u]; pii pos = {i-len+1, u};
            if(u>0){
                len+=LPS[i+1][u-1];
                pos = {i-LSP[i][u]+1, u-LPS[i+1][u-1]};
            }

            if(len>ans){
                // pr(i, u, len, pos)
                if(rev) pos = {pos.fi, m-1-(pos.se+len-1)};
                ans = len; op = pos;
            }
        }
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string sa, sb;
    cin>>sa>>sb; n = sa.size(), m = sb.size();
    solve(sa, sb, 0); 
    reverse(all(sb)); solve(sa, sb, 1);

    cout << ans << endl << op.fi << " " << op.se; 
}

/*
subtask 1: for each length, loop through the window and for each window loop through a split of this substring into substrings a, b
and check if ab, ba, rev(ba), rev(ab) exists in string2. time complexity: n*n*n*n

full solution: 
Let the two strings be named sa and sb
LSS[i][u] = maximum common suffix of sa[:i] and sb[:u]
LSP[i][u] = maximum common suffix of sa[:i] and prefix of sb[u:]
LPS[i][u] = maximum common prefix of sa[i:] ans suffix of sb[:u]

If the answer has a window in sa [i, u] then this substring can further be split in into two substrings a,b
that should exist in sb as either: ab, ba, rev(ab), reb(ba). To handle the rev cases we can simply perform the algorithm to find ab,ba on rev(sb)

Reduced problem: find a substring ab such that ab or ba exists in sb. We can view ab as a special case of ba where a.size()==0

If sa[i:u] is an answer, then LSP[i][u]+LPS[i][u] == u-i+1; To check all pairs (i, u) we need n^2 time
To find LSP, LPS quickly we use the fact that:
LSP[i][u-LSS[i][u]] =  max(LSP[i][u-LSS[i][u]], LSS[i][u])
LSP[i][u] = max(LSP[i][u], LSP[i][u-1]-1)

This gives n^2 time
*/
