#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<int, int> pii;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define pren cerr << endl;
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
int const mxn = 1e5+4;
uset<string> tagged;
set<string> ans;
int n, m;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    string curr;
    rep(i, 0, n){
        string s; cin>>s;
        if(i==0) {
            curr = s;
            tagged.insert(s);
        }
    }

    rep(i, 0, m){
        string s1, s2, s3; cin>>s1>>s3>>s2;
        if(s1==curr){
            tagged.insert(s2);
            tagged.erase(s1);
            curr = s2;
        }
        else if(tagged.count(s1)){
            tagged.insert(s2);
            auto it = tagged.find(s1);
            tagged.erase(it);
        }
        else{
            ans.insert(s1);
            tagged.insert(s2);
        }
    }

    cout << sz(ans) << endl;
    for(auto x: ans) cout << x << " ";
}