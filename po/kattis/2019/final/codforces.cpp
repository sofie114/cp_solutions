#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr2(x) cerr << #x << "=" << x << endl
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
//go for outline with ;, then details
//di}

int const mxn = 1e6+10;
ll n, k, a[mxn], nex[mxn], ans = 1e18;
vo<int> findnext[mxn];


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    rep(i, 0, n) cin >> a[i];

    rep(_, 0, 2){
        repd(i, 0, n){
            if(findnext[a[i]+1].size()){
                nex[i] = findnext[a[i]+1].back();
            }
            findnext[a[i]].pb(i);
        }
    }

    // rep(i, 0, n) cout << nex[i] << " ";

    rep(i, 0, n){
        if(a[i]==1){
            ll curr = i, ct=1;
            while(1){
                if(a[curr]==k)break;
                ll dis = nex[curr]-curr; if(dis<0) dis+=n;
                ct += dis;
                curr = nex[curr];
            }
            ans = min(ans, ct);
        }
    }

    cout << ans;

}
