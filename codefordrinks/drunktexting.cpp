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
//en dp som kollar vilka av a-j är aktiva och uppdaterar detta optimalt. 

int const mxn = 1005;
string a, b, ans;
int dp[mxn], dpmax=-1, nextind[mxn];
umap<char, set<int>> char_place;
umap<int, set<ar<int, 2>>> corrnext;

int main(){
    getline(cin, a); getline(cin, b);
    repd(i, 0, len(a)){
        char_place[a[i]].insert(i);

        int mx = 0, mxind=-1;
        repd(u, 0, len(b)){
            if(a[i] == b[u]){
                if(mx+1 > dp[u]){
                    dp[u] = mx+1;
                    corrnext[u].insert({int(i), mxind}); //the corresponding on string a and the chosen from string b
                }
                else{
                    if(dp[u] > mx){
                        mx = dp[u];
                        mxind = u;
                    }    
                }
            }
            else{
                if(dp[u] > mx){
                    mx = dp[u]; 
                    mxind = u;
                }
            }

            if(dp[u] > dpmax) dpmax = dp[u];
        }
    }

    rep(i, 0, len(b)){
        if(dp[i] == dpmax){
            auto it = corrnext[i].begin();
            int nex = (*it)[1], preva=(*it)[0];
            nextind[i] = nex;
            rep(u, i, len(b)){
                if(u==nex){
                    it = corrnext[u].upper_bound({preva, -1});
                    nex = (*it)[1]; preva = (*it)[0]; 
                    nextind[u] = nex;
                }
            }
            break;
        }
    }

    // rep(i, 0, len(b)) cout << dp[i] << " "; cout << endl;
    // rep(i, 0, len(b)) cout << nextind[i] << " ";
    
    if(dpmax==0){
        cout << a+b;
        return 0;
    }

    int currleft = dpmax, st = 0, preva = 0, nex=-1;
    rep(u, 0, len(b)+1){
        if(u==len(b)){
            // pr(st, u, preva, len(a), a.substr(preva, len(a)-preva));
            if(st < u); ans += b.substr(st, u-st);
            if(preva < len(a)) ans += a.substr(preva, len(a)-preva);

        }

        else if(u==nex || (nex == -1 && nextind[u] != 0)){
            if(st<u){ //for string b
                ans += b.substr(st, u-st);
            } 

            auto it = char_place[b[u]].lower_bound(preva); //can it be out of bounds
            // for string a
                ans += a.substr(preva, *it+1-preva);
                // pr(b.substr(st, u-st), a.substr(preva, *it+1-preva));
            
            // pr(ans, st, u, preva, *it);

            // currleft--; 
            nex = nextind[u];
            st = u+1; preva = *it+1; 
        }
    }
    // string s = "Vikea har skabelsatmarbejde ogmed USAs efterret men ingen stjenerste";
    // pr(len(a), len(b), len(ans), len(s));
    cout << ans << endl;
}
