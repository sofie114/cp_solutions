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
typedef pair<ll, ll> pii;

#define rep(i, a, b) for(ll i=(a); i<(b); i++)
#define repd(i, a, b) for(ll i=(b-1); i>=(a); i--)
ll const inf = LLONG_MAX, mxn = 1e5+4;
int n, bin, ans[mxn];
vi columnInt(mxn, 0);

int main(){
    cin>>n;

    rep(u, 0, 20){
        cout << "? ";
        rep(i, 0, n){
            if(((1<<u) & i)){
                cout << '1';
            }
            else cout << '0';

        }
        cout << endl;

        string tmp;
        cin>>tmp; 
        rep(i, 0, n){
            if(tmp[i] == '1')
                columnInt[i] |= (1<<u);
        }
    }

    rep(i, 0, n){
        ans[columnInt[i]] = i;
    }
    cout << "! ";
    rep(i, 0, n) cout << ans[i] << " ";
}
