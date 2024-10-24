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
int const inf = 1e16, mxn = 1e5+4;
int n, m, ans = inf;
vi wind;

int cl(int a, int b){return (n+b-a)%n;}
int an(int a, int b){return (n+a-b)%n;}

int topdown(int i, int rot, vo<vi>& dpc, vo<vi>& dpa){
    if(i==m) return abs(rot);
    if(rot>=0 && dpc[i][rot]!=inf) return dpc[i][rot];
    else if(rot<0 && dpa[i][-rot]!=inf) return dpa[i][-rot];
    int clockwise = cl(wind[i], wind[i+1]), anti = an(wind[i], wind[i+1]);

    int ret = min(topdown(i+1, rot+clockwise, dpc, dpa)+clockwise, topdown(i+1, rot-anti, dpc, dpa)+anti);
    if(rot>=0) dpc[i][rot] = ret;
    else dpa[i][-rot] = ret;
    return ret;
}
void sol2(){
    map<int, int> pdp; // p(rev)dp[i] = minimum steps to have i rotation and get to previous window (positive is clockwise rotation)
    int to, from=1;

    rep(i, 0, m){ // get to window i 
        map<int, int> dp;
        to = wind[i];
        int clockwise = cl(from, to), anti = an(from, to);
        from = wind[i];

        if(i==0){
            dp[clockwise] = clockwise; dp[-anti] = anti;
        }
        else{
            for(auto [rot, steps]: pdp){
                if(dp.count(rot+clockwise)) dp[rot+clockwise] = min(dp[rot+clockwise], steps+clockwise);
                else dp[rot+clockwise] = steps+clockwise;

                if(dp.count(rot-anti)) dp[rot-anti] = min(dp[rot-anti], steps+anti);
                else dp[rot-anti] = steps+anti;
            }
        }
        swap(pdp, dp);
    }
    for(auto [rot, steps]: pdp) ans = min(ans, steps+abs(rot));
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m; wind.resize(m+5);
    rep(i, 0, m) cin>>wind[i];

    if(n<=100 && m<=100){
        //top down, dpc[i][u] = min moves to go from windows i-m when arrived at i with u rotation clockwise, dpa but for anticlockwise
            wind.insert(wind.begin(), 1);
            vo<vi> dpc(m, vi(n*m+1, inf)), dpa(m, vi(n*m+1, inf)); //clockwise and anticlockwise dp
            cout << topdown(0, 0, dpc, dpa);

        // bottom up
            // sol2();
    }
}

/*
subtask 1: from each window, we either walk clockwise or anticlockwise. try both. time complexity: n! = 10! ok
subtask 2: 
    top down: dpc[i][u] = min moves to visit windows i-m (starting at i) with u rotation clockwise
    bottom up: dp[i][u] = minimum moves to arrive at window i with u extra clockwise/anticlockwise steps 
    O(m*(n*m)) as u < n*m 
subtask 3: realize abundant dp states:
    dp[i][u] = minimum moves to arrive at window i with u with (u*n+wind[i-1]) extra clockwise rotation
    O(m*m)

full solution: 
    a greedy solution. 
    insight: changing a move from clockwise to anticlockwise changes the extra clockwise rotation with -n: 
    moving from pos1 to pos2 clockwise is pos2-pos1 and anticlockwise is n-(pos2-pos1)
    changing clockwise movement includes -(pos1-pos2) and -(n-(pos2-pos1) which sums to -n
    --> change in rotation is the same when we choose a window to change clockwise to anticlockwise
    we can begin with all moves being clockwise and change those which saves the most moves. 
*/
