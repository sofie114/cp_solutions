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
ll const inf = LLONG_MAX, mxn = 1e3+4;
int r, c, er, ec, tbl[mxn][mxn];
vo<vo<vi>> dist(mxn, vo<vi>(mxn, vi(4, inf)));
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} ;

bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>c>>r;
    priority_queue<array<int, 4>, vo<array<int, 4>>, greater<array<int, 4>>> pq;

    rep(i, 0, r){
        rep(u, 0, c){
            char C; cin>>C;
            if(C=='.') tbl[i][u] = 1;
            else if(C=='M'){
                er = i, ec = u;
                tbl[i][u] = 1;
                pq.push({0, 0, i, u}); 
                rep(w, 0, 4)
                    dist[i][u][w] = 0;
            }
            else if(C=='_'){
                tbl[i][u] = 2;
            }
        }
    }

    //dist, which pair, i, u
    while(sz(pq)){
        array<int, 4> v = pq.top(); pq.pop();
        // pr(v)
        int row = v[2], col = v[3], whichpair = v[1];


        if(tbl[row][col] == 1){
            //go in all four directions
            int i = 0;
            for(auto x: dir){
                int nr = x[0]+row, nc = x[1]+col, newd = v[0]+1;;

                if(ir(nr, nc) && tbl[nr][nc] && dist[nr][nc][i] > newd){
                    dist[nr][nc][i] = newd;
                    pq.push({newd, i, nr, nc});
                }
                i++;
            }
        }
        else{
            int nr = dir[whichpair][0]+row, nc = dir[whichpair][1]+col, newd = v[0];
            if(ir(nr, nc) && tbl[nr][nc] && dist[nr][nc][whichpair] > newd){
                dist[nr][nc][whichpair] = newd;
                pq.push({newd, whichpair, nr, nc});
            }

            int i = 0;
            for(auto x: dir){
                int nr = x[0]+row, nc = x[1]+col, newd = v[0]+1; 
                if(ir(nr, nc) && tbl[nr][nc] && newd < dist[nr][nc][i]){
                    int rnr = x[0]*-1+row, rnc = x[1]*-1+col;
                    if(ir(rnr, rnc) && !tbl[rnr][rnc]){
                        dist[nr][nc][i] = newd;
                        pq.push({newd, i, nr, nc});
                    }
                }
                i++;
            }
            //only go in the direction it came from
        }
    }

    rep(i, 0, r){
        rep(u, 0, c){
            int mini = inf;

            rep(w, 0, 4){
                mini = min(mini, dist[i][u][w]);
            }
            if(mini == inf) cout << -1 << " ";
            else cout << mini << " ";
        }
        cout << "\n";
    }
}


