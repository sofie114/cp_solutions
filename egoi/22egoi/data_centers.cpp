#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define ar array
#define umap unordered_map
#define pb push_back
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;
int n, s;

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> s;
    vo<ll> data;
    rep(i, 0, n){
        int x;
        cin >> x;
        data.pb(x);
    }

    sort(data.begin(), data.end(), greater<ll>());
    vo<ll> tmp(n);
    rep(i, 0, s){
        if(i%2==0){
            int m, c;
            cin >> m >> c;
            ll p1 = c, p2 = 0;
            rep(k, 0, n){
                if((p1<n&&data[p1]>data[p2]-m)||p2>=c) {tmp[k]=data[p1]; p1++;}
                else {tmp[k] = data[p2]-m; p2++;}
            }
        }
        else{
            int m, c;
            cin >> m >> c;
            ll p1 = c, p2 = 0;
            rep(k, 0, n){
                if((p1<n&&tmp[p1]>tmp[p2]-m)||p2>=c) {data[k]=tmp[p1]; p1++;}
                else {data[k] = tmp[p2]-m; p2++;}
            }
        }
    }
    if(s%2==1) rep(i, 0, n) cout << tmp[i] << " ";    
    else rep(i, 0, n) cout << data[i] << " "; 
}

//IDEA, using merge sort because both vectors are sorted and there is no need to sort them together in nlogn instead of just merging in n
