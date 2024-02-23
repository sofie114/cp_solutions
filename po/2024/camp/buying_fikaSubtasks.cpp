#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
#define se second
#define fi first
#define sz(x) x.size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<int, int> pii;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define pren cerr << endl;
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define trav(item, arr) for (auto &item: arr)
void _pr(int x) {cerr << x;}
void _pr(long long x) {cerr << x;}
void _pr(unsigned long long x) {cerr << x;}
void _pr(double x) {cerr << x;}
void _pr(char x) {cerr << '\'' << x << '\'';}
void _pr(const char* x) {cerr << x;}
void _pr(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void _pr(const pair<T, V> &x);
template<typename T, typename V> void _pr(const pair<T, V> &x) {cerr << "\e[95m" << "[ "; _pr(x.first); cerr << ", "; _pr(x.second); cerr << "\e[95m" << ']';}
template<typename T> void _pr(const T &x) {int F=0; cerr << '{'; for(auto &i: x) cerr << (F++ ? ", " : ""), _pr(i); cerr << "\e[91m" << '}';}
template <typename T, typename... V> void _pr(T t, V... v) {_pr(t); if(sizeof...(v)) cerr << ", "; _pr(v...);}
#define pr(x...) cerr << "\e[91m" << __func__ << ':' << __LINE__ << " [" << #x << "] = ["; _pr(x); cerr << "\e[91m" << ']' << "\033[0m"  << endl;

ll const inf = LLONG_MAX, mxlog = 25;
template<class T> //now both ll and int possile
struct RMQ{
    T n; vo<vo<T>> st; vo<T> lg;

    RMQ(vo<T> &arr): n(T(sz(arr))), st(mxlog, vo<T>(n, 0)), lg(n+1, 0){
        st[0] = arr;
        rep(k, 1, mxlog){
            rep(i, 0, n-(1<<k)+1){
                st[k][i] = min(st[k-1][i], st[k-1][i+(1<<(k-1))]); //min
            }
        }
        lg[1] = 0; rep(i, 2, n+1) lg[i] = lg[i/2]+1;
    }
    ll qry(int l, int r){
        int k = lg[r-l+1];
        return min(st[k][l], st[k][r-(1<<k) + 1]); //min
    }
};

//go for outline with ;, then details
int const mxn = 2e5+4;
ll n, c, val[mxn], ans[mxn], prefv[mxn], prefc[mxn], dp[mxn][54];
vll cost;
int increasing = 1;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>c; cost.resize(n);
    rep(i, 0, n){
        cin>>val[i];

        prefv[i] = val[i]; 
        if(i>0) prefv[i] += prefv[i-1]; 
    }
    rep(i, 0, n){ 
        cin>>cost[i]; 
        
        prefc[i] = cost[i]; 
        if(i>0) {
            prefc[i]+=prefc[i-1];
            if(cost[i] < cost[i-1]) increasing = 0;
        }
    }

    if(c<=50){
        repd(i, 0, n){
            rep(u, 0, c+1){
                if(cost[i] <= u){
                    dp[i][u] += val[i];
                    if(i<n-1){
                        dp[i][u] += dp[i+1][u-cost[i]];
                    }
                }
                else if(i<n-1)
                    dp[i][u] += dp[i+1][u];
            }
        }

        rep(i, 0, n) cout <<  dp[i][c] << " ";
    }
    else if(n<=1000){
        repd(i, 0, n){ //k val
            ll mon = c, tmpval = 0;
            rep(u, i, n){
                if(cost[u] <= mon){
                    tmpval += val[u];
                    mon -= cost[u];
                }
            }
            ans[i] = tmpval;
        }

        rep(i, 0, n) cout << ans[i] << " ";
    }
    else if(increasing){
        rep(i, 0, n){
            ll lo=i, hi=n, tmp1 = 0, tmp2=0; 
            if(i > 0) tmp1 = prefv[i-1], tmp2 = prefc[i-1];

            while(hi-lo>1){
                ll mid = (hi+lo)/2;
                
                if(prefc[mid] - tmp2 <= c) lo = mid;
                else hi = mid;
            }

            if(cost[i] <= c){
                ans[i] = prefv[lo] - tmp1;
            }

        }
        rep(i, 0, n) cout << ans[i] << " ";
    }
    else{
        RMQ<ll> rmq(cost);
        rep(i, 0, n){
            ll mon = c, curr=i;
            while(1){
                int lo = curr-1, hi = n;
                while(hi-lo>1){
                    int mid = (lo+hi)/2;
                    if(rmq.qry(curr, mid) <= mon) hi = mid;
                    else lo = mid;
                }
                if(hi == n) break;
                curr = hi; 
                mon -= cost[curr]; ans[i]+=val[curr];
                curr++;
            }
        }

        rep(i, 0, n) cout << ans[i] << " ";
    }
}
