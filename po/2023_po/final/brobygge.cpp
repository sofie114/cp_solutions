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
#define repv(item, arr) for (auto item: arr)
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

int const mxn = 1e9+10, mxt=1e5+10;
int n, m, t, par[mxt], rnk[mxt];

int find(int v){
    if(v==par[v]) return v;
    par[v] = find(par[v]);
    return par[v];
}

void uni(int a, int b){
    a = find(a), b = find(b);
    if(a!=b){
        if(rnk[b]>rnk[a]) swap(a, b);
        par[b] = a;
        rnk[a]++;
    }
}

map<ar<int, 2>, int> tbl;

int main(){
    cin >> n >> m >> t;

    par[t]=t, par[t+1]=t+1;
    bool ch = false;
    rep(i, 0, t){ //t is start, t+1 is end
        par[i] = i;
        int a, b; cin >> a >> b;
        tbl[{a, b}] = i;
    
        int dir[4][2] = {{1, 0}, {0, 1}, {-1,0}, {0, -1}};
        repv(x, dir){
            if(x[0]+a==0) uni(t, i);
            if(x[0]+a==n-1) uni(t+1, i);
            if(tbl.count({x[0]+a, x[1]+b})) uni(i, tbl[{x[0]+a, x[1]+b}]);
        }

        a = find(t), b = find(t+1);
        if(a==b){
            cout << i+1; ch = 1;
            break;
        }
    }

    if(!ch) cout << "nej";
}