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
mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){return uniform_int_distribution<int>(l, r)(mt_rng);}

//go for outline with ;, then details
int const inf = LLONG_MAX, mxm = 5002, mxc = 500;
int r, c, m;
bitset<mxc> dp[mxm][mxc]; //dp[time point][row][col]

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c>>m;
    vo<bitset<mxc>> ini(r); bitset<mxc> emt;
    
    rep(i, 0, r){
        rep(u, 0, c){
            char ch; cin>>ch;
            if(ch=='.'){
                dp[0][i].set(c-1-u);
                ini[i].set(c-1-u);
            }
        }
    }

    rep(k, 1, m+1){
        char let; cin>>let;
        if(let=='W'){
            rep(i, 0, r){
                dp[k][i] = (dp[k-1][i] << 1) & ini[i]; 
            }
        }
        else if(let=='E'){
            rep(i, 0, r){
                dp[k][i] = (dp[k-1][i] >> 1) & ini[i];
            } 
        }
        else if(let=='N'){
            rep(i, 0, r){
                if(i==r-1) dp[k-1][i] = emt;
                else dp[k][i] = dp[k-1][i+1] & ini[i];
            } 
        }
        else if(let=='S'){
            rep(i, 0, r){
                if(i==0) dp[k][i] = emt;
                else dp[k][i] = dp[k-1][i-1] & ini[i]; 
            } 
        }
        else{
            rep(i, 0, r){
                dp[k][i] |= (dp[k-1][i]>>1) & ini[i];
                dp[k][i] |= (dp[k-1][i]<<1) & ini[i];

                if(i!=0) dp[k][i] |= dp[k-1][i-1] & ini[i];
                if(i!=r-1) dp[k][i] |= dp[k-1][i+1] & ini[i];
            }
        }
    }
    int ans = 0;
    rep(i, 0, r) ans += dp[m][i].count();

    cout << ans;
}

/*
subtask 1&2: notice they can be solved together easily. dp[i][u][time point] = 1 if the ship can be can be on row i column u at this time point
--> answer = dp[i][u][m] for all i, u.
in the function walk(i, u, pos) it performs the instruction on position pos from the cell (i, u) and calls the walk function for different i, u, pos
time complexity: m*(r*c) 

full solution: n bitsets of length m representing the grid. for each index in the message, 1 in the bitsets means the ships could be here
and 0 means it cannot. dp[k][i][u] = 1 if the ship can be at (i, u) at time k<=m. use bit shift, bit AND (to remove blocked cells), 
bit OR (when the instruction is ?) to solve. 
time complexity: m*(r*c / 64) 
*/
