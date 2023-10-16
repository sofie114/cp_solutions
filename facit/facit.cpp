#include <bits/stdc++.h>
using namespace std;

#define umap unordered_map
#define vo vector
#define pb push_back
#define ar array
#define len(x) x.size()
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr1(x) cout << #x << "=" << x << endl
//what i dont use for no-google contests
#define all(v) v.begin(), v.end()i
#define repd(i, a, b) for(ll i=(b-1); i >= a; i--)
#define pr(x) {cout << x << " ";} cout << endl;
#define repv(item, arr) for (auto &item: arr)
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

//problems that occur
//check if brackets are including wrong, esp when a lot of if else statements
//dont loop over something while adding or removing things in it 
//check if i am printing an int, str etc and not an array
// created 2 variables with the same name (the first one will be used)
//i matris, när svaret inte kan vara mindre än en specifik square, checka att den inte är det då!
//make sure using float, int, char, string correctly, check if ll should be used
//declare variables outside main function and then not inside, if declared again inside, n and m will just be 0 in functions outside main.
//check if == and = is used incorrectly
//if with % 10^9+7, mod it after every rep
//when (integer+integer) is divided with 2 to produce a double, there wont be floating point values, instead do double+double
//when variable automatically turns to 0 during loop, buffer overflow somwhere else, my prob was doing vec.size()-integer, 
//.size() returns size_t (unsigned integer) which gives undefined behvaior when it becomes negative. 
//all outputs are 0 when submitting, not initializing a variable with a value and then doing var++, might work when i run myself but not when grader does it
//idenfifier x is undefined: variable out of scope (could be outside main), missing an opening or closing bracket somewhere relevant, 
//funcion, variable not declared
//when using set, DONT forget that the elements stored are unique, i forgot this and only focused on the sorting nature of sets, use multiset
//when erasing elements from a set, the iterator becomes invalidated


//RUNTIME ERROR
//Division with zero, array out of bounds, uninitialized variables, stack overflow(stack memory), infinite loops
//too small mxn even though not too small, segment tree
//var is ambiguous means bad var name, change it


//MEMORY LIMIT EXCEEDED (actually subheading for RTE)
// int, float: 4 bytes. double, long long: 8 bytes. In CSES 512 mb means appro 1e8 of 4 bytes or 6*1e6 of 8 bytes. Gave me memory limit for knapsack 
// 10^3 or 10^4 is the maximum depth for recursion calls, more will prob give memore limit

//TLE
// for bfs: remember to put it as visited when you add it to the queue and not when you have popped it out from the queue
// to prevent the same node from being added to the queue
// string concatenation with + operator is actually n^2, and the fastest is n. use .pb(single char) for O(1)
// vector.pop_back() is O(1)
// distance(set.begin(), iterator) is O(n) for bidirectional iterators (list, set, map, multiset), but O(1) for array, deque

//stupid mistakes:
//using i for both instead of arr[i], arr2[j];

//tips
// exit(0) for terminating everything
// return 0; in main to stop running the rest


