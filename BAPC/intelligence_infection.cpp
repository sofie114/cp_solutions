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
int const mxn = 1e5+5;
int n, e, m, vis[mxn], add=0;
vo<vi> adj(mxn);
vo<uset<int>> dag(mxn), par(mxn);
vi comp, enemy(mxn), newEnemy(mxn), enemyinchild(mxn), msg(mxn), compsz(mxn);
//msg 1=public, -1=private, 0=dont start message here

struct SCC{
    int timer=0;
    vi disc, stack, comps;
    SCC(vo<vi>& adj, int n){
        disc.resize(n), comps.resize(n), comp = vi(n, -1);
    }       
    
    int dfs(int at){
        disc[at] = timer++; int low = disc[at];
        stack.pb(at);

        for(auto x: adj[at]){
            if(comp[x]==-1){
                if(!disc[x]) low = min(low, dfs(x));
                else low = min(low, disc[x]);
            }
        }
        if(low==disc[at]){
            comps.pb(at);
            for(int tmp=-1; tmp!=at;) {
                comp[tmp=stack.back()] = at; //tmp changed before usage
                stack.pop_back();
            }
        }
        return low;
    }
    void gen(){
        rep(i, 0, n){
            if(!disc[i]) dfs(i);
        }
    }
};

struct topologicalSort{ 
    int n;
    vi order, vis;
    vo<uset<int>> adj;
    topologicalSort(vo<uset<int>>& _adj, int _n): n(_n), adj(_adj), vis(n) {}

    void topo_dfs(int at){
        vis[at] = 1;

        for(auto x:adj[at]){
            if(!vis[x]) topo_dfs(x);
        }
        order.pb(at);
    }
    vi getOrder(){
        rep(i, 0, n){
            if(!vis[comp[i]]) topo_dfs(comp[i]);
        }
        reverse(order.begin(), order.end());
        return order;
    }
};

//dfs to find if enemy in children
int dfs(int at){
    if(vis[at]) return enemyinchild[at];
    vis[at]=1;

    for(auto x: dag[at]){
        enemyinchild[at] |= dfs(x);
        par[x].insert(at);
    }   
    return enemyinchild[at];
}



int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>e>>m;
    rep(i, 0, m){
        int a, b; cin>>a>>b;
        adj[a].pb(b);
    }
    rep(i, 0, e){
        int a; cin>>a; enemy[a]=1;
    }

    SCC scc(adj, n);
    scc.gen();

    //enemy och vilka noder som har enemy barn för nya grafen som är en dag
    rep(i, 0, n){
        if(enemy[i]){
            newEnemy[comp[i]]=1;
            enemyinchild[comp[i]]=1;
        }
        else{
            compsz[comp[i]]++;
        } 
        
        for(auto x: adj[i]){
            if(dag[comp[i]].count(comp[x]) || comp[i]==comp[x]) continue;
            dag[comp[i]].insert(comp[x]); 
        }
    }

    //ge alla noder benämningar beroende på om de kan få en public, private message
    rep(i, 0, n){
        if(!vis[i]) dfs(comp[i]);
        if(!newEnemy[comp[i]]){
            if(enemyinchild[comp[i]]){
                msg[comp[i]]=-1;
            }
            else{
                msg[comp[i]]=1;
            }

        }
        else add+=compsz[i];
    }

    topologicalSort ts(dag, n);
    vi order = ts.getOrder();

    //kolla om vi har en ancestor som är source för public message
    rep(i, 0, sz(order)){
        for(auto x: par[order[i]]){
            if(msg[x]>=1 && msg[order[i]]==1){
                msg[order[i]]=2;
            }
        }
    }

    //räkna alla public+private message + vita i en SCC
    int ans =0;
    rep(i, 0, n){
        if(msg[i]==2) ;
        else if(msg[i]==-1) ans+=compsz[i];
        else if(msg[i]==1) ans++;
    }

    //add är vita i en enemy SCC
    cout << ans+add;
}
/*
4 2 4
0 1
1 2
0 3
3 2
0 1

5 1 6
0 1
1 0
1 2
2 3
3 2
4 2
0
*/
