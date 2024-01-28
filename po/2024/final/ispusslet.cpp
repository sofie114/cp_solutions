#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define sz(x) x.size()
#define s second  
#define f first
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
int const mxn = 20005;
// int const mxn = 10;
int r, c, k, sr, sc,  vis[mxn], start, color[mxn], iscycle[mxn], par[mxn], startodd=-1, grenodd=-1, nx[mxn];
vi ctvis1(mxn), ctvis2(mxn);
vo<set<int>> row, col;
vo<pii> crosses;
vo<set<pair<int, char>>> adj(mxn);
map<pii, int> nodeind, edg;
vo<char> ans1, ans2;


char other(char c){
    if(c=='>') return '<';
    else if(c=='<') return '>';
    else if(c=='^') return 'v';
    else return '^';
}

bool works(vi &ctvis, vo<char> &ans){
    rep(i, 0, sz(crosses)){
        if(ctvis[i] % 2 == 0) return 0;
    }
    //assert(sz(ans)<=1e2);

    cout << sz(ans) << endl;
    rep(i, 0, sz(ans)) cout << ans[i];
    return 1;
}
pii findodd(int at, int parent, int col){ //return if odd in subtree and if in odd cycle 
    color[at] = col;
    for(auto ok: adj[at]){
        int x = ok.f;
        if(x==parent) continue;

        if(color[x] != -1){
            if(color[x] != color[at]^1 && startodd==-1){
                startodd = x; iscycle[at]=1; nx[at] = x; 
                return {1, 1};
            }
            else return {0, 0};
        }

        pii tmp = findodd(x, at, color[at]^1); 
        // pr(at, x, tmp)
        if(at==start && tmp.f) grenodd = x;
        if(tmp.s){
            iscycle[at] = 1; nx[at] = x;
            // pr(at, start)
            if(at==startodd){
                return {1, 0};
            }
            return {1, 1};
        }
        else if(tmp.f) return {1, 0};
    }

    return {0, 0};
}

void dfs(int at, int parent, int rootcycle){
    vis[at] = 1;

    vo<pair<int, char>> toErase;
    for(auto ok: adj[at]){
        int x = ok.f; if(x==parent) continue;
        
        if(vis[x] || (iscycle[x] && x!=rootcycle && !(nx[x]==at && nx[at]==x))){
                toErase.pb(ok);
        }
        else dfs(x, at, rootcycle);
    }
    for(auto ok: toErase){
        // pr(ok)
        adj[at].erase(ok);
        adj[ok.f].erase({at, other(ok.s)});
    }
}

bool treesolution(int at, vi &ctvis, vo<char> &ans){ //return parity
    vis[at] = 1;

    ctvis[at]=1; if(at==start) ctvis[at]--;
    for(auto ok:adj[at]){
        int x = ok.f;
        if(!vis[x] && !iscycle[x]){
            vis[x] = 1; ctvis[at]++; ans.pb(ok.s);
            int tmp = treesolution(x, ctvis, ans); ans.pb(other(ok.s));

            if(!tmp){
                ctvis[at]++; ctvis[x]++;
                ans.pb(ok.s);
                ans.pb(other(ok.s));
            }

        }
    }

    if(ctvis[at] % 2 == 0) return 0;
    return 1;
}

void revsolution(int at, int prev){
    vis[at] = 1;

    ctvis2[at]++; if(at == start) ctvis2[at]--;
    for(auto ok: adj[at]){
        int x = ok.f;
        if(!vis[x] && x != nx[at] && !iscycle[x]){
            ans2.pb(ok.s); 
            bool tmp = treesolution(x, ctvis2, ans2);
            ans2.pb(other(ok.s)); ctvis2[at]++;

            if(!tmp){
                ctvis2[x]++; ctvis2[at]++; ans2.pb(ok.s); ans2.pb(other(ok.s));
            }
        }
    }

    // pr(at, next)

    if(prev != -1 && ctvis2[prev] % 2 ==0){
        ans2.pb(edg[{at, prev}]); ans2.pb(edg[{prev, at}]);
        ctvis2[at]++, ctvis2[prev]++;
    }
    
    if(nx[at]==startodd){
        ctvis2[startodd]++; ans2.pb(edg[{at, startodd}]);
        if(ctvis2[at]%2==0){
            ctvis2[startodd]++; ctvis2[at]++;
            ans2.pb(edg[{startodd, at}]);
            ans2.pb(edg[{at, startodd}]);
        }
        return;
    }
    else{
        ans2.pb(edg[{at, nx[at]}]);
        revsolution(nx[at], at);
        // pr(ans2);
    }
}

