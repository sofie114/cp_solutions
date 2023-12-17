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
int const mxn = 1010;
int n;
string s;
vi consecA(mxn);

int cost(char c){
    return min('Z' - c+1, c - 'A');
}

int basecost(){
    int ct=0;
    rep(i, 0, sz(s)){
        ct+=cost(s[i]);
    }
    return ct;
}

void calcConsecutive(int n){
    if(s[n-1]=='A')
        consecA[n-1]=1;
    else consecA[n-1]=0; //unnecessary if array assigned to 0

    repd(i, 0, n-1){
        if(s[i]=='A'){
            consecA[i]=consecA[i+1]+1;
        }
        else consecA[i]=0;
    }
}

int findcost(int i, int segm, int n){
    if(i==0) return n-segm;
    if(i+segm >= n) return i-1;
    return min(2*(i-1) + (n-(i+segm)), i-1 + 2*(n-(i+segm))); 
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    rep(_, 0, n){
        cin>>s;
        int ans = basecost();
        int add=1e9;


        consecA.assign(sz(s), 0);
        calcConsecutive(sz(s));

        rep(i, 0, sz(s)){
            if(consecA[i]){
                add = min(add, findcost(i, consecA[i], sz(s)));
            }
        }

        // pr(ans, add);
        cout << min(ans+add, int(ans+sz(s)-1)) << endl;
    }

}
