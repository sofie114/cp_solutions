#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()i
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
#define print(...) {cout << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cout << arg << ", ";
    print_vars(args...);
}
//idea: find distance from each square to nearest wall with multisource bfs from all walls. 
// then start a dijkstra from the persons square and add the neighbouring squares and square beside walls they can see in the four directions to the priority queue
// these added square will have weight 1 for neighbours and weight disttowallfromcurrsquare for squares beside walls in the four directions
// solution:)


int const mxn = 1e3+10;
int r, c, tbl[mxn][mxn], start[2], cake[2];
string s;
vo<ar<ll, 2>> walls;
vo<vo<int>> dwall(mxn, vo<int>(mxn, 1e9));
vo<vo<int>> ans(mxn, vo<int>(mxn, 1e9));
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool ir(int a, int b){
    return a>=0&&b>=0&&a<r+2&&b<c+2&&tbl[a][b];
}

void bfswall(){
    queue<ar<ll, 2>> q; 
    for(auto x: walls){
        q.push({x[0], x[1]});
        dwall[x[0]][x[1]]=0;
    }

    while(len(q)){
        ar<ll, 2> v = q.front(); q.pop();

        for(auto x: dir){
            int nr=x[0]+v[0], nc=x[1]+v[1];
            
            if(ir(nr, nc) && dwall[nr][nc] > dwall[v[0]][v[1]] + 1){
                dwall[nr][nc] = dwall[v[0]][v[1]] + 1;
                q.push({nr, nc});
            }
        }
    }

}

int main(){
    cin >> r >> c;
    rep(i, 0, r+2){
        if(i!=0 && i!=r+1) {
            cin >> s;
        }   

        rep(u, 0, c+2){
            if(i==0||i==r+1||u==0 || u==c+1) {
                tbl[i][u] = 0;
                walls.pb({i, u});
            }
            else{
                if(s[u-1]=='#') {
                    tbl[i][u]=0;
                    walls.pb({i, u});
                }
                else tbl[i][u] = 1;

                if(s[u-1]=='S') start[0]=i, start[1]=u;
                if(s[u-1]=='C') cake[0]=i, cake[1]=u;
            }
        }
    }

    //nearest distance to wall
    bfswall();

    //wall you see from each square
    ar<ar<vo<ar<ll, 2>>, mxn>, mxn> sight;

    //rows
    rep(i, 0, r+2){
        int tmpwall = 0;

        rep(u, 0, c+2){
            if(!tbl[i][u]) {
                tmpwall=u+1;
            }
            else{
                if(tmpwall!=u) sight[i][u].pb({i, tmpwall});
            }
        }

        tmpwall = r+1;

        repd(u, 0, c+2){
            if(!tbl[i][u]){
                tmpwall = u-1;
            }
            else{
                if(tmpwall!=u) sight[i][u].pb({i, tmpwall});
            }
        }
    }

    //columns
    rep(u, 0, c+2){
        int tmpwall = 0;

        rep(i, 0, r+2){
            if(!tbl[i][u]) {
                tmpwall=i+1;
            }
            else{
                if(tmpwall!=i) sight[i][u].pb({tmpwall, u});
            }
        }

        tmpwall = c+1;
        repd(i, 0, r+2){
            if(!tbl[i][u]){
                tmpwall = i-1;
            }
            else{
                if(tmpwall!=i) sight[i][u].pb({tmpwall, u});
            }
        }
    }


    //dijkstra from starting pos with edges to neighbours and edges to squares by walls you see
    priority_queue<ar<ll, 3>, vo<ar<ll, 3>>, greater<ar<ll, 3>>> pq;
    ans[start[0]][start[1]] = 0;
    pq.push({0, start[0], start[1]});

    while(len(pq)){
        ar<ll, 3> v = pq.top(); pq.pop();
        int a = v[1], b=v[2];

        for(auto x: dir){
            int nr=x[0]+v[1], nc=x[1]+v[2];
            
            if(ir(nr, nc) && ans[nr][nc] > ans[a][b] + 1){
                ans[nr][nc] = ans[a][b] + 1;
                pq.push({ans[a][b] + 1, nr, nc});
            }
        }
        for(auto x: sight[a][b]){
            if(ans[x[0]][x[1]] > ans[a][b] + dwall[a][b]){

                ans[x[0]][x[1]] = ans[a][b] + dwall[a][b];
                pq.push({ans[a][b] + dwall[a][b], x[0], x[1]});
            }
        }
    }

    //print the answer grid

    // rep(i, 0, r+2){
    //     rep(u, 0, c+2){
    //         cout << ans[i][u]%int(1e9) << " ";
    //     }
    //     cout << endl;
    // }

    cout << ans[cake[0]][cake[1]];

}





