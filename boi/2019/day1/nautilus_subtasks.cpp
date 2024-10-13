#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define vo vector
#define pb push_back
#define fi first
#define se second 
#define all(x) x.begin(), x.end()
typedef vo<int> vi;
typedef pair<int, int> pii;
 
#define pr(a, b) cout << #a << " " << #b << " " << a << " " << b << endl;
#define rep(i, a, b) for(int i=(a); i<(b); i++)
int const inf = INT_MAX, mxn = 1e5+4, sub = 105;
int r, c, m, tbl[sub][sub], dp[sub][sub][sub], ans;
vo<pii> add;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
 
bool ir(int a, int b){
    return a>=0&&b>=0 && a<r && b<c;
}
 
void walk(int i, int u, int pos){
    if(dp[i][u][pos] != -1) return;
    dp[i][u][pos] = 1;
    if(pos == m) return;
 
    if(add[pos] == pii{inf, inf}){
        for(auto [a, b]: dir){
            int nr = a+i, nc = b+u;
            if(ir(nr, nc)){
                if(tbl[nr][nc])
                    walk(nr, nc, pos+1);
            }
        }
    }
    else{
        int nr = i+add[pos].fi, nc = u+add[pos].se;
        if(ir(nr, nc)){
            if(tbl[nr][nc]){
                walk(nr, nc, pos+1);
            }    
        }
    }
}
 
void sol1(){
    memset(dp, -1, sizeof(dp));
    rep(i, 0, r){
        rep(u, 0, c){
            if(tbl[i][u])
                walk(i, u, 0);
        }
    }
 
    rep(i, 0, r){
        rep(u, 0, c){
            if(dp[i][u][m] == 1) {
                ans++;
            }
        }
    }
 
    cout << ans;
}
 
 
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c>>m;
    rep(i, 0, r){
        rep(u, 0, c){
            char a; cin>>a;
            if(a=='.') tbl[i][u] = 1;
        }
    }
    rep(i, 0, m){
        char a; cin>>a;
        if(a=='W') add.pb({0, -1});
        else if(a=='S') add.pb({1, 0});
        else if(a=='N') add.pb({-1, 0});
        else if(a=='E') add.pb({0, 1});
        else add.pb({inf, inf});
    }
    sol1();
}

/*
subtask 1&2: notice they can be solved together easily. dp[i][u][time point] = 1 if the ship can be can be on row i column u at this time point
--> answer = dp[i][u][m] for all i, u.
in the function walk(i, u, pos) it performs the instruction on position pos from the cell (i, u) and calls the walk function for different i, u, pos
time complexity: m*(r*c) 

full solution: n bitsets of length m representing the grid. for each index in the message, 1 in the bitsets means the ships could be here
and 0 means it cannot. dp[k][i][u] = 1 if the ship can be at (i, u) at time k<=m. use bit shift, bit AND (to remove blocked cells), 
bit OR (when the instruction is ?) to solve. 
time complexity: m*(r*c / 64) 
*/
