#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define vo vector
#define pb push_back
#define ar array
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

//go for outline with ;, then details
int const mxn = 3e5+4;
int const mxsquared = 3005;
ll n, m, curr[mxn], ans[mxn], uniq[mxn], tot, indeg[mxn], vis[mxn], posInCycle[mxn], whichCycle[mxn];
vo<uset<ll>> occ(mxn);
vi start, f;
vo<vi> cycles;

void singleCycle(int curr){
    cycles.pb({}); 
    while(1){
        if(vis[curr]) break;
        posInCycle[curr+1] = sz(cycles.back());
        whichCycle[curr+1] = sz(cycles)-1;
        cycles.back().pb(curr+1);
        vis[curr] = 1;
        curr = f[curr]-1;
    }
}
void findCycles(int v){
    singleCycle(v);
    rep(i, 0, m){
        if(vis[i]) continue;
        singleCycle(i);
    }
    // pr(cycles
    // pr(posInCycle)
}

int findfx(int x, int exp){
    // pr(x, exp)
    return cycles[whichCycle[x]][(posInCycle[x] + exp) % sz(cycles[whichCycle[x]])];
}

int rig(int ind){
    if(ind<n-1) return ind+1;
    return 0;
}

void evaluate(){
    rep(i, 0, n) { if(ans[i]==-1) {pr("exit from here 2") cout << -1; exit(0);} }
    rep(i, 0, n) cout << ans[i] << " "; 
}
void fail(){ rep(i, 0, n) if(ans[i]==-1) { pr("exit from here") cout << -1; exit(0);} }

int main(){
    vi permcheck;
    cin>>n>>m; 
    cin.tie(0)->sync_with_stdio(0); memset(ans, -1, sizeof(ans)); f.resize(m);
    rep(i, 0, n) {
        cin>>curr[i];
        start.pb(curr[i]);
        occ[i].insert(curr[i]);
    }
    rep(i, 0, m) {
        cin>>f[i];
        indeg[f[i]]++;
        permcheck.pb(i+1);
    }

    if(n==1){
        int time;
        rep(i, 1, m+1){
            occ[0].insert(curr[0]);
            curr[0] = f[curr[0]-1];
            if(sz(occ[0]) >= m){
                time = i;
                break;
            }
            if(i==m){
                cout << -1; exit(0);
            }
        }
        cout << time;
        exit(0);
    }
    else if(n<=500 && m<= 500){
        int t = 2, prevfirst;
        rep(_, 0, m*n+1){
            int ch = 1;
            prevfirst = curr[0];
            rep(i, 0, n){
                if(i==n-1) curr[i] = f[prevfirst-1];
                else curr[i] = f[curr[rig(i)]-1];
                occ[i].insert(curr[i]);
            
                if(ans[i] != -1) continue;
                else if(sz(occ[i]) >= m) ans[i] = t;
                else ch = 0;
            }
            t++;
        }
        evaluate();
    }
    else if(n<=3000 && m<=3000){ //group 4, 5
        //check number of tails
        int tails=0, allsame = 1, indeg0ind=0;
        rep(i, 0, m) {if(indeg[i+1]==0) {tails++; indeg0ind = i+1; }; }
        rep(i, 0, n) { 
            if(start[i] != indeg0ind) allsame = 0;
        }
        
        if(tails > 1) { fail(); }
        if(tails==1){
            findCycles(indeg0ind-1);
            if(allsame && sz(cycles)==1) {
                rep(i, 0, n) ans[i] = m; 
            } 
            evaluate();
        }
        else{
            if(!is_permutation(all(f), permcheck.begin())) fail();
            findCycles(0);
    
            vi seq;
            rep(exp, 0, n*(m+5)){
                seq.pb(findfx(start[exp%n], exp));
            }
            pr(seq)

            int p1=0, p2=0;
            while(p1 < n && p2 < n*(m+5)){
                if(tot < m){
                    if(uniq[seq[p2]] == 0) tot++;
                    uniq[seq[p2]]++;
                    p2++;
                }
                if(tot >= m){
                    ans[p1] = p2-p1;
                    uniq[seq[p1]]--; if(uniq[seq[p1]] == 0) tot--;
                    p1++;
                }

            }
            evaluate();
        }
    }
    else{
        // group 2
        rep(i, 0, n) start.pb(start[i]);
        int p1=0, p2=0;
        while(p1 < n && p2 < 2*n){
            if(tot < m){
                if(uniq[start[p2]] == 0) tot++;
                uniq[start[p2]]++;
                p2++;
            }
            if(tot >= m){
                ans[p1] = p2-p1;
                uniq[start[p1]]--;
                if(uniq[start[p1]] == 0) tot--;
                p1++;
            }

        }
        evaluate();
    }
}
