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

int const mxn = 20, mxmid=20;
int n, add, mid, triwid, ans = 1e9, par[500], rnk[500];
int whites[mxmid][mxmid]; 
string fake[mxn];
vo<vo<string>> squares;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool ir(int a, int b){
    return a>=0&&b>=0&&a<triwid&&b<triwid; //maybe add not #
}

void whiteness(){
    int a, b, rows, cols;
    a = 0, cols=1;
    rep(i, 2, 2+triwid){
        b=0;
        rep(u, 1, 1+cols){ 
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; cols++; if(cols>triwid) break;
    }

    a = 0, cols=1;
    repd(i, n-2-triwid, n-2){ //hmm
        b=0;
        rep(u, 1, 1+cols){

            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; cols++; if(cols==triwid) break;
    }


    a = 0, cols=1;
    rep(i, 2, 2+triwid){
        b=0;
        repd(u, n-1-cols, n-1){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; cols++; if(cols>triwid) break;
    }

    a = 0, cols=1;
    repd(i, n-2-triwid, n-2){
        b=0;
        repd(u, n-cols-1, n-1){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; cols++; if(cols==triwid) break;
    }

    a = 0, rows = 1; //lodräta
    rep(u, 2, 2+triwid){
        b=0;
        rep(i, 1, 1+rows){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; rows++; if(rows>triwid) break;
    }

    a = 0, rows = 1;
    rep(u, 2, 2+triwid){
        b=0;
        repd(i, n-1-rows, n-1){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; rows++; if(rows>triwid) break;
    }

    a = 0, rows = 1;
    repd(u, n-2-triwid, n-2){
        b=0;
        rep(i, 1, 1+rows){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; rows++; if(rows==triwid) break;
    }

    a = 0, rows = 1;
    repd(u, n-2-triwid, n-2){
        b=0;
        repd(i, n-1-rows, n-1){
            if(fake[i][u]=='1') whites[a][b]++;  
            b++; 
        }
        a++; rows++; if(rows==triwid) break;
    }
}

int findpar(int v){
    if(par[v]==v) return v;
    return par[v] = findpar(par[v]);
}

void uni(int a, int b){
    a = findpar(a), b = findpar(b);
    if(a!=b){
        if(rnk[a]<rnk[b]) swap(a, b);
        par[b] = a;
        rnk[a]++;
    }
}

void gen_bin(string bin, int l, int ind){
    if(ind==l) {
        rep(i, 0, triwid){ //for each amt of bottom row filled

            squares.pb({});
            int prev = 0;
            string tmp="";

            rep(row, 1, triwid){ //add the top of triangle
                tmp = bin.substr(prev, row); prev+=row;
                
                rep(u, row, triwid){ 
                    tmp+='0';
                }

                squares.back().pb(tmp);
            }

            tmp = "";
            rep(u, 0, triwid) { //add longest row last
                if(u>=i) tmp+='1';
                else tmp += '0';
            }

            squares.back().pb(tmp);

        }
        return;
    }

    bin.pb('0');
    gen_bin(bin, l, ind+1);
    bin[ind] = '1';
    gen_bin(bin, l, ind+1); 
}

bool possible(vo<string> bin){
    rep(i, 0, triwid){ //set up union find
        rep(u, 0, triwid){
            int ind = i*n+u;
            par[ind] = ind;
        }
    }

    rep(i, 0, triwid){

        rep(u, 0, triwid){
            int ct = 0;
            vo<vo<int>> neidir = {};

            //union and check for hook
            for(auto d: dir){
                int nr=d[0]+i, nc=d[1]+u;
                if(ir(nr, nc)) {
                    if(bin[nr][nc]=='1') {ct++; neidir.pb({d[0], d[1]});}

                    int ind = i*n+u; 
                    if(bin[i][u]=='1' && bin[nr][nc]=='1') uni(ind, nr*n+nc);
                }
            }


            if(bin[i][u]=='1' && ct==2 && i!=triwid-1) { 
                int a = neidir[0][0], b = neidir[0][1], c = neidir[1][0], d = neidir[1][1];
                if(a!=c && b!=d) return 0; //hook
            }

            if(i>0 && u>0){ //square
                if(bin[i-1][u] == '1' && bin[i-1][u-1]=='1' && bin[i][u-1]=='1' && bin[i][u]=='1') return 0;
            }

        }
    }

    int parwhite=-1;
    rep(i, 0, triwid){ //check if white is in same union
        rep(u, 0, triwid){
            int ind = i*n+u;

            if(bin[i][u]=='1') {
                if(findpar(ind) != parwhite && parwhite != -1) return 0;
                parwhite = findpar(ind);
            }
        }
    }

    return 1;
}

int main(){
    cin >> n; mid = n/2+1; triwid = n/2-1; 

    rep(i, 0, n){
        cin >> fake[i];
        rep(u, 0, n){
            if(i==u && i==mid-1) {if(fake[i][u]=='0') add++; }
            else if((i==0 || u==0 || i==n-1 || u==n-1 || i==u || i+u==n-1) && fake[i][u]=='1') add++; //not correct
        }
    }

    //there are 8 corresponding squares if fig divided into triangles: find sum of the whiteness for one square in triangle
    whiteness();

    //generate all triangles, fill rest with 0 to make squares
    gen_bin("", triwid*(triwid-1)/2, 0);

    //manual add when only middle flake is white
    squares.pb({});
    rep(i, 0, triwid){
        string ok(triwid, '0');
        squares.back().pb(ok);
    }

    int amtpos=0; //number of valid triangles

    for(auto bin: squares){

        if(possible(bin)){

            // rep(i, 0, triwid){
            //      pr(bin[i]);
            // } cout << endl;

            //compare with fake, store best ans
            int test = 0;
            rep(i, 0, triwid){
                rep(u, 0, triwid){
                    if(bin[i][u] == '0') test += whites[i][u];
                    else {
                        if(i==triwid-1)  test += 4 - whites[i][u];
                        else test += 8 - whites[i][u];
                    }
                }
            }

            ans = min(ans, test);
            amtpos++;

        }
        
    }

    pr(ans, add, amtpos);
    cout << ans + add;
}

/*
15
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000
000000000000000

11
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000
00000000000


*/


