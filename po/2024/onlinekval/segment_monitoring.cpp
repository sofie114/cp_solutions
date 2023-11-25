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
int const mxn = 2*1e5+10;
ll mini, maxi, q;
umap<ll, ar<ll, 2>> cameras;
set<ar<ll, 2>, greater<ar<ll, 2>>> lo; //hi ind, camera ind
set<ar<ll, 2>> hi; //lo ind, camera ind

int main(){
    cin >> mini >> maxi >> q;
    rep(i,0,q){
        char type; cin >> type;
        if(type=='+'){
            ll s, a, b; cin >> s >> a >> b;
            cameras[s] = {a, b};
            if(a<=mini) lo.insert({b, s});
            if(b>=maxi) hi.insert({a, s});
        }
        else{
            int s; cin >> s;
            if(cameras[s][0] <= mini){
                auto it = lo.find({cameras[s][1], s});
                lo.erase(it);
            }
            if(cameras[s][1]>=maxi){
                auto it2 = hi.find({cameras[s][0], s});
                hi.erase(it2);
            }
            cameras.erase(s);
        }

        ll left, right;
        if(len(lo) == 0 || len(hi)==0){
            cout << -1 << endl; continue;
        }
        auto it = lo.begin();
        right = (*it)[0];
        if(right >= maxi) cout << 1 << endl;
        else{
            auto it2 = hi.begin();
            left = (*it2)[0];
            if(left<=right) cout << 2 << endl;
            else cout << -1 << endl;
        }

    }
}

