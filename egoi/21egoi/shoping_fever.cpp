#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define pb push_back
#define umap unordered_map
#define ar array
typedef long long ll;


#define rep(i, a, b) for(ll i = (a); i<b; i++)
#define pr(a, b) cout << #a << ", " << #b << "=" << a << ", " << b << endl
ll const mxn = 500010;

int main(){
    int n, q;
    cin >> n >> q;
    ll arr[n], ans=0;
    rep(i, 0, n){
        cin >> arr[i];
        ans+=arr[i];
    }
    sort(arr, arr+n);
    reverse(arr, arr+n);
    vo<ll> dp(n+1, 0);
    dp[1] = arr[0]*q/100, dp[2]=dp[1]+arr[1]*q/100;
    rep(i, 3, n+1){
        dp[i] = max(dp[i-1]+arr[i-1]*q/100, arr[i-1]+dp[i-3]);
    }
    ans-=dp[n];
    cout << ans;
}

// 300 300 200 200 200 