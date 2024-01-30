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
int const mxn = 2e5+10;
int n, c, work[mxn], home[mxn], stand[mxn], lpar[mxn], vis[mxn], homenode[mxn], dep[mxn], dad[mxn];
int nodeToCarInd[mxn];
vo<vi> adj(mxn); 
vi ans;

int findp(int v){ //return lowest parent which is a car;
    return (v==0 || stand[v]) ? v: lpar[v] = findp(lpar[v]);
}

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;
    LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

void dfs(int at, int parent, int depth){
    dep[at] = depth++;

    for(auto x: adj[at]){
        if(x==parent) continue;
        dad[x] = at;
        dfs(x, at, depth);
    }
}


bool solve(int at, LCA &tree){
    vis[at] = 1;
    int lca = tree.lca(at, homenode[at]);

    int x1 = findp(dad[at]);
    // pr(at, homenode[at], lca, x1, x2, d1, d2)

    while(dep[x1] >= dep[lca]){
        if(vis[x1]) return 0;
        if(x1 == at) break;

        int tmp = solve(x1, tree);
        if(!tmp) return 0;
        
        x1 = findp(x1);
    }

    int x2 = findp(homenode[at]);
    while(dep[x2] >= dep[lca]){
        if(x2==at){
            break;
        }
        if(vis[x2]) return 0;

        int tmp = solve(x2, tree);
        if(!tmp) return 0;

        x2 = findp(x2);
    }

    ans.pb(nodeToCarInd[at]);
    stand[at] = 0; 
    return 1;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>c; 
    adj[0].pb(1), adj[1].pb(0);
    rep(i, 0, n-1){
        int a, b; cin>>a>>b;
        adj[a].pb(b), adj[b].pb(a);
    }
    rep(i, 1, c+1){
        cin>>work[i]>>home[i]; 
        homenode[work[i]] = home[i]; nodeToCarInd[work[i]] = i;
        stand[work[i]]++;
    }

    dfs(0, 0, 0);

    LCA tree(adj);

    rep(i, 1, n+1){
        if(stand[i] && !vis[i]){
            bool ok = solve(i, tree);
            if(!ok) {
                cout << "No"; exit(0);
            }
        }
        
    }

    cout << "Yes" << endl;
    for(auto x: ans) cout << x << " ";

}



/*
fenwick tree on tintout euler tour (updateable) to find cars between nodes a and b
create a graph which finds the order of the cars using the relationship order

7 3
1 2
2 3
3 4
2 5
1 6
6 7
4 2
1 2
6 1



6 3
1 2
2 3
3 4
3 5
5 6
4 6
5 3
2 4


6 3
1 2 
2 3
2 4
1 5
5 6
1 3
2 4
6 5

5 2
1 2
1 3
1 4
1 5
5 3
4 2

6 2
1 2
2 3
3 4
1 5
5 6
4 2
5 6

*/
