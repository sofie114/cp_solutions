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

//go for outline with ;, then details
/*
Repeatedly construct highest sum with least number of items
*/
int const mxn = 1000;
int s, m, l, shelf, ans, yes;
ar<int, 3> cont;

 
int solve(int a, int b, int c, int sum){
    if(sum>shelf || a>s || b>m || c>l) return 0;

    int ret = sum, r1 = solve(a, b, c+1, sum+3), r2=solve(a, b+1, c, sum+2), r3 =solve(a+1, b, c, sum+1);
    ret = max(max(r1, ret), max(max(r2, ret), max(r3, ret)));


    if(!yes){
        cont = {a, b, c}; yes=1;
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>s>>m>>l>>shelf;
    while(s||m||l){
        yes=0;
        solve(0, 0, 0, 0);
        s-=cont[0], m-=cont[1], l-=cont[2]; ans++;
    }
    cout << ans;
}

