#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define ar array
#define umap unordered_map
#define pb push_back
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;

int const mxn = 1e6;

int main(){
    ll len, t, m, n;
    cin >> len >> t >> m >> n;
    vo<vo<ll>> trains(t); vo<ll> copy;
    ll inp;
    rep(i, 0, t) {cin >> inp; trains[i].pb(inp);}
    rep(i, 0, t) {cin >> inp; trains[i].pb(inp);}

    rep(i, 0, t) copy.pb(trains[i][0]);  


    ll zur[m], lug[n];
    rep(i, 0, m) cin >> zur[i];
    rep(i, 0, n) cin >> lug[i];

    bool ans = 0;
    rep(i, 0, m){
        rep(j, 0, n){
            double meet;
            if(abs(zur[i]-lug[j])>=len) continue;
            if(zur[i]>=lug[j]) meet = (double((len)-(zur[i]-lug[j])))/2;  
            else meet = double(lug[j]-zur[i])+(double((len)-(lug[j]-zur[i])))/2;

            // pr(i, j); 
            vo<ll>::iterator upper1 = upper_bound(copy.begin(), copy.end(), meet);
            ll u1 = upper1-copy.begin();
            if(u1<=0) continue;
            u1--;
            // pr(meet, u1); pr(copy[u1], trains[u1][1]);
            if(copy[u1]<meet&&trains[u1][1]>meet){
                ans = 1;
                break;
            }
        }
        if(ans) break;
    }
    if(ans) cout << "YES";
    else cout << "NO";
}