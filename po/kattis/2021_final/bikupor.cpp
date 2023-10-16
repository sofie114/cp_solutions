#include <bits/stdc++.h>
using namespace std;
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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;

int const MAXN = 200001;
int n,m,k;

vector<vector<int> > graph(MAXN, vector<int>());

int to[MAXN], deg[MAXN];
set<pair<int,int> > comps;

int parent(int i){
    while(i != to[i]){
        i = to[i];
    }
    return i;
}

void merge(int i, int j){
    int i2 = parent(i);
    int j2 = parent(j);
    if(i2 != j2){
        if(deg[i2] < deg[j2])swap(i2,j2);
        comps.erase({deg[i2], i2});
        comps.erase({deg[j2], j2});
        to[j2] = i2;
        deg[i2] += deg[j2];
        comps.insert({deg[i2],i2});
    }
}

void increment(int small, int big){
    int i2 = parent(big);
    to[small] = i2;
    comps.erase({deg[i2], i2});
    deg[i2]++;
    comps.insert({deg[i2],i2});
}

void add(int i){
    bool found = 0;
    trav(y, graph[i]){
        if(y > i){
            if(!found){
                increment(i, y);
                found = 1;
            }
            else{
                merge(i, y);
            }
        }
    }   
    if(!found){
        comps.insert({1, i});
    }
}

int main() {
    cin >> n >> m >> k;
    rep(c1,0,m){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    rep(c1,0,n){
        to[c1] = c1;
        deg[c1] = 1;
    }

    rep(c1,0,n-k){
        bool found = 0;
        trav(y, graph[c1]){
            if(y >= n-k)found = 1;
        }
        if(!found){
            cout << "1\n" << c1+1 << "\n";
            return 0;
        }
    }

    vector<int> answer;
    for(int c1 = n-1; c1 >= 0; c1--){
        add(c1);
        if(c1 < n-k){
            int comp_size = comps.begin()->first;
            print(c1, comp_size);
            if(comp_size <= n-k-c1){
                int root = comps.begin()->second;
                print(n-k-c1, root);
                rep(c2,0,n){
                    if(parent(c2) == root)answer.push_back(c2);
                }
                break;
            }
        }
    }
    if(sz(answer) == 0){
        cout << "-1\n";
    }
    else{
        cout << sz(answer) << "\n";
        trav(y,answer){
            cout << y+1 << " ";
        }
        cout << "\n";
    }
    return 0;
}