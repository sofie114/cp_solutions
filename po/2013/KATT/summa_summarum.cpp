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

int const mxn=1e5+10;
ll n, t, sa=0, sb=0;
vo<ll> a;
vo<ll> b;

int main(){
    cin >> n;
    rep(i, 0, n){
        cin >> t; a.pb(t);
        sa+=t;
    }
    rep(i, 0, n){
        cin >> t; b.pb(t);
        sb+=t;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll fakea, fakeb, best = abs(sb-sa-2*(-a[0]+b[0]));
    rep(i, 0, n){
        
        ll lo=-1, hi=n;
        while(hi-lo>1){
            ll mid = (lo+hi)/2;
            fakea = sa-a[i]+b[mid]; fakeb = sb-b[mid]+a[i];
            if(abs(fakeb-fakea) < best){ //assume lo is best
                best = abs(fakeb-fakea);
            }
            if(fakeb-fakea >= 0) lo = mid;
            else hi=mid;
        }

    }   

    cout << best;

}
