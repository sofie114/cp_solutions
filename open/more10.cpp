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
int n, ans=1, wordind;

struct dsu{
    vi par, rnk;
    dsu(int n): par(n), rnk(n, 0){
        iota(all(par), 0);
    }

    int find(int v){
        if(par[v]==v) return v;
        return par[v] = find(par[v]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a!=b){
            if(rnk[a]<rnk[b]) swap(a, b);
            par[b] = a;
            rnk[a]++;
        }
    }
};

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n; 
    int len = 3; 
    umap<string, set<int>> occ;
    umap<string, int> ind; 
    vo<array<string, 3>> q;
    vo<string> words;
    map<int, string> indToWord;
    rep(i, 0, n){
        string a, b, c;
        cin>>a>>c>>b;
        q.pb({a, b, c});
        if(!ind.count(a)){
            indToWord[wordind] = a;
            ind[a] = wordind++;
        }
        if(!ind.count(b)){
            indToWord[wordind] = b;
            ind[b] = wordind++;
        }
        if(a.size() < 3) words.pb(a);
        if(b.size() < 3) words.pb(b);
    }
    
    for(auto word: words){
        occ[word].insert(ind[word]);
    }

    for(auto [a, b, c]: q){
        int tmp = min(len, (int)min(a.size(), b.size()));
        occ[a.substr(a.size() - tmp, tmp)].insert(ind[a]);
        occ[b.substr(b.size() - tmp, tmp)].insert(ind[b]);
        while(tmp>1){
            tmp--;
            if(occ.count(a.substr(a.size()-tmp, tmp))) occ[a.substr(a.size(), tmp)].insert(ind[a]);
            if(occ.count(b.substr(b.size()-tmp, tmp))) occ[b.substr(b.size(), tmp)].insert(ind[b]);
        }
    }

    dsu g(wordind);
    for(auto [suf, v]: occ){
        int f = *v.begin();
        for(auto i: v){
            g.unite(i, f);
        }
    }
    for(auto [a, b, c]: q){
        if(c=="is"){
            g.unite(ind[a], ind[b]);
        }
    }
    for(auto [a, b, c]: q){
        if(c=="not"){
            if(g.find(ind[a]) == g.find(ind[b])) {ans = 0; break;}
        }
    }

    if(ans) cout << "yes";
    else cout << "wait what?";
}
