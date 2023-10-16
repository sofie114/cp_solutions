#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(s) s.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(x) x.begin(), x.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define repv(item, arr) for(auto item: arr) 
#define prvo(arr) for (auto item: arr){cout << item << " ";} cout << endl;
#define prar(n, arr) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
#define print(...) {cout << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cout << arg << ", ";
    print_vars(args...);
}

int const mxn = 1e3+10;
int dp[mxn], m, dishes[mxn];
long double n;  

int main(){
    cin >> n;
    rep(i, 0, 30){
        long double a; cin >> a;
        n = max(n+a, n*(a/100+1));
    }
    cout << setprecision(18) << n;
}