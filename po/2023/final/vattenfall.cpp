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
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto& item: arr)
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

int const mxn = 1e5+10;
int r, c, k, n, in[mxn];
umap<int, vo<int>> klp;
map<ar<int, 2>, int> vis;
set<int> out;

int find(int r, int c){
    if(!klp.count(c)) {out.insert(c); return 0;}
    auto upper = upper_bound(all(klp[c]), r); //cannot be standing on a cliff
    if(upper==klp[c].begin()) {out.insert(c); return 0;}
    upper--;
    if(vis[{*upper, c}]) return 0;
    vis[{*upper, c}] = 1;
    return (*upper)+1;
}

int main(){
    cin >> r >> c >> k >> n;
    rep(i, 0, k) cin >> in[i];
    rep(i, 0, n){
        int a, b; cin >> a >> b;
        vis[{a, b}] = 0;
        klp[b].pb(a); //might be bad
    }

    repv(x, klp){
        sort(all(x.second));
    }

    queue<ar<int, 2>> q; 
    rep(i, 0, k){
        q.push({r, in[i]});
        while(len(q)){
            ar<int,2> cu = q.front(); q.pop();
            int nr = find(cu[0], cu[1]);
            if(nr==0) continue;

            if(cu[1]+1<c && !vis.count({nr, cu[1]+1})) q.push({nr, cu[1]+1}); 
            if(cu[1]-1>=0 && !vis.count({nr, cu[1]-1})) q.push({nr, cu[1]-1});
        }
    }
    cout << len(out);
}


