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
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define repv(item, arr) for(auto item: arr) 
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

int const mxn = 1e3+10;
int n, m, arr[mxn], vis[mxn];

int main(){
    cin >> n >> m;
    rep(i, 0, n) {
        char c; cin >> c;
        if(c=='V') arr[i] = 1;
        else arr[i] = 0;
    }

    int mx = 0, ct=0;
    rep(t, 0, m){
        if(t==0){
            int start = 0, end=0, curr=0;
            rep(i, 0, n){
                if(arr[i]) ct++;
                else ct--;
                if(ct<0) {ct = 0; curr=i+1;}
                if(ct>mx){
                    start = curr; end = i;
                    mx = ct;
                }
            } 
            if(mx>0){
                rep(i, start, end+1){
                    vis[i]=1;
                }
            }
        }
        else{
            int maxf=0, maxv=0, f[2], v[2], f1=0, v1=0, cuf=0, cuv=0;
            rep(i, 0, n){
                if(vis[i]){
                    if(arr[i]) cuf--;
                    else cuf++;
                    if(cuf<0){cuf=0; f1=i+1;} //might be outside n, check later
                    if(cuf>maxf){
                        maxf = cuf;
                        f[0]=f1; f[1]=i;
                    }
                    
                }
                else{
                    if(arr[i]) cuv++;
                    else cuv--;
                    if(cuv<0) {cuv=0; v1=i+1;}
                    if(cuv>maxv){
                        maxv = cuv;
                        v[0]=v1; v[1]=i;
                    }
                }
            }
            if(maxv==0&&maxf==0) break;

            if(maxv>=maxf){
                rep(i, v[0], v[1]+1){
                    vis[i]=1;
                }
            }
            else{
                rep(i, f[0], f[1]+1){
                    vis[i]=0;
                }
            }

        } 
    }

    int ans = 0;
    rep(i, 0, n){
        if(vis[i]){
            if(arr[i]) ans++;
            else ans--;
        } 
    }
    cout << ans << endl;
}
