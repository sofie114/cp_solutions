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
//sjukaste idén nu för att lösa MLE
int const mxn = 2e4+1, mxr=1e3+2;
int r, c, n, wet[mxr][mxr], up[mxr][mxr], down[mxr][mxr]; //down is amt close enough hydrants on a lower row
// int height[mxn];
ll dp[mxr];
vo<ar<int, 2>> hydr;

int main(){
    cin.tie(0) -> sync_with_stdio(0);

    cin >> r >> c >> n;
    rep(i, 0, n){
        int a, b; cin >> a >> b; a--, b--;
        hydr.pb({a, b});
    }

    for(auto h: hydr){
        rep(u, 0, c){
            int disth = abs(h[1]-u)+h[0], sum=u+disth;
            if((sum)/2+(sum)%2 > u+h[0]) continue;
            // pr(u)
            if(sum % 2 == 0){
                int row = max(0, int(sum/2-u));
                down[row][u]++; 
                wet[row][u]+= row+u - (sum-row-u) + 1;
            }
            else{ 
                int row = max(0, int(sum/2+1-u));
                down[row][u]++; 
                wet[row][u]+= row+u - (sum-row-u) + 1; //please correct
            }

            up[h[0]][u]++; //good 
        }
    }

    rep(u, 0, c){
        int increasing = 0;
        rep(i, 0, r){
            if(i>0) wet[i][u] += increasing*2 + wet[i-1][u];
            increasing += down[i][u] - up[i][u];
        }
    }


    // rep(i, 0, r){
    //     rep(u, 0, c) cout << wet[i][u] << " ";
    //     cout << endl;
    // }

    //dp thing
    memset(dp, 0x3f, sizeof(dp));
    rep(i, 0, r){
        rep(u, 0, c){
            if(i==0) {
                if(u==0) dp[u] = 0 + wet[i][u];
                else{
                    dp[u] = dp[u-1] + wet[i][u];
                }
            }
            else if(u==0){
                dp[u] = dp[u] + wet[i][u];
            }
            else{
                dp[u] = min(dp[u], dp[u-1]);
                dp[u]+=wet[i][u];
            }

        } 
    }

    // rep(i, 0, r){
    //     rep(u, 0, c) cout << dp[i][u] << " ";
    //     cout << endl;
    // }
    cout << dp[c-1];

}

/*
5 6 3
2 2
2 6
3 2

0 0 2 2 
0 2 4 4 
2 4 6 6 
4 6 8 8 
4 6 8 8 

0 1 1 2 4 6 
1 5 6 8 10 12 
3 7 8 10 12 14 
3 7 8 10 12 14 
3 7 8 10 12 14

do you always want to maximize wetness in the pair wetness, time, actually why dont you try all 
insikt ksk: du vill aldrig gå ner eller vänster, 
om du går till vänster för att dodga så följer den med dig ett steg -> onödigt
when one hydrant starts affecting you, it will keep affecting you with the same amount for every step you take if the 
hydrant is to your left and down
else you will get 1 step closer and it will give you 2 more than it gave you before moving
vanlig bfs kanske funkar
max 2000 rutor i bfs kön, varje innehåller hydrants
vid varje rute, säg, (tid, hydrant) när den börjar verka. 
if we can only walk right and up, we know time when we reach there, hence we know what fire hydrants that affect it,
make bfs which passes on wetness and amount of hydrants affecting so we know how to increase wetness. 

if you find dist to all hydrants from 0.0, then for each step you move to the right, the ones already affecting you will keep doing it, some of the
ones on the right will start affecting you
the new dist is: olddist + totheright*2 - leftoldactivesones

bfs from start, carry on a list of hydrants that are not affcting you
placera ut alla gränser, max 1000sqrt2 för varje hydrant. när du passerar en gräns, gör den hydranten aktiv i din bfs state
union find
time < 2000

markera ut gränsen för varje hydrant: 1000*20000 - ok
om en/flera gränser besöks under bfs från rot, kolla upp om de redan är inkluderade
varje nod i kön har 2e4 för alla påslagna hydranter, max 1000 noder åt gången i kön - ok
O(1e6+2e7)

have 2 set2 with manhattan distance and index to all hydrants. 
one set is for the hydrants you get closer to when moving right and the other is for up
every move, dont update distances in set, just update a counter
when passing a hydrant on row/col, remove it from corresponding set. 
för alla som redan påverkar dig, en counter för vilka som påverkas dig ner/vänster, en upp och en höger

if memory limit gets exceeded, just do one square at a time

idea now:
1. you only walk right or up
2. each box contains wetness at the time we will reach there (which will be a fixed time)
3. find the path with the lowest sum. 
*/

