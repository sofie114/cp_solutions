#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
#define rs(x, a) x.resize(a); 
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
#define pren cerr << endl;
//what i dont use for no-google contests
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

/*
Idea: lets edges be the trade: b/a ratio, then find if there is a cycle you can multiply all edges and get > 1. This can however get integer overflow,
thus we use the log trick and add the edges instead and see if sum > 0. If there are precision problems, use Kahan's algorithm but long doubles worked too
Set all distances to 0 and use bellman ford to find if the emerald node value is increased after num_edges-1 times, when performing "longest path".
*/

//go for outline with ;, then details
int const mxn = 1e6;
int n, t, timer, em, ans;
vo<pair<long double, pair<int, int>>> edg;
umap<string, int> ind;
vo<long double> dist(mxn);


void bellmanFord(){
    rep(i, 0, 2*timer){
        for(auto x: edg){
            long double d = x.first;
            int u, v;
            tie(u, v) = x.second;

            long double newd = dist[u]+d;

            if(newd > dist[v])
            {
                dist[v] = newd;
                if(i>timer && v==em){
                    ans = 1;
                    return;
                }
            }
            
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(_, 0, n){
        int t; cin>>t;
        rep(i, 0, t){
            long double a, b; string c, d;
            cin>>a>>c>>b>>d;
            if(!ind.count(c)) ind[c]=timer++;
            if(!ind.count(d)) ind[d]=timer++;
            int u=ind[c], v=ind[d];


            edg.pb({log(b/a), {u, v}}); //log trick
        }
    }

    // pr(edg);

    //if no emerald
    if(ind.count("Emerald")) em = ind["Emerald"];
    else{
        cout << "no"; exit(0);
    }

    //bellman for and check if emerald node is increased after n-1 rounds
    bellmanFord();

    if(ans) cout << "yes";
    else cout << "no";
}

/*

*/
