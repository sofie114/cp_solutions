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
int const mxn = 1e7;
ll n, k, dag[mxn], ettor[mxn];

int main(){
    cin >> n >> k;
    dag[0]=1;
    ll i=1, ans=0; 
    while(1){
        dag[i]=dag[i-1]*k+1;
        if(i>0) {
            ettor[i] = ettor[i-1]*k+1;
            if(i>k){
                i--;
                ans+=n-dag[i]+ettor[i];
                break;
            } 
            
        }
        if(dag[i]==n){
            ans = ettor[i];
            break;
        }
        if(dag[i]>n){
            ll curr=n;
            repd(u, 0, i){
                ans += ettor[u]*(curr/dag[u]);
                curr -= (curr/dag[u])*dag[u];
            }
            break;
        }
        i++;
        
    }
    cout << ans << endl;
}
