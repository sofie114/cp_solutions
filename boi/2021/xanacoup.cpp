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
int const inf = 1e9, mxn = 1e5+4;
int n, ans=inf;
vo<vi> adj(mxn);
vi col, ini, off;

void press(int at){
    col[at] = 1-col[at];
    for(auto x: adj[at]){
        col[x] = 1-col[x];
    }
}

void sol1(){
    rep(mask, 0, (1<<n)){
        int ct = 0;
        col = ini;
        rep(i, 0, n){
            if(mask & (1<<i)){
                press(i);
                ct++;
            }
        }

        if(off == col) ans = min(ans, ct);
    }
}

void sol3(){
    int ct = 0;
    rep(i, 1, n){
        if(col[i-1]){
            col[i-1] = 0; col[i] ^= 1;
            if(i<n-1) col[i+1] ^= 1;
            ct++;
        }

        if(i==n-1 && !col[i]) ans = min(ans, ct);
    }

    ct = 0;
    col = ini; col[0] ^= 1; col[1] ^= 1;
    rep(i, 1, n){
        if(col[i-1]){
            col[i-1] = 0; col[i] ^= 1;
            if(i<n-1) col[i+1] ^= 1;
            ct++;
        }
    
        if(i==n-1 && !col[i]) ans = min(ans, ct);
    }
}

vi dfs(int at, int p){ //press and my color after press
    vi ret = {inf, inf, inf, inf};
    vo<vi> kids;

    for(auto x: adj[at]){
        if(x==p) continue;
        vi tmp = dfs(x, at);
        kids.pb(tmp);
    }
    if(kids.size() == 0){
        if(ini[at]) ret = {1, inf, inf, 0};
        else ret = {inf, 1, 0, inf};
    }
    else if(kids.size() == 1){ 
        if(ini[at]){
            ret = {min(inf, kids[0][3]+1), min(inf, kids[0][1]+1), kids[0][0], kids[0][2]};
        }
        else{
            ret = {min(inf, kids[0][1]+1), min(inf, kids[0][3]+1), kids[0][2], kids[0][0]};
        }
    }
    else{
        vi a = kids[0], b = kids[1];
        //press
        for(int i: {1, 3}){
            for(int u: {1, 3}){
                if(a[i]==inf || b[u] == inf) continue;
                int ind = ((ini[at]^1) + (i==1) + (u==1))%2;
                ret[ind] = min(ret[ind], a[i] + b[u] + 1);
                
            }
        }
        //dont press
        for(int i: {0, 2}){
            for(int u: {0, 2}){
                if(a[i]==inf && b[u] == inf) continue;
                int ind = (ini[at] + (i==0) + (u==0))%2 + 2;
                ret[ind] = min(ret[ind], a[i] + b[u]);
            }
        }
    }

    return ret;
}

vi full(int at, int p){
    vi ret = {inf, inf, inf, inf};
    vo<vi> kids;

    for(auto x: adj[at]){
        if(x==p) continue;
        vi tmp = full(x, at);
        kids.pb(tmp);
    }
    if(kids.size() == 0){
        if(ini[at]) ret = {1, inf, inf, 0};
        else ret = {inf, 1, 0, inf};
    }
    else{
        //find cheapest for all children and swap one to get reverse color
        //press so all kids white
        int sum = 1, posi = 1, ind = 0, cheap = inf;
        for(auto v: kids){
            if(v[3] > v[1]) {
                sum += v[1];
                ind++;
                if(v[3]!=inf) cheap = min(cheap, v[3]-v[1]);
            }
            else{
                if(v[3] == v[1] && v[1] == inf) {posi = 0; break;}
                sum += v[3];
                if(v[1] != inf) cheap = min(cheap, v[1]-v[3]);
            }
        }
        if(posi){
            ind = ((ini[at]^1) + ind)%2;
            ret[ind] = sum;
            if(cheap != inf) ret[ind^1] = sum + cheap;
        }

        //dont press
        sum = 0, posi = 1, ind = 0, cheap = inf;
        for(auto v: kids){
            if(v[2] > v[0]) {
                sum += v[0];
                ind++;
                if(v[2] != inf) cheap = min(cheap, v[2]-v[0]);
            }
            else{
                if(v[2] == v[0] && v[0] == inf) {posi = 0; break;}
                sum += v[2];
                if(v[0] != inf) cheap = min(cheap, v[0]-v[2]);
            }
        }
        if(posi){
            ind = (ini[at] + ind)%2;
            ret[ind+2] = sum;
            if(cheap != inf) ret[(ind^1) + 2] = sum + cheap;
        }
    }

    return ret; 
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n; col.resize(n), ini.resize(n), off.assign(n, 0); 
    vi indeg(n, 0);
    int linegraph = 1;
    rep(i, 0, n-1){
        int a, b; cin>>a>>b; a--, --b;
        adj[a].pb(b), adj[b].pb(a); indeg[a]++, indeg[b]++;
        if(abs(a-b) > 1) linegraph = 0;
    }

    rep(i, 0, n) {
        cin>>col[i]; ini[i] = col[i];
    }

    if(n<=20){
        sol1();
    }
    // else if(n<=40) ;//press centroid and then do bitmask on each subtree
    else if(linegraph){
        sol3();
    }
    else if(0){
        //binary tree
        rep(i, 0, n){
            if(indeg[i] == 1){
                vi tmp = dfs(i, i);
                ans = min(tmp[0], tmp[2]);
                break;
            }
        }
    }
    else{
        vi tmp = full(0, 0);
        ans = min(tmp[0], tmp[2]);
    }
    

    (ans==inf) ? cout << "impossible" : cout << ans;
}
