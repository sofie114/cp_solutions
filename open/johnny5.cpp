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
int n, e, sr, sc, c, ans;
vo<array<int, 4>> cans; //time coordinate
//dp states: can positions and previous can taken -> cans picked up (save energy used)
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
map<pii, int> explodeTime;
bool ir(int a, int b){  
    return a>=0&&b>=0&&a<n&&b<n;
}

int manhattan(int r, int c, int tr, int tc){
    return abs(r-tr)+abs(c-tc);
}

map<array<int, 4>, int> dp, dp2; //energy left, previous taken -> cans
void solve(){

    rep(i, 0, sz(cans)){
        int currR = cans[i][1], currC = cans[i][2], currtime = cans[i][0], reward = cans[i][3];

        for(auto x: dp){
            auto [eleft, r, c, prevtime] = x.fi; 
            int d = manhattan(r, c, currR, currC);

            if(reward == 1){
                if(d <= eleft && currtime - prevtime >= d){
                    int neweleft = eleft - d;
                    if(dp2.count({neweleft, currR, currC, currtime})){
                        dp2[{neweleft, currR, currC, currtime}] = max(dp2[{neweleft, currR, currC, currtime}], x.se+1);
                    }
                    else if(dp.count({neweleft, currR, currC, currtime})){
                        dp2[{neweleft, currR, currC, currtime}] = max(dp[{neweleft, currR, currC, currtime}], x.se+1); 
                    }
                    else{
                        dp2[{neweleft, currR, currC, currtime}] = x.se+1;
                    }
                }
            }
            else{
                if(d <= eleft && currtime - prevtime >= d){
                    int neweleft = eleft - d+1 ;
                    if(dp2.count({neweleft, currR, currC, currtime})){
                        dp2[{neweleft, currR, currC, currtime}] = max(dp2[{neweleft, currR, currC, currtime}], x.se);
                    }
                    else if(dp.count({neweleft, currR, currC, currtime})){
                        dp2[{neweleft, currR, currC, currtime}] = max(dp[{neweleft, currR, currC, currtime}], x.se); 
                    }
                    else{
                        dp2[{neweleft, currR, currC, currtime}] = x.se;
                    }
                }
            }
        }

        for(auto x: dp){
            if(dp2.count(x.fi)){
                dp2[x.fi] = max(x.se, dp2[x.fi]);
            }
            else{
                dp2[x.fi] = x.se;
            }
        }
 
        dp = dp2; dp2.clear();
    }

    for(auto x: dp) {
        ans = max(ans, x.se);
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>e>>sr>>sc>>c;

    dp[{e, sr, sc, 0}] = 0;
    rep(i, 0, c){
        int r, col, t; cin>>r>>col>>t;
        cans.pb({t, r, col, 1});

        for(auto x: dir){
            int nr = x[0]+r, nc = x[1]+col;
            if(ir(nr, nc)){
                cans.pb({t, nr, nc, 2});
            }
        }
    }
    sort(all(cans));
    solve();
    cout << ans;
}

/*
transition: look through all previous states
dp state: energy left, previous taken -> max cans
time complexity: O(200*500*500)

3 2 1 1 2
1 2 1
2 2 2
*/
