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
//always pick to remove the flavor which reappears the latest out of the curr flavors

int const mxn = 3*1e5;
ll n, m, k, q[mxn], ans;
set<int> flav_ind[mxn];
set<ar<ll, 2>> coming_flav;
umap<ll, ll> curr;

int main(){
    cin >> n >> m >> k;
    rep(i, 0, n) {
        cin >> q[i];
        flav_ind[q[i]].insert(i);
    }


    rep(i, 0, n){
        // for(auto item: curr) cout << item.first << " "; cout << endl;

        if(curr.count(q[i])){
            coming_flav.erase({i, q[i]}); 
            auto it = flav_ind[q[i]].upper_bound(i);

            if(it==flav_ind[q[i]].end()){
                coming_flav.insert({int(1e9), q[i]});
            }
            else{
                coming_flav.insert({*it, q[i]});
            }

            continue;
        }

        if(len(curr) < k){
            curr[q[i]] = 1;
            auto it = flav_ind[q[i]].upper_bound(i);
            // pr(q[i], *it);

            if(it==flav_ind[q[i]].end()){
                coming_flav.insert({int(1e9), q[i]});
            }
            else{
                coming_flav.insert({*it, q[i]});
            }
            ans++;
        }
        else{
            auto it = coming_flav.end(); it--;
            curr.erase((*it)[1]);
            curr[q[i]] = 1;
            coming_flav.erase(it);
            // pr(q[i], (*it)[1], (*it)[0]);

            auto it1 = flav_ind[q[i]].upper_bound(i);
            if(it1==flav_ind[q[i]].end()){
                coming_flav.insert({int(1e9), q[i]});
            }
            else{
                coming_flav.insert({*it1, q[i]});
            }
            ans++;
        }
    }

    cout << ans;

}
