#include <bits/stdc++.h>
#include "maskroskaos.h"
using namespace std;
#define int long long
#define vo vector
#define pb push_back
#define se second
#define fi first
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef pair<int, int> pii;
#define umap unordered_map
#define uset unordered_set

#define rep(i, a, b) for(int i=(a); i<b; i++)
#define pr1(x) cerr << #x << '=' << x << ' ';
//for google contests
#define repd(i, a, b) for(int i=(b-1); i >= a; i--)
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
mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
int rand(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}
int const inf = LLONG_MAX, mxn = 1e5+4;
int ret, pre;

void rec(vi upper, vi lower, int lef, vi lowin){ 
    int pairs = upper.size(), half = pairs/2 + lef*(pairs%2);
    if(pairs == 1) {
        Answer(upper[0], lower[0]);
        return;
    }
    vi up1, up2, lo1, lo2;
    int a = accumulate(all(lowin), 0);
    swap(upper, lower);
    if(a > half){
        int ct = a;
        rep(i, 0, pairs){
            if(ct != half){
                if(lowin[i]){
                    pre = Query(upper[i]); ct--;
                }
                up2.pb(upper[i]);
            }
            else{
                if(lowin[i]) up1.pb(upper[i]);
                else up2.pb(upper[i]);
            }
        }
    }
    else{
        int ct = a;
        rep(i, 0, pairs){
            if(ct != half){
                if(!lowin[i]){
                    pre = Query(upper[i]); ct++;
                }
                up1.pb(upper[i]);
            }
            else{
                if(lowin[i]) up1.pb(upper[i]);
                else up2.pb(upper[i]);
            }
        }
    }

    vi lowin1, lowin2;
    rep(i, 0, pairs){
        int x = lower[i];
        if(lo1.size() == half || lo2.size() == pairs-half){
            if(lo1.size() < half) { lo1.pb(x); lowin1.pb(lef); }
            else { lo2.pb(x); lowin2.pb(lef); }
        }
        else{
            ret = Query(x);
            if(ret == pre){
                lo1.pb(x);
                lowin1.pb(lef^1);
            }
            else{
                lo2.pb(x);
                lowin2.pb(lef^1);
            }
            pre = ret;
        }
    }

    rec(up1, lo1, 1, lowin1);
    rec(up2, lo2, 0, lowin2);
}

void Solve(signed n){
    vi a(2*n); iota(all(a), 1);
    vi up, lo;
    rep(i, 0, 2*n){
        int x = a[i];
        ret = Query(x);
        if(ret != pre){
            up.pb(x);
        }
        else lo.pb(x);
        pre = ret;
    }
    vi tmp(n, 1);
    rec(up, lo, 1, tmp);
}

/*
save some queries with swapping upper and lower

divide into two sets, remove half of upper and all of lower to find matching using 1.5*len of each stage
queries: nlogn * 1.5
*/
