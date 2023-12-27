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
// ett set för varje rad och kolumn sparar vilka som är obesökta
int const mxn = 1e6;
int r, c, k, g1, g2;
vo<vi> tbl;
vo<set<int>> row, col, wrow, wcol;

bool ir(int a, int b){
    return a>=0&&b>=0&&a<r&&b<c; //maybe add not #
}

bool valid(set<int>::iterator it, set<int>& s){
    return it!=s.end();
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>r>>c>>k;
    tbl.resize(r, vi(c)); row.resize(r), col.resize(c), wcol.resize(c), wrow.resize(r);

    queue<ar<int, 2>> qu;
    vo<vll> dist(r, vll(c, -1)); 

    rep(i, 0, r){
        rep(u, 0, c){
            char c; cin>>c;
            if(c=='.') {
                tbl[i][u]=1;
                row[i].insert(u); 
                col[u].insert(i);
            }
            else if(c=='#') {
                wrow[i].insert(u);
                wcol[u].insert(i);
            }
            else if(c=='S'){
                qu.push({int(i), int(u)});
                dist[i][u]=0;
            }
            else{
                row[i].insert(u);
                col[u].insert(i);
                g1=i, g2=u;
            }
        }
    }


    while(qu.size()){
        ar<int, 2> v = qu.front(); qu.pop();

        // pr(v[0], v[1])
        //horisontell
        int lef=v[1] - k, rig=v[1] + k+1;

        auto it = wrow[v[0]].upper_bound(v[1]);
        if(valid(it, wrow[v[0]])) rig = min(rig, *it); 
        if(it!=wrow[v[0]].begin()) {it--; lef = max(lef, *it);}

        while(1){
            auto it = row[v[0]].lower_bound(lef);
            if(it!=row[v[0]].end() && *it < rig){
                int nr = v[0], nc = *it;
                dist[nr][nc] = dist[v[0]][v[1]] + 1;
                qu.push({nr, nc});

                row[v[0]].erase(it);
                col[*it].erase(v[0]);
            }
            else break;
        }

        //vertikal
        int up = v[0]-k, down = v[0]+k+1;
        auto it1 = wcol[v[1]].upper_bound(v[0]);
        if(valid(it1, wcol[v[1]])) down = min(down, *it1);
        if(it1!=wcol[v[1]].begin()) {it1--; up = max(up, *it1);}

        while(1){
            auto it = col[v[1]].lower_bound(up);
            if(it!=col[v[1]].end() && *it < down){
                int nr = *it, nc = v[1];
                dist[nr][nc] = dist[v[0]][v[1]] + 1;
                qu.push({nr, nc});

                col[v[1]].erase(it);
                row[*it].erase(v[1]);
            }
            else break;
        }
    }

    cout << dist[g1][g2] << endl;

}
