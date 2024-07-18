#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vo vector
#define fi first
#define se second 
#define pb push_back
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define pr(x) cout << #x << "=" << x << endl;
int const mxn = 2e5+10, inf = LLONG_MAX;
int n, k, r, arr[mxn];
unordered_map<int, int> need;

bool work(int len){
    vi occ(n, 0);
    unordered_set<int> missing; //index to numbers needed
    for(auto [a, b]: need){
        missing.insert(a);
    }
    rep(i, 0, n){
        occ[arr[i]]++;
        if(need.count(arr[i]) && occ[arr[i]] >= need[arr[i]]) {
            if(missing.count(arr[i])) missing.erase(arr[i]);
        }

        if(i+1 > len){
            //remove
            occ[arr[i-len]]--;
            if(need.count(arr[i-len]) && occ[arr[i-len]] < need[arr[i-len]]) missing.insert(arr[i-len]);
        }

        if(missing.size()==0) return 1;
    }
    return 0;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k>>r;
    rep(i, 0, n){
        cin>>arr[i];
    }
    rep(i, 0, r) {
        int a, b;
        cin>>a>>b; need[a] = b;
    }

    int lo = 0, hi = n+1;
    while(hi>lo+1){
        int mid = (hi+lo)/2;
        if(work(mid)) hi = mid;
        else lo = mid;
    }

    if(hi==n+1) cout << "impossible";
    else cout << hi;
}
