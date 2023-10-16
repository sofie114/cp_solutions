#include <bits/stdc++.h>
using namespace std;

#define vo vector
#define ar array
#define umap unordered_map
#define pb push_back
typedef long long ll;

#define rep(i, a, b) for(ll i=(a); i<b; i++)
#define pr(a, b) cout << #a << "=" << a << " " << #b << "=" << b << endl;

int const mxn = 50+1, mxm=100, M=1000000007;
int t, n;

int main(){
    cin >> t;
    rep(T, 0, t){
        cin >> n;
        ll need[n], arr[n];
        memset(need, 0, sizeof(need));
        rep(i, 0, n) {
            cin >> arr[i];
            if(!arr[i]) need[i]++; //add for one basic
            else need[i]-=arr[i]-1;
        

        for(int i=n-1; i>=0; i--){
            if(need[i]>0){ 
                for(int k=i-1; k>=0; k--){
                    need[k]+=need[i];
                }
            }
        }
        ll ct = 1;
        rep(i, 0, n) if(need[i]>0) ct+= need[i];
        cout << ct << endl;
    }
}

//IDEA: loop from 0 to n-1, have one array need, if we already have some of that number in arr, need[i]-=arr[i]
//after loop n-1 to 0, if need[i]>0, we need it and the add 1 to each of the need[k] for k=i-1 to 0, some need[k] might be negative beause we
//got some of those numbers from the initial array, then we just add 1 to the negative number as if we are using that initial resource
// in the end, sum all number in need (the amount of operations to get 1 of each number < n) and add 1 (to get n).

// 4 1 0 2 0
// 3 0 0 1 0 changed arr
// 3 3 2 0 1   need
// +1


