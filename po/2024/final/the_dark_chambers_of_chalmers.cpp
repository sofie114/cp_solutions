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
int const mxn = 40;
int d, pre, dep;
string s;
vi bottnodes;
uset<int> isbottnode; //nodeind to bottom row index, 
umap<int, int> fl; //nodeind to floor
vo<vi> lists;
vo<vi> adj(mxn); //node

void godownright(){ cout << "downright" << endl; cin>>s; }
void godownleft(){ cout << "downleft" << endl; cin>>s; }
void app(){ cout << "app" << endl;cin>>d; }
void goup(){ cout << "up" << endl; cin>>s; }
void goleft(){ cout << "left" << endl; cin>>s; }
void goright(){ cout << "right" << endl; cin>>s; }

void downone(){
    int tmp;
    if(s[2]=='1') {
        godownright();
        app();
        if(d==1){
            cout << "left" << endl;
            cin>>s;
        }
    }
    else godownleft();
}

void exploretop(int v, int F){
    if(v>6) bottnodes.pb(v);
    fl[v] = F;

    if(s[1]=='1') adj[v].pb(v+1), adj[v+1].pb(v);
    if(s[3]=='1'){
        adj[v].pb(v*2+1), adj[v*2+1].pb(v);

        if(v < 7){
            godownleft();
            exploretop(v*2+1, F+1);
            goup();
        }
    }
    if(s[2]=='1'){
        adj[v].pb(v*2+2), adj[v*2+2].pb(v);

        if(v < 7){
            godownright();
            exploretop(v*2+2, F+1);
            goup();
        }
    }
}

vi bfs(int start){
    queue<int> qu; qu.push(start); //node + floor
    vo<pii> dist(mxn, {100, 0}); //stairs + sum
    dist[start] = {0, 0};
    while(qu.size()){
        int v = qu.front(); qu.pop();

        for(auto x: adj[v]){
            int stairs = dist[v].first;
            if(fl[x] != fl[v]) stairs++;

            if(stairs < dist[x].first){
                dist[x].first = stairs;
                dist[x].second = dist[v].second + 1;
                qu.push(x);
            }
        }
    }   
    vi ret;
    rep(i, 7, 15){
        if(isbottnode.count(i)) { ret.pb(dist[i].second); }
    }
    return ret;
}

void walkto(int l){
    if(l<11){
        godownleft();
        if(l<9){
            godownleft();
            if(l<8) { godownleft(); }
            else {godownright(); }
        }
        else{
            godownright();
            if(l<10) {godownleft(); }
            else { godownright(); }
        }
    }
    else {
        godownright();
        
        if(l<13){
            godownleft();
            if(l<12){ godownleft(); }
            else {godownright(); }
        }
        else{
            godownright();
            if(l<14) godownleft();
            else godownright();
        }
    }

}

bool solve(){
    for(auto x: bottnodes){
        vi list = bfs(x);
        lists.pb(list);
        // pr(list)
    }

    umap<int, int> diff; //difference between two pos -> what node is correct
    int tmp = 0, l, r;

    rep(i, 0, sz(bottnodes)){
        rep(u, i+1, sz(bottnodes)){
            diff.clear();

            rep(lisind, 0, sz(bottnodes)){
                if(diff.count(lists[lisind][i] - lists[lisind][u])){
                    break;
                }
                else diff[lists[lisind][i] - lists[lisind][u]] = lisind;

                if(lisind == sz(bottnodes)-1) { tmp = 1;}
            }

            if(tmp) { l = i, r = u; break; }
        }
        if(tmp) break;
    }

    // pr(l, r, bottnodes[l], bottnodes[r], diff);
    int a, b;
    walkto(bottnodes[l]); app(); a = d; rep(i, 0, 3) goup();
    walkto(bottnodes[r]); app(); b = d; rep(i, 0, 3) goup(); 
    int dbott = a - b;
    if(!diff.count(dbott)) return 0; 

    dep = a - lists[diff[dbott]][l], pre = dep;  //think right

    if(dep > 10){
        int correctnode = bottnodes[diff[dbott]];
        walkto(correctnode);
        return 1;
    }
    return 0;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>s;
    while(s[0]=='1') goup();

    exploretop(0, 0);
    for(auto x: bottnodes) isbottnode.insert(x);
    // pr(bottnodes);
    // pr(adj);

    if(sz(bottnodes) > 1){ 
        bool tmp = solve(); 
        if(!tmp){
            app(); dep = d, pre = d;
        }
    
    }
    else if(sz(bottnodes) == 1) { walkto(bottnodes[0]); app(); dep = d, pre = d;}
    else{
        app(); dep = d, pre = d;
    }

    rep(i, 0, dep/2){ 
        vi exist = {0, 0, 0, 0};

        if(s[3]=='1'){
            godownleft();
            if(s[3]=='1') exist[0]=1;
            if(s[2]=='1') exist[1]=1;

            if(s[1]=='1'){
                goright();
                if(s[3]=='1') exist[2]=1;
                if(s[2]=='1') exist[3]=1;
            }
        }
        else{
            godownright();
            if(s[3]=='1') exist[2]=1;
            if(s[2]=='1') exist[3]=1;
        }
        int ct = 0;
        rep(i, 0, 4) ct += exist[i];
        pr(ct, exist);

        if(ct==2 || ct == 1){
            bool queried = 0;
            rep(u, 0, 4){
                pr(s, u, (u%2))
                if(s[2]=='1' && (u%2)==0){
                    godownright();
                    if(!queried){
                        app(); queried = 1;
                        if(d!=pre-2){
                            goup(); 
                        }
                        else break;
                    }
                    else break;
                }
                if(s[3]=='1' && (u%2)==1){
                    godownleft();
                    if(!queried){
                        app(); queried = 1;
                        if(d!=pre-2){
                            goup(); 
                        }
                        else break;
                    }
                    else break;
                }
                if(s[4]=='1' && u==1) goleft();
            }
        }
        else if(ct==3 && exist[0]==1){
            if(exist == vi({1, 1, 1, 0})){
                godownleft(); app();
                if(d==pre-1) goleft();
                else if(d==pre) {goleft(); goleft();}
            }
            else if(exist == vi({1, 0, 1, 1})){
                godownright(); app();
                if(d==pre-1) goleft();
                else if(d==pre+1){goup(); goleft(); godownleft();}
            }
            else if(exist == vi({1, 1, 0, 1})){
                goleft(); godownleft(); app();
                if(d==pre-1) goright();
                else if(d==pre+1){goup(); goright(); godownright();}
            }
        }
        else{
            godownright(); app();
            if(d==pre-1) goleft();
            else if(d==pre) {goleft(); goleft();}
            else if(d==pre+1) {rep(i, 0, 3) goleft();}
        }

        pre-=2;
    }

    if(dep%2) downone();
    cout << "here";
}
