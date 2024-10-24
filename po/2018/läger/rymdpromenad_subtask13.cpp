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

void sol1(int pos, int ind, int clockwise, int moves){
    if(ind==m){
        ans = min(ans, moves+abs(clockwise));
        return;
    }
    sol1(wind[ind], ind+1, clockwise + cl(pos, wind[ind]), moves+(n+wind[ind]-pos)%n);
    sol1(wind[ind], ind+1, clockwise - an(pos, wind[ind]), moves + (n+pos-wind[ind])%n);
}

void checkclock(int a, int b, int fulrot, int steps, map<int, int>& dp){
    if(a+b > n) fulrot++;
    if(dp.count(fulrot)) dp[fulrot] = min(dp[fulrot], steps+b);
    else dp[fulrot] = steps+b;
}
void checkanti(int a, int b, int fulrot, int steps, map<int, int>& dp){
    if(a-b <= 0) fulrot--;
    if(dp.count(fulrot)) dp[fulrot] = min(dp[fulrot], steps+b);
    else dp[fulrot] = steps+b;
}

void sol3(){
    map<int, int> pdp; // p(rev)dp[i] = minimum steps to have (i*n+window[i-1]) extra clockwise rotation
    int to, from=1;

    rep(i, 0, m){ // get to window i 
        map<int, int> dp;
        to = wind[i];
        int clockwise = cl(from, to), anti = an(from, to);
        from = wind[i];

        if(i==0){
            dp[0] = clockwise; dp[-1] = anti;
        }
        else{
            for(auto [fulrot, steps]: pdp){
                checkclock(wind[i-1], clockwise, fulrot, steps, dp);
                checkanti(wind[i-1], anti, fulrot, steps, dp);
            }
        }
        swap(pdp, dp);
    }

    for(auto [fulrot, steps]: pdp){
        if(fulrot < 0) ans = min(ans, steps + abs(fulrot)*n-wind[m-1]+1);
        else ans = min(ans, steps+fulrot*n+wind[m-1]-1);
    }
}

int topdown(int i, int fulrot, vo<vi>& dpc, vo<vi>& dpa){
    if(i==m) return abs(wind[i]-1+fulrot*n);
    if(fulrot>=0 && dpc[i][fulrot]!=inf) return dpc[i][fulrot];
    else if(fulrot<0 && dpa[i][-fulrot]!=inf) return dpa[i][-fulrot];

    int clockwise = cl(wind[i], wind[i+1]), anti = an(wind[i], wind[i+1]), a = fulrot, b = fulrot;

    if(wind[i]+clockwise>n) a++;
    if(wind[i]-anti<=0) b--;
    int ret = min(topdown(i+1, a, dpc, dpa)+clockwise, topdown(i+1, b, dpc, dpa)+anti);

    if(fulrot>=0) dpc[i][fulrot] = ret;
    else dpa[i][-fulrot] = ret;
    return ret;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m; wind.resize(m);
    rep(i, 0, m) cin>>wind[i];

    if(n<=10 && m<=0) sol1(1, 0, 0, 0);
    else if(m<=1000){
        // top down, dp[i][u] = min dist to walk from window i to m, arriving at window i with wind[i]+u*n rotations clockwise
        wind.insert(wind.begin(), 1);
        vo<vi> dpc(m, vi(m+2, inf)), dpa(m, vi(m+2, inf));
        ans = topdown(0, 0, dpc, dpa);

        // bottom up
        // sol3();
    }
    cout << ans;
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
