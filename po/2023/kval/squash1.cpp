#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr2(x) cerr << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr1(x) {cerr << x << " ";} cerr << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
#define pr(...) {cerr << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cerr << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cerr << arg << ", ";
    print_vars(args...);
}

//top down approach for squash, memoization instead of tabulation
//dp(i, amount important segments, active or not)

int const mxn = 1e3+10;
ll n, k, add[mxn];
vo<vo<vo<ll>>> dp(mxn, vo<vo<ll>>(mxn, vo<ll>(2, -1)));
string s;


ll solve(ll i, ll amt, ll act){
    if(dp[i][amt][act] != -1){
        return dp[i][amt][act];
    }

    //base case
    if(i==0 && act == 0 || amt==0){
        dp[i][amt][act] = 0;
        return 0;
    }
    if(i==0 && act==1) {
        dp[i][amt][act] = add[i];
        return add[i];
    }

    if(act==1){
        dp[i][amt][act] = max(solve(i-1, amt, 1)+add[i], solve(i-1, amt-1, 0)+add[i]);
    }
    else{
        dp[i][amt][act] = max(solve(i-1, amt, 0), solve(i-1, amt, 1));
    }
 
    return dp[i][amt][act];
}

int main(){
    cin >> n >> k >> s;
    rep(i, 0, n) {
        if(s[i] == 'V') add[i] = 1;
        else add[i] = -1;
    }

    cout << max(solve(n-1, k, 1), solve(n-1, k, 0));

}