void pathToOdd(int at){
    vis[at]=1;
    bool startoddexist = 0;
    if(at!=start) ctvis2[at]++; 

    for(auto ok: adj[at]){
        int x = ok.f;
        // pr(x, vis[x], iscycle[x])
        if(x == startodd) startoddexist = 1;
        if(!vis[x] && x!=startodd && !iscycle[x]){
            vis[x] = 1; ans2.pb(ok.s);
            // pr(ctvis2)
            pathToOdd(x); ans2.pb(other(ok.s));
            ctvis2[at]++;
            // pr(at, ans2)
            // pr(ctvis2)

            if(ctvis2[x]%2==0){
                ctvis2[at]++, ctvis2[x]++;
                ans2.pb(ok.s);
                ans2.pb(other(ok.s));
            }
        }
    }

    // pr(at, startoddexist)
    if(startoddexist){
        ans2.pb(edg[{at, startodd}]);
        revsolution(startodd, -1);
        ans2.pb(other(edg[{at, startodd}])); ctvis2[at]++;
        // pr(ans2)
        // pr(ctvis2)
        if(ctvis2[startodd] % 2==0){
            ans2.pb(edg[{at, startodd}]);ans2.pb(other(edg[{at, startodd}]));
            ctvis2[at]++, ctvis2[startodd]++;
        }

    }

}

void dfs2(int at){ //hantera om s är i cykeln
    vis[at] = 1;

    ctvis2[at]++; if(at==start) ctvis2[at]--;
    for(auto ok:adj[at]){
        int x = ok.f;
        if(!vis[x] && x!=grenodd && !iscycle[x]){
            vis[x] = 1; ans2.pb(ok.s);
            dfs2(x); ans2.pb(other(ok.s)); ctvis2[at]++;

            if(ctvis2[x]%2==0){
                ctvis2[at]++; ctvis2[x]++;
                ans2.pb(ok.s);
                ans2.pb(other(ok.s));
            }

        }
    }

    if(at==start){
        if(iscycle[start]){
            revsolution(start, -1);
        }
        else{
            pathToOdd(start);
            // pr(at, ans2)
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c>>k;
    row.resize(r+1); col.resize(c+1); 
    
    int ind = 0;
    rep(i, 0, r){
        rep(u, 0, c){
            char c; cin>>c;
            if(c=='X'){
                row[i].insert(u); col[u].insert(i);
                crosses.pb({i, u});
                nodeind[{i, u}] = ind; ind++;
            }
            else if(c=='S'){
                sr=i, sc=u;
                row[i].insert(u); col[u].insert(i);
                crosses.pb({i, u});
                nodeind[{i, u}] = ind; ind++;
            }
        }
    }

    for(auto x: crosses){
        auto it = row[x.f].upper_bound(x.s);
        if(it!=row[x.f].end()){
            pii a = {nodeind[x], nodeind[{x.f, *it}]}, b = {nodeind[{x.f, *it}], nodeind[x]};

            edg[a] = '>'; edg[b] = '<';

            adj[a.f].insert({a.s, edg[a]});
            adj[b.f].insert({b.s, edg[b]});
        }

        auto it2 = col[x.s].upper_bound(x.f);
        if(it2!=col[x.s].end()){
            pii a = {nodeind[x], nodeind[{*it2, x.s}]}, b = {nodeind[{*it2, x.s}], nodeind[x]};
            edg[a] = 'v', edg[b] = '^';
            adj[nodeind[x]].insert({nodeind[{*it2, x.s}], 'v'});
            adj[nodeind[{*it2, x.s}]].insert({nodeind[x], '^'});
        }
    }
    start = nodeind[{sr, sc}];


    // pr(start)
    // pr(adj);

    treesolution(start, ctvis1, ans1);
    // pr(ctvis1)

    if(k==0 && ctvis1[start]%2==0){ 
        if(sz(adj[start])){
            ans1.pb((*adj[start].begin()).s);
            ans1.pb(other((*adj[start].begin()).s));
            ans1.pb((*adj[start].begin()).s);
            ctvis1[start]++;
        }
    }

    if(works(ctvis1, ans1)) exit(0);
    if(k==0) {
        cout << -1;
        exit(0);
    }


    memset(vis, 0, sizeof(vis)); memset(color, -1, sizeof(color)); memset(nx, -1, sizeof(nx));
    findodd(start, start, 0);
    // rep(i, 0, sz(crosses)){
    //     if(iscycle[i]) dfs(i, i, i);
    // }
    // pr(adj)
    // pr(startodd, grenodd);
    // pr(iscycle)
    // pr(nx)
    
    if(startodd !=-1) {
        dfs2(start);
        // pr(ctvis2, ans2)
        if(works(ctvis2, ans2)){
            exit(0);
        }
    }

    cout << -1;

}


/*
skapa ctvis för alla subträd i grafen
ta bort alla extra kanter när jag hittar udda cykeln?

3 7 1
S.X...X
X......
..X.X.X

4 7 1
X...X..
X.S.X..
..X....
..X....

4 5 1
.X...
XS.XX
.X..X
.X..X

5 5 1
S.XX.
X....
XX...
.X...
XX...
*/
