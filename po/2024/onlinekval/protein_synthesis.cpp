#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;
typedef vector<int> vi;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cerr << #x << "=" << x << " ";
#define pren cerr << endl;
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define trav(item, arr) for (auto &item: arr)
#define prar(arr, n) rep(i, 0, n){cerr << arr[i] << " ";} cerr << endl;
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
int const mxn = 1e5+10, mxm=1e6+10;
int n, m;
ll B=341298, mod=1e9+7;
string s;
set<int> lens;
umap<int, umap<ll, string>> prots;
vo<vi> adj(mxn);

typedef unsigned long long ull;
struct polynomialHash{
	vo<ll> prefh, bpow;
	polynomialHash(string& txt, ull B=341298, ull mod = 1e9+7) : prefh(txt.size()+1), bpow(txt.size()+1){ //acts as a member initializer
		bpow[0] = 1; 
		rep(i, 0, txt.size()){
			bpow[i+1] = (bpow[i]*B) % mod;
			prefh[i+1] = ((prefh[i]*B)%mod + txt[i]) % mod; 
		}
	}

	ll hashinterval(int l, int r){ 
    	ll ret = (prefh[r+1] - prefh[l]*bpow[r-l+1]) % mod;
		ret += mod; ret %= mod; //prevent ret from being negative
		return ret; 
	}
};


ll computeHash(string const& txt, ull B=341298, ull mod = 1e9+7) { 
	ll hash_val = 0, b_pow = 1;
	rep(i, 0, len(txt)){
		hash_val = (hash_val * B + txt[i]) % mod;
		b_pow = (b_pow*B) % mod;
	}
	return hash_val; 
}

int bfs1d(vo<vi>& edg){
    queue<int> q; q.push(0);
    vo<ll> dist(mxn, 1e10); dist[0] = 0;
    while(q.size()){
        int v = q.front(); q.pop();
		if(v==n) break;

        for(auto x: edg[v]){
            if(dist[x]==1e10){
                dist[x] = dist[v]+1;
                q.push(x);
            }
        }
    }   

	return dist[n];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
	cin >> n >> s >> m; 
	polynomialHash polynomialHash(s, B, mod);

	rep(i, 0, m){
		string a; cin >> a;
		if(len(a) > n) continue;
		ll h = computeHash(a, B, mod);
		prots[len(a)][h] = a;
		lens.insert(len(a));
	}

	for(auto leng: lens){
		//compute all hashes in string s of size leng;
		rep(i, 0, len(s)-leng+1){
			int l = i, r = i+leng-1;
			ll hash = polynomialHash.hashinterval(l, r);

			// pr(hash, l, r)

			if(prots[leng].count(hash))
			{
				//compare - no need because of good hash
					// bool ch = 1;
					// if(prots[leng][hash] == s.substr(i, leng));

				adj[i].pb(i+leng);
			}
		}
	}

	//bfs
	cout << bfs1d(adj);

}


/*
98
97*26 + 98*1
97*1*26
*
