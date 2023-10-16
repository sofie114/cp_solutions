#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vo vector
#define umap unordered_map
#define pb push_back

#define rep(i, a, b) for(ll i = (a); i<b; i++)
#define pr(a, b) cout << #a << ", " << #b << "=" << a << ", " << b << endl;
int const mxn = 1e6;
ll n, seg[4*mxn], arr[2*mxn];
ll open[2*mxn][2]; //what couples are founded so far, tried to use umap but got RTE

ll query(ll node, ll lo, ll hi, ll ml, ll mh){
    if(lo>=ml && hi<=mh) return seg[node];
    if(lo>mh || hi<ml) return 0;
    ll mid = (hi+lo)/2;
    ll left = query(2*node+1, lo, mid, ml, mh);
    ll right = query(2*node+2, mid+1, hi, ml, mh);
    return left+right;
}

void update(ll node, ll lo, ll hi, ll pos, ll new_val){
    if(lo==hi){
        seg[node] = new_val;
        return;
    }
    ll mid = (hi+lo)/2;
    if(pos <= mid) update(2*node+1, lo, mid, pos, new_val);
    else update(2*node+2, mid+1, hi, pos, new_val);
    seg[node] = seg[2*node+1]+seg[2*node+2];
}

int main(){
    cin >> n;
    ll ct = 0;
    rep(i, 0, 2*n){
        cin >> arr[i];
        arr[i]--;
        if(open[arr[i]][0]==0){
            open[arr[i]][0] = 1, open[arr[i]][1] = i;
            update(0, 0, 2*n-1, i, 1);
        }else{
            update(0, 0, 2*n-1, open[arr[i]][1], 0);
            ct += query(0, 0, n*2-1, open[arr[i]][1], i);
        }
    }
    ct+=n;
    cout << ct;
}


//solution idea, answer = amount of overlapping couples + n (for sending them away)
// 