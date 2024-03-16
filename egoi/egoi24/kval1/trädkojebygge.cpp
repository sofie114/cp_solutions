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
int A, B, C, k, ans;
vo<vo<vo<pii>>> dp;

pii solve(int a, int b, int c){ //max våningar och rest 
    if(!a && !b && !c){
        return {0, 0};
    }
    if(dp[a][b][c] != pii({-1, -1})) return dp[a][b][c];

    pii ret = {0, 0};
    if(c){
        pii tmp = solve(a, b, c-1); tmp.se+=3;
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }

        if(tmp.se >= k) {tmp.fi++; tmp.se = 0;}
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }
    }

    if(b){
        pii tmp = solve(a, b-1, c); tmp.se+=2;
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }

        if(tmp.se >= k) {tmp.fi++; tmp.se = 0;}
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }
    }

    if(a){
        pii tmp = solve(a-1, b, c); tmp.se+=1;
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }

        if(tmp.se >= k) {tmp.fi++; tmp.se = 0;}
        if(ret.fi < tmp.fi){
            ret.fi = tmp.fi; 
            ret.se = tmp.se;
        }
        else if(ret.fi == tmp.fi){
            ret.se = max(ret.se, tmp.se);
        }
    }
    // pr(a, b, c, ret)
    dp[a][b][c] = ret;
    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>A>>B>>C>>k;
    dp.assign(A+1, vo<vo<pii>>(B+1, vo<pii>(C+1, {-1, -1})));

    ans = solve(A, B, C).fi;
    cout << ans;
}
