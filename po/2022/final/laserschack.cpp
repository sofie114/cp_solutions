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
int const mxn = 40005;
int r, c, ra, ca, rk, ck;
ll inf = INT_MAX;
vo<vi> tbl, tid;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c; //maybe add not #
}
bool nobomb(int a, int b, int sec){
    return tid[a][b]>sec;
}

bool bfs(int sec){
    if(sec >= tid[ra][ca]) return 0;

    vo<vo<vi>> dist(r, vo<vi>(c, vi(2, inf)));
    dist[ra][ca][0] = 0, dist[ra][ca][1]=0;
    queue<ar<int, 4>> qu; 
    for(auto x: dir) qu.push({ra, ca, x[0], x[1]}); 

    while(qu.size()){
        ar<int, 4> v = qu.front(); qu.pop();
        if(v[0]==rk && v[1]==ck) return true;

        if(tbl[v[0]][v[1]]){
            for(auto x: dir){
                int nr = v[0]+x[0], nc = v[1]+x[1], tmp=0;
                if(x[1]) tmp = 1;

                if(ir(nr, nc) && nobomb(nr, nc, sec) && dist[nr][nc][tmp]==inf){
                    dist[nr][nc][tmp] = dist[v[0]][v[1]][tmp]+1;
                    if(tbl[nr][nc]) {
                        tmp ^= 1;
                        dist[nr][nc][tmp] = dist[v[0]][v[1]][tmp]+1;
                    }
                    qu.push({nr, nc, x[0], x[1]});
                }
            }
        }
        else{
            int nr = v[0]+v[2], nc=v[1]+v[3], tmp=0;
            if(v[3]) tmp=1;
            
            if(ir(nr, nc) && nobomb(nr, nc, sec) && dist[nr][nc][tmp]==inf) {
                dist[nr][nc][tmp] = dist[v[0]][v[1]][tmp]+1;
                if(tbl[nr][nc]) {
                    tmp ^= 1;
                    dist[nr][nc][tmp] = dist[v[0]][v[1]][tmp]+1;
                }
                qu.push({nr, nc, v[2], v[3]});
            }
        }


    }
    return 0;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c;
    tbl.assign(r, vi(c, 0));
    tid.assign(r, vi(c, inf));

    queue<ar<int, 2>> qu; 

    rep(i, 0, r){
        rep(u, 0, c){
            char a; cin>>a;
            if(a=='A') ra=i, ca=u;
            else if(a=='K') rk = i, ck = u;
            else if(a=='o') tbl[i][u] = 1;
            else if(a=='R') {
                qu.push({int(i), int(u)});
                tid[i][u] = 0;
            }
        }
    }

    while(qu.size()){
        ar<int, 2> v = qu.front(); qu.pop();

        for(auto x: dir){
            int nr = v[0]+x[0], nc = v[1]+x[1];
            if(ir(nr, nc) && tid[nr][nc]==inf){
                tid[nr][nc] = tid[v[0]][v[1]]+1;
                qu.push({nr, nc});
            }
        }
    }
    // pr(tid)
    int lo = 0, hi = 40001;
    while(hi-lo>1){
        int mid = (hi+lo)/2;
        if(bfs(mid)) lo = mid;
        else hi = mid;
    }

    cout << hi;
}
