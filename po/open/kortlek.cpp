#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(x) cout << #x << "=" << x << endl

//what i dont use for no-google contests
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define printli(arr) for (auto x: arr){cout << x << " ";} cout << endl
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

int const mxn = 1e6;
int n, m, nicole[mxn], simon[mxn];

int main(){
    cin >> n >> m;
    rep(i, 0, n) cin >> nicole[i];
    rep(i, 0, m) cin >> simon[mxn];
    sort(nicole, nicole+n); sort(simon, simon+m);


}
