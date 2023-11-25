#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr2(x) cerr << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr1(x) {cerr << x << " ";} cerr << endl;
#define repv(item, arr) for (auto &item: arr)
#define prar(n, arr) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
#define pr(...) {cerr << #__VA_ARGS__ << "="; print_vars(__VA_ARGS__);}
template<typename T>
void print_vars(T arg) {
    cerr << arg << endl;
}

template<typename T, typename... Args>
void print_vars(T arg, Args... args) {
    cerr << arg << ", ";
    print_vars(args...);
}
//go for outline with ;, then details
int const mxn = 1e5+10;
ll n, x;
double y;
vo<ll> strips;

int main(){
    cin >> n >> x >> y;
    rep(i, 0, n){
        int a; cin >> a; strips.pb(a);
    }

    sort(strips.begin(), strips.end());

    int sum=0, ct=0;
    rep(i, 0, len(strips)){
        if(double(sum+strips[i]*x) / double(ct+1) > y){
            break;
        }
        else{
            sum+= strips[i]*x;
            ct++;
        }
    }

    cout << ct;
}


