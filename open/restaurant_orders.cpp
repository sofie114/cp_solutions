#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define uset unordered_set
#define int long long
#define vo vector
#define fi first
#define pb push_back
#define se second
#define all(x) x.begin(), x.end()
#define pr(x) cerr << #x << " " << x << endl;
#define sz(x) x.size()
typedef vo<int> vi;
typedef pair<int, int> pii; 

#define rep(i, a, b) for(ll i = (a); i<(b); i++)

// cool dp
int const mxn = 3e4+4;
int n, dp[mxn], m, pre[mxn];

signed main(){
    cin>>n;
    vi cost(n);
    rep(i, 0, n){
        cin>>cost[i];
    }

    dp[0] = 1;
    rep(i, 0, n){
        rep(u, 0, mxn){
            if(cost[i] <= u){
                dp[u] += dp[u - cost[i]];
                if(dp[u - cost[i]]) pre[u] = i;
            }
        }
    }

    cin>>m;
    rep(i, 0, m){
        int q; cin>>q;
        if(dp[q] == 0) cout << "Impossible" << "\n";
        else if(dp[q]==1){
            //reconstruct
            multiset<int> ans;
            while(q != 0){
                ans.insert(pre[q]);
                q -= cost[pre[q]];
            }
            for(auto x: ans) cout << x+1 << " ";
            cout << "\n";
        }
        else cout << "Ambiguous" << "\n";
    }
}
