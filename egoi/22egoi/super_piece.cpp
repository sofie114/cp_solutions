#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define ar array
#define umap unordered_map
#define pb push_back
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;
int q;

int main(){
    cin >> q;
    rep(_, 0, q){
        string pieces;
        cin >> pieces;
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        ll min_val = LLONG_MAX;
        ll d1 = c-a, d2 = d-b;
        rep(i, 0, pieces.size()){
            if(pieces[i]=='Q'){
                if(d1==0||d2==0||abs(d1)==abs(d2)) min_val = 1;
                else min_val = min(ll(2), min_val);
                // if(pieces.find('N')==pieces.npos) break;
            }
            else if(pieces[i]=='R'){
                if(d1==0||d2==0) min_val=1;
                else min_val= min(min_val, ll(2));
            }
            else if(pieces[i]=='B'){
                if(abs(d1)==abs(d2)) min_val=1;
                else if((d1+d2)%2==0) min_val=min(min_val, ll(2));
                //if knight in too
            }
            else if(pieces[i]=='N'){
                // if(abs(max(d1, d2)/min(d1, d2))==2) min_val=min(min_val, min(d1, d2));
                min_val = min(abs(abs(d2)-abs(d1)), min_val);
            }
            else if(pieces[i]=='K'){
                if(abs(d1)<=1&&abs(d2)<=1) min_val = 1;
                else min_val = min(min_val, max(abs(d1), abs(d2))); 
            }
            else if(pieces[i]=='P'){
                if(d2==0&&d1>0) min_val=min(min_val, d1);
            }
        } 
        if(min_val == LLONG_MAX) cout << -1 << endl;
        else cout << min_val << endl;
    }
}