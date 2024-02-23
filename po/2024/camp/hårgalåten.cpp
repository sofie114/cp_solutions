#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define vo vector
#define pb push_back
#define se second
#define fi first
#define sz(x) x.size()
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
void _pr(signed x) {cerr << x;}
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
ll const inf = LLONG_MAX, mxn = 3e5+10;
int n, m, start[mxn], f[mxn], indeg[mxn], allsame=1, indeg0, ans[mxn];
int posInCycle[mxn], whichCycle[mxn], vis[mxn], uniq[mxn];
vo<vi> cycles;
vo<uset<ll>> occ(mxn);

void fail(){
    cout << -1; exit(0);
}
void eval(){
    rep(i, 0, n) { 
        if(ans[i]==-1) fail();
    }
    rep(i, 0, n) cout << ans[i] << " "; 
}


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
}

int findfx(int x, int exp){
    return cycles[whichCycle[x]][(posInCycle[x] + exp) % sz(cycles[whichCycle[x]])];
}

signed main(){
    cin.tie(0)->sync_with_stdio(0); memset(ans, -1, sizeof(ans));
    cin>>n>>m;
    vi curr;

    rep(i, 0, n){
        cin>>start[i];
        curr.pb(start[i]);
        occ[i].insert(curr[i]);
    }
    rep(i, 0, m) {
        cin>>f[i];
        indeg[f[i]]++;
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

    int tails = 0;
    rep(i, 0, m) {
        if(indeg[i+1]==0) {
            tails++;
            indeg0 = i+1;
        }
    }

    if(tails > 1) fail();
    else if(tails == 1){
        rep(i, 0, n) {
            if(start[i] != indeg0) allsame = 0;
        }

        findCycles(indeg0-1);
        if(allsame && sz(cycles)==1) {
            rep(i, 0, n) ans[i] = m;
        }
        eval();
    } 
    else{
        //no need to check if perm
        findCycles(0);

        uset<int> afterN;
        set<int> lanes;
        vo<pii> seq; //position, what measure
        rep(i, 0, n){
            int tmp = findfx(start[i], i); //hittar f^i(start[i]) där start[i] = xi
            seq.pb({i, tmp});
            lanes.insert(i);
        }
        rep(u, 1, 2*m){ //BFS basically 
            vi rem;
            for(auto i: lanes){
                int tmp = findfx(seq[i].se, u*n); //hittar f^u*n(seq[i].se) 

                if(afterN.count(tmp)) rem.pb(i);
                else{
                    seq.pb({u*n+i, tmp});
                    afterN.insert(tmp);
                }
            }

            for(auto x: rem) lanes.erase(x);
        }
        sort(all(seq));
        /*
        bruteforce n*m
        rep(u, 0, m+10){
            rep(i, 0, n){
                seq.pb({u*n+i, findfx(start[i], u*n+i)});
            }
        }
        */

        int p1 = 0, p2 = 0, tot = 0;
        while(p1 < n && p2 <= sz(seq)){
            if(tot < m){
                if(p2==sz(seq)) break;
                if(uniq[seq[p2].se] == 0) tot++;
                uniq[seq[p2].se]++;
                p2++;
            }

            if(tot >= m){
                ans[p1] = seq[p2-1].fi - seq[p1].fi + 1;
                // pr(p1, p2)
                if(uniq[seq[p1].se] == 1) tot--;
                uniq[seq[p1].se]--;
                p1++; 
            }
        }
        
        eval();
    }

}
