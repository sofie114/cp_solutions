#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--);
#define prvo(arr) for (auto item: arr){cout << item << " ";} cout << endl;
#define prar(arr, n) rep(i, 0, n){cout << arr[i] << " ";} cout << endl;
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

int const mxn=1e6;
int n, b, w;
long double dp[mxn][2];
vo<vo<long double>> batteri; //e, w, c

bool sortcol(const vector<long double>& a, const vector<long double>& b){
    if(a[3]==b[3]) return a[2] < b[2];
    else return a[3] > b[3];
}

int main(){
    cin >> n >> b >> w;
    rep(i, 0, n){
        long double a, b, c; cin >> a >> b >> c;
        batteri.pb({a, b, c, a/(b+w)});
    }
    sort(batteri.begin(), batteri.end(), sortcol);
    for(auto x:batteri){
        prvo(x);
    }

    rep(i, 0, n){
        for(ll t=b; t>=batteri[i][2]; t--){
            long double with_e = dp[int(t-batteri[i][2])][0]+batteri[i][0], with_w = dp[int(t-batteri[i][2])][1]+batteri[i][1];
            if(with_e/(with_w+w) > dp[t][0]/(dp[t][1]+w)){
                dp[t][0] = with_e, dp[t][1] = with_w;
            }
        }
        rep(t, batteri[i][2]+1, b+1){
            if(dp[t][0]/(dp[t][1]+w) < dp[t-1][0]/(dp[t-1][1]+w)){
                dp[t][0] = dp[t-1][0]; dp[t][1] = dp[t-1][1];
            }
        } 
        if(i==3) print(batteri[i][2], dp[int(b-batteri[i][2])][0], dp[int(b-batteri[i][2])][1]);
        print(i, dp[b][0], dp[b][1], dp[b][0]/(dp[b][1]+w));
    }

    cout << setprecision(6) << dp[b][0]/(dp[b][1]+w);
}


//budget with i items = 



