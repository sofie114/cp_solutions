#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr1(x) {cerr << x << " ";} cerr << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
#define pr(...) {cerr << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cerr << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cerr << arg << ", ";
    print_vars(args...);
}

// #define pr2d(r, c, arr) 
// rep(wi, 0, r){
//     rep(wii, 0, u){
//         cout << arr[wi][wii] << " ";
//     }
//     cout << endl;
// }



int const mxn = 510, mxu = 1e6;
int r, c, vis[mxn][mxn], q, sr, sc;
string tbl[mxn];
vo<vo<ll>> dist(mxn, vo<ll>(mxn, -1)); 
ll rnk[mxu], par[mxu], union_size[mxu];


ll find(int v){
    if(par[v]==v) return v;
    return par[v] = find(par[v]);
}

void uni(int a, int b){
    a = find(a), b = find(b);
    if(a!=b){
        if(rnk[a]<rnk[b]) swap(a, b);
        par[b] = a;
        rnk[a]++;

        union_size[a] += union_size[b]; 
        union_size[b] = 0;
        
    }
}


bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c&&tbl[a][b] == '#'; //maybe add not #
}

void bfs(int a, int b){
    dist[a][b] = 1; 
    queue<ar<ll, 2>> q; q.push({a, b});

    while(q.size()){
        ar<ll, 2> v = q.front(); q.pop();

        int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(auto x: dir){
            ll nr = v[0]+x[0], nc = v[1]+x[1];
            if(ir(nr, nc)){
                uni(v[0]*c + v[1], nr*c + nc);

                if(dist[nr][nc] == -1){
                    dist[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }
}

int main(){
    cin >> r >> c >> q;
    rep(i, 0, r){
        cin >> tbl[i];
        rep(u, 0, c){
            par[i*c+u] = i*c+u;  //omg index compression
            union_size[i*c+u] = 1;


            if(tbl[i][u] == 'S'){
                sr = i, sc = u;
                tbl[i][u] = '#';
            }
        }
    }
    bfs(sr, sc);

    
    cout << union_size[find(sr*c+sc)] << endl;
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--, b--;
        tbl[a][b] = '#';
        bfs(a, b);

        // rep(wi, 0, r){
        //     rep(wii, 0, c){
        //         cout << par[wi*c+wii] << " ";
        //     }
        //     cout << endl;
        // }   

        // pr(union_size[find(sr*c+sc)])
        cout << union_size[find(sr*c+sc)] << endl;
    }


}   