//sort by first columns then second:
bool comp(const vector<int>& a, const vector<int>& b) {
    if (a[0] == b[0]) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

//sort by first column. 
bool sortcol(const vector<int>& a, const vector<int>& b){
    return a[0] < b[0];
}

//sort by first column array
bool sort(const int* a, const int* b){
    return a[0] < b[0];
}

//global array are initialized to default values but not local arrays/variables
int const mxn = 1e6;
bool vis[mxn];  //to false
string s; //will be ""
int n; // will be 0

int main(){
cin.tie(0)->sync_with_stdio(0);
//habit is good: use i and u for loops;
//use ct, ans, tmp, r, c, lo, hi, mxn; 



//implementation

//INPUT
getline(cin, s); //whole line
//sometimes we switch between cin >> and getline which causes problems: 
// if the input is:
// a
// b
// it is actually: a\nb\n, but when we do: cin >> variable_a; we only take the a and not \n.
// when we then take getline(cin, variable_b), we actually take the \n,
// which is why we need to use:
cin.ignore();

//STRING
int i_am_int;
i_am_int = s.size(); //finds len of strings
i_am_int = s.length();
reverse(s.begin(), s.end()); //reverse

//DATA STRUCTURES

//SET
set<int> myset;
myset.insert(1); //O(logn)
myset.erase(1) //erase element with value 1, O(logn);
myset.erase(myset.begin(), myset.begin()+n);
cout << myset.upper_bound(40); //O(logn)


//UNORDERED_MAP
unordered_map<int, int> umap; //no type of arrays can be used as keys, O(1) lookup
if (umap.count(1)) cout << "1 found in hashmap" << endl;
for(auto thing: umap){
    cout << thing.first;
}

//MAPS
map<ar<int, 2>, int> m; //C-style arrays cant be used as keys but std::array can be, O(logn) lookup

//CSTYLE ARRAYS    
//setting all values to zero inside main
int arr[mxn] = {0}; //does only work the variable mxn is a const, aka something to be inputed does not work if we want to set {0}
//outside main:
int arr[mxn];


//STD::ARRAYS
ar<int, 2> ok;
ok.fill(0); //filling with 0;

//VECTORS
vo<int> v;
vo<vo<int>> v2(mxn, vo<int>(mxn, -1));
v.pop_back(); //O(1) removal at back
v.erase(v.begin()+3); // erase at index 3, aka 4th element


//SORTING
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>()); //descending order
sort(v2[0].begin(), v2[0].end()); //sorting first row of a 2d vector
sort(arr, arr+mxn); 

reverse(arr, arr+mxn);
reverse(v.begin(), v.end()); //reversing
 
//POINTERS
auto it = v.begin();
cout << *it; //adding * before an iterator will print the value it points to    

//random
srand(3); //three is the seed
srand(time(0)); //to get different seeds
int a = (rand() % (100-5+1) + 5); //gives numbers from 5to100

//VARIABLES
int apple, banana;
swap(apple, banana);

//LOOPS
for(auto x: v){
    break;
}
for(int x:v){
    break;
}

//REFERENCES
vo<int> con;
for(auto x: con)  //loops through a copy of con
for(auto &x: con){} //x is a reference of type auto 
int x = 10;
int &y = x; //changing y will now change x too

//POWERS
ll power = pow(3, 4);
power = 2<<(6)   //a<<b is equivalent to a*=2^b



// DFS
int vis[mxn];
vo<int> adj[mxn];
void dfs(int at){
    if(vis[at]==1) return;
    vis[at] = 1;
    
    for(auto v; adj[at]){
        dfs(v);
    }
}

//BFS, maybe a bit wrong
queue<ar<int, 2>> q; q.push(0, 0);
vo<int> dist(mxn, -1); dist[0] = 0;
while(q.size()){
    ar<int, 2> v = q.front(); q.pop();

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for(auto x: dir){
        int a = v[0]+x[0], b = v[1]+x[1];
        if(dist[a][b]==-1){
            dist[a][b] == dist[v[0]][v[1]]+1;
            q.push({a, b});
        }
    }
}

// SEGMENT TREE - MINIMUM
ll seg[4*mxn], arr[mxn];

void build(int node, int lo, int hi){
    if(lo==hi) seg[node] = arr[lo];

    int mid = (lo+hi)/2;
    build(2*node+1, lo, mid);    //for 0-indexed, child nodes are 2n+1 and 2n+2, for 1-indexed theyre 2n and 2n+1
    build(2*node+2, mid+1, hi);
    seg[node] = min(seg[2*node+1], seg[2*node+2]);
}

ll query(int node, int lo, int hi, int ml, int mh){  //mh = myhigh, ml=mylow
    if(lo>=ml && hi<=mh) return seg[node];
    if(hi<ml || lo>mh) return INT_MAX; //because it is a minimum segtree
    int mid = (hi+lo)/2;
    ll left = query(2*node+1, lo, mid, ml, mh);
    ll right = query(2*node+2, mid+1, hi, ml, mh);
    return min(left, right);
}

void update(int node, int lo, int hi, int pos, ll new_val){
    if (lo==hi) {seg[node] = new_val; return;}
    int mid = (lo+hi)/2; 
    if(pos <= mid) update(2*node+1, lo, mid, pos, new_val);
    else update(2*node+2, mid+1, hi, pos, new_val);
    seg[node] = min(seg[2*node+1], seg[2*node+2]);
}

int main(){
    int n;
    build(0, 0, n-1);
    int a, b;
    query(0, 0, n-1, a, b);
    update(0, 0, n-1, a, b);
}



//BINARY SEARCH
bool f(int x){
    return true; //function 
}
int lo=0, hi=1e9, arr[1000]; //one of hi and lo should be a possible answer and one should not be
while(hi-lo>1){
    int mid = (hi+lo)/2;
    if(f(mid)) lo=mid;
    else hi = mid;
}

//TERNARY SEARCH
double f(double x):
    return x + (1/x)

int low = 0.001, high = 100

while(high - low > 0.000001){
    double m1 = (low * 2 + high) / 3;
    //m1 = low + (high - low) / 3
    double m2 = (low + 2 * high) / 3
    //m2 = high - (high - low) / 3;

    if(f(m2) > f(m1)){
        high = m2;
    }
    else{
        low = m1;
    }
}

//lowerbound, finds lowest element equal or exceeding val. 
vo<int>::iterator low = lower_bound(v.begin(), v.end(), 30); 
int lo = low-v.begin();
//upperbound finds first element exceeding val;
auto up = upper_bound(v.begin(), v.end(), 30); 
int up = up-v.begin();



    //KNAPSACK bottom up
    int const mxn = 1e3, mxs=1e5;
    int dp[mxs+1];
    int n, x;
    int weight[mxn], value[mxn];

    int main(){
        cin >> n >> x;
        rep(i, 0, n) cin >> weight[i];
        rep(i, 0, n) cin >> value[i];

        rep(i, 0, n){ //item
            for(ll t=x; t>=weight[i]; t--){ //william genius, running only where its needed
                dp[t] = max(dp[t], dp[t-weight[i]]+value[i]); //going from left to right to not add the same value multiple times 
            }
        }
        cout << dp[x];
    } 

    //solution classic 0/1 knapsack problem bottom up
    int const mxn = 2030;
    int items[mxn][2];
    int memo[mxn][mxn];
    //top down recursive approach with dp(n-1, c) as first call:
    int knapsack(int row, int col){
        if (row == -1 || col == 0) return 0;
        int ans = memo[row][col];
        if (ans != -1) return ans;
        if (items[row][1] > col) return memo[row][col] = knapsack(row-1, col);
        return memo[row][col] = max(items[row][0]+knapsack(row-1, col-items[row][1]), knapsack(row-1, col));
    }


//UNION FIND
ll rnk[n], par[n];
ll find(int v){
    if(par[v]==v) return v;
    return par[v] = find(v);
}
void union_sets(int a, int b){
    a = find(a), b = find(b);
    if(a!=b){
        if(rnk[a]>rnk[b]) swap(a, b);
        par[b] = a;
        rnk[a]++;
    }
}


//DIJKSTRA
priority_queue<ar<ll, 2>, vo<ar<ll, 2>>, greater<ar<ll, 2>>> pq; pq.push({3, 0}); //push start weight, node ind
vo<int> dist(mxn, 1e9); dist[start] = 0; 

while(pq.size()){
    ar<ll, 2> v = pq.top(); pq.pop();
    //check something
    for(auto x: adj[v[1]]){
        ll newd = x[0]+dist[v[1]];
        if(newd<dist[x[1]]){
            dist[x[1]] = newd;
            pq.push({newd, x[1]});
        }
    }

}


}

Grundytal 
Vi vill att mex talet är 0
mex minsta tal större än 0 som inte finns

L 3 3
W 3 2
L 4 2

W 3 1
W 2 1
L 1 1
W 1 0
