#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define vo vector
#define fi first 
#define se second
#define pr(x) cerr << #x << " " << x << endl;

typedef long long ll;
typedef vo<int> vi;
typedef vo<ll> vll;

#define rep(i, a, b) for(ll i=(a); i<(b); i++)

ll const inf = LLONG_MAX, mxn = 2e5+10;
int n, ans;

signed main(){
    cin>>n;
    vi p(n), r(n), pref(n);
    vo<set<int>> bits(30);

    rep(i, 0, n) cin>>p[i];
    rep(i, 0, n) { 
        cin>>r[i];
        pref[i] = r[i];
        if(i>0) pref[i] += pref[i-1];
    }

    rep(i, 0, n){
        rep(u, 0, 30){
            if(p[i] & (1<<u)){
                bits[u].insert(i);
            }
        }
    }

    rep(i, 0, n){
        set<int> rig;
        rep(u, 0, 30){
            auto it = bits[u].lower_bound(i);
            if(it!=bits[u].end()){
                rig.insert(*it);
            }
        }

        int curr = p[i];
        for(auto x: rig){

            curr |= p[x];
            int tmp = 0; 
            if(i>0) tmp = pref[i-1];
            ans = max(ans, curr - (pref[x] - tmp));
        }
    }

    cout << ans;
}
