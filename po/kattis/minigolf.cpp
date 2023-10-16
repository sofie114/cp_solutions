#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--);
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto item: arr)
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

int const mxn=1e5+10;
int r, c, k, start[2], e[2];
vo<set<ar<ll, 2>>> rows, cols;

int main(){
    cin >> r >> c >> k; rows.resize(r), cols.resize(c);
    rep(i, 0, r){
        rep(t, 0, c){
            char c; cin >> c;
            if(c=='G') e[0]=i, e[1]=t;
            if(c=='.'||c=='G') rows[i].insert({t, 1}), cols[t].insert({i, 1});
            else if(c=='#') {rows[i].insert({t, 0}), cols[t].insert({i, 0}); print(i, t)}
            else if(c=='S') start[0]=i, start[1]=t;
        }
    }

    rep(i, 0, r) {repv(x, rows[i]) pr(x[0]);}
    rep(i, 0, r) {repv(x, rows[i]) pr(x[1]);}

    queue<ar<int, 2>> q; q.push({start[0], start[1]});
    int d[r][c]; memset(d, -1, sizeof(d)); d[start[0]][start[1]] = 0;
    while(q.size()){
        ar<int, 2> v = q.front(); q.pop();
        print(v[0], v[1]);

        while(1){
            //down 
            auto it1 = cols[v[1]].lower_bound({v[0], 0}); int r = (*it1)[0];
            if(it1!=cols[v[1]].end() && (*it1)[1] && r <= v[0]+k){
                print("down", r);
                auto it2 = rows[r].lower_bound({v[1], 0});
                print((*it2)[0]);
                cols[v[1]].erase(it1);
                rows[r].erase(it2);

                d[r][v[1]] = d[v[0]][v[1]]+1;
                q.push({r, v[1]}); 
            }
            else break;
        }
        while(1){
            //up
            auto it1 = cols[v[1]].lower_bound({v[0], 0}); 
            if(it1==cols[v[1]].begin()) break;
            it1--; int r = (*it1)[0];
            print("under", r);
            if((*it1)[1] && r >= v[0]-k){
                auto it2 = rows[r].lower_bound({r, 0});
                cols[v[1]].erase(it1);
                rows[r].erase(it2);

                d[r][v[1]] = d[v[0]][v[1]]+1;
                q.push({r, v[1]}); 
            }
            else break;      
        }
        while(1){
            //left
            auto it1 = rows[v[0]].lower_bound({v[1], 0}); 
            if(it1==rows[v[0]].begin()) break;
            it1--; int c = (*it1)[0];
            if((*it1)[1] && c >= v[1]-k){
                print("left", c);
                auto it2 = cols[c].lower_bound({c, 0});
                rows[v[0]].erase(it1);
                cols[c].erase(it2);

                d[v[0]][c] = d[v[0]][v[1]]+1;
                q.push({v[0], c}); 
            }
            else break;           
        }
        while(1){
            //right
            rep(i, 0, r) {repv(x, rows[i]) pr(x[0]);}
            rep(i, 0, r) {repv(x, rows[i]) pr(x[1]);}
            auto it1 = rows[v[0]].lower_bound({v[1], 0}); int c = (*it1)[0];
            rep(i, 0, r) {repv(x, rows[i]) pr(x[1]);}
            print(c, (*it1)[1], distance(rows[v[0]].begin(), it1));
            if(it1!=rows[v[0]].end() && (*it1)[1] && c <= v[1]+k){
                print("right", c, (*it1)[1]);
                auto it2 = cols[c].lower_bound({v[0], 0});
                rows[v[0]].erase(it1);
                cols[c].erase(it2);

                d[v[0]][c] = d[v[0]][v[1]]+1;
                q.push({v[0], c}); 
            }
            else break;
        }
    }
    print("ok");
    cout << d[e[0]][e[1]];

}