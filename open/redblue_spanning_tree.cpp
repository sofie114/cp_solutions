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
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define repd(i, a, b) for(int i=(b-1); i >= a; i--)
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
int const inf = LLONG_MAX, mxn = 1e3+4;
int n, m, k;
vo<pii> red, blue;

struct dsu{
    vi par, rnk;
    dsu(int n): par(n), rnk(n){
        iota(all(par), 0);
    }

    int find(int v){
        if(par[v]==v) return v;
        return par[v] = find(par[v]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a!=b){
            if(rnk[a] < rnk[b]) swap(a, b);
            par[b] = a;
            if(rnk[a]==rnk[b]) rnk[a]++;
        }
    }
};

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k;
    rep(i, 0, m){
        char c; int a, b;
        cin>>c>>a>>b; a--, --b;

        if(c=='R') red.pb({a, b}); 
        else blue.pb({a, b});
    }

    dsu g(n);
    for(auto [a, b]: red){
        g.unite(a, b);
    }
    set<int> comps(g.par.begin(), g.par.end());
    if(k < comps.size()-1 ||  blue.size() < k || blue.size() < comps.size()-1) {cout << 0; exit(0);}
    

    //check how many blue edges we can place out avoiding cycles 
    dsu blueg(n);
    set<int> uniq; int ct = 0;
    for(auto [a, b]: blue){
        uniq.insert(a), uniq.insert(b);
        if(blueg.find(a) != blueg.find(b)) {blueg.unite(a, b); ct++;}
    }

    if(ct < k) cout << 0;
    else cout << 1;

}


/*
grafen garanteras vara connected

i en dsu, connecta alla röda
kolla antalet komponenter och se om comp-1 >= antal blå för att lösning ska finnas. inser att detta
är onödigt men det är en cool insikt att man kan reducera en SCC av bara röda kanter till ett spännande träd 

skapa en ny dsu och lägg till så många blå som möjligt så att inga cykler skapas (ordning spelar ej roll)
om antalet blå du kunde lägga till >= k så är svaret ja

Lemma: om ett spännande träd kan hittas med en mängd av blå kanter så finns lösningen där 
det endast finns k blå kanter bland mängden.
*/
