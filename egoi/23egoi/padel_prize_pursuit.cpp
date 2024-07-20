#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vo vector
#define fi first
#define se second 
#define pb push_back
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define pr(x) cout << #x << "=" << x << endl;
int const mxn = 2e5+10, inf = LLONG_MAX;
int n, m, ans[mxn];
vo<vi> adj(mxn); 
vi nodetopers(mxn, -1);

void dfs(int at, vi &counter, int mx, int pers){ //return 
    //look for longest holder
    ans[pers]++;

    //go down to earlier medals
    for(auto x: adj[at]){
        int tmp = nodetopers[x], passmx=mx, passpers=pers;
        counter[tmp] += at-x;
        if(counter[tmp] > mx || (counter[tmp]==mx && tmp<pers)){
            passmx = counter[tmp]; passpers = tmp;
        }

        dfs(x, counter, passmx, passpers);
        counter[tmp] -= at-x;
    }

}


vo<vi> from(mxn);
vi indeg(mxn, 0);
signed main(){
    cin>>n>>m;
    rep(i, 0, m){
        int x, y; cin>>x>>y;
        //fix forest, add fake root
        nodetopers[i]=x;
        while(from[y].size()){
            int a = from[y].back();
            adj[i].pb(a); indeg[a]++;
            from[y].pop_back();
        }
        from[x].pb(i);
    }
    rep(i, 0, m){
        if(indeg[i]==0) adj[m].pb(i);
    }
    
    vi counter(n+1, 0);
    dfs(m, counter, -1, n);

    rep(i, 0, n) cout << ans[i] << " ";

}
