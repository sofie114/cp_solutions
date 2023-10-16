#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()i
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
#define print(...) {cout << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cout << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cout << arg << ", ";
    print_vars(args...);
}

int const mxn = 2*1e3;
int n, k, h[mxn], ans=0;

int main(){
    cin >> n >> k;
    rep(i, 0, n) cin >> h[i];

    rep(i, 0, n){
        // print(i);
        int a[k+1], b[k+1];
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
        int ct=0, kt=0;
        rep(u, i+1, n){
            if(kt>k) break;
            if(h[u] < h[i]){
                a[kt]=ct;
                kt++;
            }
            ct++;
        }
        if(kt<k+1) rep(u, kt, k+1) a[u]=ct;
        // prar(k+1, a);


        ct=0, kt=0;
        repd(u, 0, i){
            if(kt>k) break;
            if(h[u]<h[i]){
                b[kt]=ct;
                kt++;
            }
            ct++;
        }
        if(kt<k+1) rep(u, kt, k+1) b[u]=ct;
        
        // prar(k+1, b);

        //find best combo
        int mx=1+a[0]+b[0];

        rep(u, 0, k){
            mx = max(mx, 1+a[u]+b[k-u]);
        }

        ans = max(mx*h[i], ans);
    }

    cout << ans;
}