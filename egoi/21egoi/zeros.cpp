#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vo vector
#define umap unordered_map
#define pb push_back

#define rep(i, a, b) for(ll i = (a); i<b; i++)
#define pr(a, b) cout << #a << ", " << #b << "=" << a << ", " << b << endl;

ll solve(ll v, ll a, ll b){
    ll curr = 1, ct=0;
    while(1){
        if(curr*v>b) break;
        curr*=v, ct++;
    }
    while(curr>1){
        if(ll(b/curr)*curr>=a) return ct;
        curr/=v, ct--;
    }
    return 0;
}

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    ll a, b;
    cin >> a >> b;
    ll min_v = min(solve(5, a, b), solve(2, a, b));
    cout << min_v;

}

//to find the amount of zeros in the end, find minimum of v for 2 and v for 5. v is a number 2^x or 5^x where a number y satisfies: a<= v*y <= b
//to find this, basically just used loops and some math logic, solution idea on egoi 2021 website
