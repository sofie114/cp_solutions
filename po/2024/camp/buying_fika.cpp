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
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
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

//go for outline with ;, then details
ll const inf = LLONG_MAX, mxn = 2e5+4;
ll n, c, val[mxn], ans[mxn], rem[40], add[40], cost[mxn];
vo<set<ar<ll, 3>>> buckets(40); //monleft, sumval, ind

int hibit(ll a){
    if(a==0) return 0;
    int leadingzeros = __builtin_clz(a);
    return 31 - leadingzeros +1 ; //so bucket 0 is 0 and not 2^0
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>c; 
    rep(i, 0, n){
        cin>>val[i];
    }
    rep(i, 0, n){ 
        cin>>cost[i]; 
    }

    ll hic = hibit(c); 
    rep(i, 0, n){
        ll h = hibit(cost[i]);
        buckets[hic].insert({c+rem[hic], -add[hic], i});
        // pr(hic, h)

        //apply query on all
        while(1){
            auto it = buckets[h].lower_bound({cost[i]+rem[h], -inf, -inf});
            if(it==buckets[h].end()) break;

            ll newmonleft = (*it)[0] - rem[h] - cost[i], tmp = hibit(newmonleft) ;
            if(tmp != h){
                buckets[tmp].insert({newmonleft + rem[tmp], (*it)[1]+val[i]+add[h]-add[tmp], (*it)[2]});
                buckets[h].erase(it);
            }
            else{
                //because now no jump down
                break;
            }
        }
        // pr(buckets)
        // pr(rem)
        rep(u, h+1, sz(buckets)){
            if(!sz(buckets[u])) continue;

            while(sz(buckets[u])){
                auto x = *(buckets[u].begin());
                ll newmonleft = x[0]-cost[i]-rem[u], tmp = hibit(newmonleft);
                // pr(tmp, x[1]+val[i])
                if(tmp != u){
                    buckets[tmp].insert({newmonleft+rem[tmp], x[1]+val[i]+add[u]-add[tmp], x[2]});
                    buckets[u].erase(x);
                }
                else{
                    break;
                }
            }
            rem[u] += cost[i]; add[u]+=val[i];
        }
        
    }

    rep(i, 0, sz(buckets)){
        for(auto x: buckets[i]){
            ans[x[2]] = x[1] + add[i];
        }
    }

    rep(i, 0, n)  cout << ans[i] << " ";
}
