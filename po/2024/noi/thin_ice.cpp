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
ll const inf = LLONG_MAX, mxn = 2e5+4;
int r, c, ans, val[mxn], siz[mxn], conEdge[mxn], add[mxn], solesiz[mxn];
set<int> dp[mxn];
vo<vi> tbl;
map<int, set<int>, greater<int>> order; //all comps of val=key;
 
int compress(int a, int b){
    return a*c + b;
}
 
struct dsu{
    vi par, siz, val, conEdge, compind;
    vo<set<int>> nei;
    dsu(int n): par(n), siz(n, 1), val(n), nei(n), conEdge(n, 0), compind(n, -1){
        rep(i, 0, n) par[i] = i;
    }
    int findpar(int v){
        if(v==par[v]) return v;
        return par[v] = findpar(par[v]);
    }
    void unite(int a, int b){
        a = findpar(a), b = findpar(b);
        if(a!=b){
            if(siz[b] > siz[a]) swap(a, b);
            par[b] = a;
            siz[a] += siz[b]; siz[b] = 0;
            conEdge[a] |= conEdge[b];
            compind[a] = max(compind[a], compind[b]); //eeeh?
        }
    }
};
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c;
}
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c; 
    tbl.assign(r, vi(c, 0));
    dsu g(r*c);
    rep(i, 0, r){
        rep(u, 0, c){
            cin>>tbl[i][u];
            if(i==0 || u==0 || i==r-1 || u==c-1) g.conEdge[compress(i, u)] = 1;
        }
    }
 
    rep(i, 0, r){
        rep(u, 0, c){
            for(auto [nr, nc]: dir){
                nr+=i, nc+=u;
                if(ir(nr, nc) && tbl[i][u] == tbl[nr][nc]){
                    g.unite(compress(nr, nc), compress(i, u));
                }
            }
        }
    }
    rep(i, 0, r){
        rep(u, 0, c){
            int b = compress(i, u); b=g.findpar(b); g.val[b] = tbl[i][u];
            order[tbl[i][u]].insert(b);
            for(auto [nr, nc]: dir){
                nr+=i, nc+=u;
                if(ir(nr, nc)){
                    int a = compress(nr, nc);
                    a = g.findpar(a);
                    if(tbl[i][u] >= tbl[nr][nc]){ //större grannar
                        g.nei[a].insert(b); 
 
                    }
                    if(tbl[nr][nc] >= tbl[i][u]){
                        g.nei[b].insert(a);
                    }
                }
            }
        }
    }

    //find all indirect and direct smaller comps neighbours
    int compind = 0;
    for(auto size: order){
        set<array<int, 3>> prevnei;
        //find compind to assign new dp
        for(auto x: size.se){ 
            prevnei.insert({x, -1, 0});
            for(auto neigh: g.nei[x]){
                neigh = g.findpar(neigh);
                prevnei.insert({neigh, g.compind[neigh], g.siz[neigh]});
            }
        }
        for(auto x: size.se){
            x = g.findpar(x);
            prevnei.insert({x, g.compind[x], g.siz[x]});
        }
        
        for(auto x: size.se){ //neigh is bigger
            for(auto neigh: g.nei[x]){
                g.unite(neigh, x);
            }
        }
        
        map<int, int> newcompind;
        for(auto [neigh, prevcompind, prevsiz]: prevnei){
            int nw = g.findpar(neigh);
            if(newcompind.count(nw)){
                if(prevcompind != -1) 
                    dp[prevcompind].insert(newcompind[nw]);
            }
            else{
                if(prevcompind != -1)
                    dp[prevcompind].insert(compind);
                newcompind[nw] = compind;
                g.compind[nw] = compind;
                val[compind] = size.fi;
                siz[compind] = g.siz[nw];
                conEdge[compind] = g.conEdge[nw];

                compind++;
            }
        }
    }

    //just go through comps increasing order

    repd(ind, 0, compind){
        if(dp[ind].size()==0) add[ind] = min(val[ind], solesiz[ind]);

        for(auto childind: dp[ind]){ //add saves best val until child
            add[ind] = max(add[ind], min(val[childind], add[childind] + siz[childind] - siz[ind]));
        }
        if(conEdge[ind]) ans = max(ans, min(val[ind], add[ind] + siz[ind]));
    }
 
    cout << ans;
}
/*
om varje komponent innehåller rutor av samma nivå. 
aktivera en komponent och kolla efter komponenter av mindre nivå (som ska vara mergade) som
kan nås antingen direkt eller indirekt via rutor av högre nivå.

de mindre nivå komponterna har ett eget bästa svar : min(val[comp], compsize after merged with bigger/equal)
de mindre nivå komponenterna har ett tmp värde: min(val[comp], prevtmp + compsize) 

vi kan använda tmp värdet

för hitta dessa grannar: precomputa genom att merga större med mindre och skapa kanter mellan nya komponent och gamla komponents
information, information är allt som behövs. 

gör samma sak i början men spara barn i parcomps och ej rev
vid merge, prevcompind.insert(newcompind)
*/
