#include <bits/stdc++.h>
using namespace std;

#define all(x), begin(x), end(x)
#define unique(c), c.resize(unique(all(c))-c.begin(c))
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define umap unordered_map
#define len(arr) ((int) (sizeof(arr))/(sizeof(arr[0])))
#define lenv(vector) ((int) (vector).size())
#define setarr(arr, value) for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {arr[i] = value;}
typedef long long ll;

int const mxn = 500050;


bool visited[mxn];
vector<int> adj[mxn];
int tid[mxn];
int parent[mxn];
vector<vector<int>> deep_fruit;
int isfruit[mxn];

void dfs(int at, int deep){
    if (visited[at]) return;
    if (isfruit[at]==1) deep_fruit.push_back({deep, at});
    visited[at] = true;

    for (auto v:adj[at]){
        if (!(visited[v])) {
            parent[v]=at;
            dfs(v, deep+1);
        }
    }
}

void dfs1(int at, int dist_time){
    if (visited[at]) return;
    if (!(tid[at] == dist_time-1)) return;
    visited[at] = true;

    for (auto v:adj[at]){
        dfs1(v, dist_time-1);
    }
}

void bfs(int at){
    deque<pair<int, int>> q;
    pair<int, int> mypair = make_pair(at, -1); //node and distance
    q.push_back(mypair);

    while (!(q.empty())){
        pair mp = q.front();
        q.pop_front();
        int curr = mp.first;
        int dist = mp.second;
        if (tid[curr] != -1 && tid[curr] <= dist) continue;
        tid[curr] = dist;
        mp.second = dist+1;
        for (auto node:adj[curr]){
            if (tid[node] < dist+1) {
                mp.first=node;
                q.push_back(mp);
            }
        }
    }
    return;
}

bool sortcol(const vector<int>& v1, const vector<int>& v2){
    return v1[0] > v2[0];
} //reverse sorting

int main(){
    int n, f;
    cin>>n>>f;

    setarr(tid, -1);

    rep(i, 0, n-1){
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 0, f){
        int frukt;
        cin>>frukt;
        adj[0].push_back(frukt);
        isfruit[frukt] = 1;
    }

    bfs(0);   //fixing tid

    dfs(1, 0); //rooting tree and finding depth

    sort(deep_fruit.begin(), deep_fruit.end(), sortcol);
    setarr(visited, false);
    

    int robot=0;
    string which = "";
    rep(i, 0, f){
        int curr = deep_fruit[i][1];
        if (visited[curr]) continue;
        int time_now = 0, högst=curr;
        while (true){
            if (time_now == tid[curr] && curr != 0) {
                högst=curr;
            }else {
                break;
            }
            time_now++;
            curr = parent[curr];
        }
        visited[högst] = true; //placerar ut robot
        robot++;
        string stri = to_string(högst);
        which += stri + " ";

        for (auto x: adj[högst]){
            dfs1(x, tid[högst]);
        }

    }

    cout << robot << endl;
    cout << which << endl;

}
