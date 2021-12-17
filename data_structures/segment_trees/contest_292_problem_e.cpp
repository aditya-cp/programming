#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef pair<string, string> pss; 
typedef vector<int> vi; 
typedef vector<vi> vvi;  
typedef vector<pii> vii; 
typedef vector<int, pii> viii; 
typedef vector<vii> vvii;
typedef vector<pll> vll; 
typedef vector<ll> vl; 
typedef vector<vl> vvl; 
typedef vector<vector<vl> > vvvl; 

// https://codeforces.com/contest/292/problem/E
int n;
vi segment_tree;
vi a, b;
void propagate(int v, int l, int r){
    int mid = (l+r)/2;
    if(segment_tree[v]!=-1){
        segment_tree[2*v] = segment_tree[v];
        segment_tree[2*v+1] = segment_tree[v]+mid+1-l;
        segment_tree[v]=-1;
    }
}
int query(int v, int l, int r, int index){
    if(l==r){
        if(segment_tree[v]==-1) return b[l];
        else return a[segment_tree[v]];
    }else{
        int mid = (l+r)/2;
        propagate(v, l, r);
        if(index<=mid) return query(2*v, l, mid, index);
        else return query(2*v+1, mid+1, r, index);
    }
}
void update(int v, int l, int r, int al, int ar, int bl, int br){
    if(l!=r) propagate(v, l, r);
    if(l == bl && r == br){
        segment_tree[v] = al;
    }else{
        int mid = (l+r)/2;
        if(br<=mid) update(2*v, l, mid, al, ar, bl, br);
        else if(bl>mid) update(2*v+1, mid+1, r, al, ar, bl, br);
        else{
            int leftCount = mid-bl+1;
            int rightCount = br-(mid+1)+1;
            update(2*v, l, mid, al, al+leftCount-1, bl, bl+leftCount-1);
            update(2*v+1, mid+1, r, al+leftCount, ar, bl+leftCount, br);
        }
    }
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout); 
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(NULL);
    int tttt;
    // cin>>ttttt;
    tttt=1;
    while(tttt--){
        int m,i,j,k;
        cin>>n>>m;
        segment_tree.assign(4*n, -1);
        a.assign(n, 0);
        b.assign(n, 0);
        for(i=0;i<n;i++)cin>>a[i];
        for(i=0;i<n;i++)cin>>b[i];
        // for(i=1;i<4*n;i++)cout<<i<<" ";cout<<endl;
        // for(i=1;i<4*n;i++)cout<<segment_tree[i]<<" ";cout<<endl;
        while(m--){
            cin>>i;
            if(i==2) {
                cin>>j;
                cout<<query(1, 0, n-1, j-1)<<endl;
            }else{
                int s;
                cin>>j>>k>>s;
                update(1, 0, n-1, j-1, j+s-2, k-1, k+s-2);
                // for(i=1;i<4*n;i++)cout<<segment_tree[i]<<" ";cout<<endl;
            }
        }
    }
    return 0;
}