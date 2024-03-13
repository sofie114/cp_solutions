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
ll const inf = LLONG_MAX, mxn = 3e5+2;
int n, m, ans[mxn];
vo<vi> adj(mxn);
map<int, vi> nodes; //val and nodeind
vi arr;

/*
activate nodes in ascending order, check neighbours that are not greater and
see if their component is big enough to eat you, if not: answer for all of the nodes this 
component contains because all the coming nodes you will active are bigger or equal and these smaller nodes cannot eat
more nodes. if the component is enough to eat me: do smaller to larger merging on the nodes your component and this component contains
*/

struct DSU{
    vi par, siz;
    vo<set<int>> kids; //val and node

    DSU(int n): par(n), siz(n), kids(n){
        rep(i, 0, n) {
            par[i] = i;
            siz[i] = arr[i];
            kids[i].insert(i);
        }
    }  
    int findpar(int v){
        if(par[v]==v) return v;
        return par[v] = findpar(par[v]);
    }

    void unite(int a, int b){
        a = findpar(a), b = findpar(b);
        if(a!=b){
            if(sz(kids[b]) > sz(kids[a])){
                swap(a, b);
            }
            par[b] = a;
            siz[a] += siz[b]; 
            for(auto x : kids[b]){
                kids[a].insert(x);
            }
            siz[b] = 0; kids[b].clear();
        }
    }

    void answer(int a){
        a = findpar(a);
        for(auto x: kids[a]){
            ans[x] = siz[a];
        }
        kids[a].clear(); //should not be able to be moved again
    }

};


signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m; arr.resize(n);
    rep(i, 0, n) {
        cin>>arr[i];
        nodes[arr[i]].pb(i);
    }
    rep(i, 0, m){
        int a, b; cin>>a>>b; a--, --b;
        adj[a].pb(b), adj[b].pb(a);

    }

    DSU g(n);
    int mx = *max_element(all(arr));
    for(auto size: nodes){
        for(auto x: size.se){
            for(auto w: adj[x]){
                if(arr[w] <= arr[x]){
                    if(g.siz[g.findpar(w)] < arr[x]){
                        g.answer(w);
                        g.unite(x, w);
                    }
                    else{
                        g.unite(x, w);
                    }
                }
            }

        }

        if(size.fi == mx){
            for(auto x: size.se){
                g.answer(x);
            }
        }
    }

    rep(i, 0, n) cout << ans[i] << " ";
}
