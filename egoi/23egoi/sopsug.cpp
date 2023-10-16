#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define pb push_bach
#define umap unordered_map
#define ar array
typedef long long ll;

#define rep(i, a, b) for(ll i = (a); i<b; i++)
#define pr(a, b) cout << #a << ", " << #b << "=" << a << ", " << b << endl;
int const mxn = 1e6;
int n, m, k, con[mxn][2], imp[mxn][2];

int main(){
    cin >> n >> m >> k;
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        con[i][0]=a, con[i][1]=b;
    }
    rep(i, 0, k){
        int a, b; cin >> a >> b;
        imp[i][0]=a, imp[i][1]=b;
    }
    
    int ans[n][2];
    if(m==0&&k==1){
        if(n==2&&imp[0][1]==0){
            cout << "0 1";
        }
        else{
        rep(i, 1, n){
            if(imp[0][1]==0&&imp[0][0]==i){
                rep(t, 1, n){
                    if(t!=imp[0][0]){
                        ans[i][0]=i;
                        ans[i][1]=t;
                    }
                }
            } 
            else{
                ans[i][0]=i;
                ans[i][1]=0;
            }
        }

        rep(i, 1, n){
            cout << ans[i][0] << " " << ans[i][1] << endl;
        }
        }
    }
    else if(m==0&&k==2){
        if(n==2){
            cout << "NO";
        }
        else{
            rep(t, 0, n){
                if(imp[0][1]!=t&&imp[1][1]!=t){
                    rep(i, 0, n){
                        if(t==i) continue;
                        cout << i << " " << t << endl;
                    }
                    break;
                }
            }
        }
    }
}