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
int const inf = LLONG_MAX, mxn = 300;
int n, m, k, meal[mxn], mxhours[mxn], sum, ans = inf;

void sol1(){
    if(m==1){
        if(k==1 && sum<=mxhours[0]) ans = mxhours[0]-sum;
    }
    else if(m==2){
        if(k==1){
            if(sum<=mxhours[0]) ans = mxhours[0]-sum;
            else if(sum<=mxhours[1]) ans = min(ans, mxhours[1]-sum);
            else if(sum<=mxhours[0]+mxhours[1]) ans = min(ans, mxhours[0]+mxhours[1]-sum);
        }
        else if(k==2){
            if(sum<=mxhours[0]+mxhours[1] && min(mxhours[0], mxhours[1])>=n){
                ans = mxhours[0]+mxhours[1]-sum;
                rep(i, 0, n) if(meal[i]<2) ans = inf;
            }
        }  
    }
}
int wastedTime(vi &chefs, int sumwork){
    if(sumwork < sum) return inf;

    int sumuniq = 0; 
    for(auto chef: chefs){
        sumuniq += min(mxhours[chef], n);
    }

    if(sumuniq < k*n) return inf;
    else return sumwork - sum;
}
void sol3(){
    int mxval = 90310; vi dp(mxval, 0); dp[0] = 1;
    rep(chef, 0, m){
        repd(i, 0, mxval){
            if(dp[i]){
                int nw = mxhours[chef]+i;
                if(nw < mxval) dp[nw] = 1;
            }
        }
    }

    rep(i, sum, mxval) 
        if(dp[i]){
            ans = i-sum; break;
        }
}

void fulsol(){
    int mxval = 90310; vo<pii> dp(mxval); dp[0] = {1, 0};
    rep(chef, 0, m){
        repd(i, 0, mxval){
            if(dp[i].fi){
                int nw = mxhours[chef]+i, uniqhours = dp[i].se+min(n, mxhours[chef]);
                if(nw < mxval){
                    dp[nw].fi = 1;
                    dp[nw].se = max(dp[nw].se, uniqhours);
                }
            }
        }
    }

    rep(i, sum, mxval) 
        if(dp[i].fi && dp[i].se>=k*n){
            ans = i-sum; break;
        }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    rep(i, 0, n) {
        cin>>meal[i]; sum+=meal[i];
    }
    rep(i, 0, m) cin>>mxhours[i]; 
    rep(i, 0, n){
        if(meal[i] < k){
            cout << "Impossible"; exit(0);
        }
    }

    if(m<=2){
        sol1();
    }
    else if(m<=15){
        rep(mask, 0, (1<<m)){
            vi chefs; int sumwork = 0;
            rep(i, 0, m){
                if((mask>>i) & 1) {chefs.pb(i); sumwork+=mxhours[i];}
            }
            ans = min(ans, wastedTime(chefs, sumwork));
        }

    }
    else if(k==1){
        sol3();
    }
    else{
        fulsol();
    }

    if(ans == inf) cout << "Impossible";
    else cout << ans;
}

/*
subtask 1: case-analysis for m,k in {1, 2}
subtask 2: subset bruteforce, use bitmask. see that we can also get prev subtask if we create a function 
f(vi chefs, sumchefhours) that returns wasted time
subtask 3: subset sum and find biggest r=subsetsum such that r<=sumhours. time complexity: maxval*ppl = (maxA*n)*m <= 3e7 
subtask 4: dp[sum] = {a1, a2, ... , an} where a1 is how many chefs working on person 1. time: mxsum * chefs * dishes = 40^4
subtask 5: dp[sum] = {x, y};
x = if it is reachable
y = maximum sum of hours we can get such that no person gets the same chef twice = sum of min(n, mxhours[i])} for all chefs i included
*/
