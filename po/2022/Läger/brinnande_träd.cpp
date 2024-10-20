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
int const inf = LLONG_MAX, mxn = 4e5+5;
int n, A[mxn], X[mxn];

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(i, 0, n) cin>>X[i];
    rep(i, 0, n) cin>>A[i];

    priority_queue<int> pq;
    int sum = 0;
    rep(i, 0, n){
        sum += A[i]; pq.push(A[i]);
        if(sum > X[i]+A[i]){
            sum -= pq.top();
            pq.pop();
        }
    }

    cout << pq.size();
}

/*
subtask 1: save trees greedily, no use in skipping a tree
subtask 2: knapsack where a[i] are weights and x=capacity of knapsack
subtask 3 & 4: 
dp[k] = minimum time saving k trees, as position does no matter. 
conditional knapsack: let each tree be an item, A[i] are weights, capacity=n, dp[k]+A[i]<X[i]
time complexity: n*n

full solution - greedy:
loop through the trees in order and add saving them to our time, if it exceeeds the deadline
to save the current one, remove a tree from before that took the longest time to save

why this works:
instead of finding which to use, find which to not use
let pref[i] = A[0] + A[1] + ... + A[i-1]
we need pref[i] <= X[i] and if this is not satisfied we MUST exclude one of the trees 0 to i-1
which one do we exclude? the biggest A[u] clearly as each tree is worth the same. 

repeat this process
*/
