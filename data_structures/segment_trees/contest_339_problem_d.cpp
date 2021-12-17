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
typedef vector<vector<vl>> vvvl; 

// https://codeforces.com/contest/339/problem/D
vi segment_tree, a;
int height;
int merge(int v, int level){
    if(level % 2 == height % 2) return segment_tree[2*v] ^ segment_tree[2*v+1];
    else return segment_tree[2*v] | segment_tree[2*v+1];
}

int merge(int left, int right, int level){
    if(level % 2 == height % 2) return left ^ right;
    else return left | right;
}
void insert(int v, int vl, int vr, int pos, int val, int level){
    if(vl == vr){
        segment_tree[v] = val;
        return;
    }

    int mid = (vl+vr)/2;
    if(pos<=mid) insert(2*v, vl, mid, pos, val, level+1);
    else insert(2*v+1, mid+1, vr, pos, val, level+1);
    segment_tree[v] = merge(v, level);
}

void build(int v, int vl, int vr, int level){
    if(vl == vr) {
        segment_tree[v] = a[vl];
        return;
    }

    int mid = (vl+vr)/2;
    build(2*v, vl, mid, level+1);
    build(2*v+1, mid+1, vr, level+1);
    segment_tree[v] = merge(v, level);
}

int query(int v, int vl, int vr, int l, int r, int level){
    if(vl == l && vr == r) return segment_tree[v];
    if(vl>=l && r>=vr) return segment_tree[v];
    int mid = (vl+vr)/2;
    int left = query(2*v, vl, mid, l, r, level+1);
    int right = query(2*v+1, mid+1, mid, l, r, level+1);
    return merge(left, right, level);
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
        int m,i,j, n;
        cin>>height>>m;
        n=1<<height;
        a.assign(n, 0);
        segment_tree.assign(4*n, 0);
        for(i=0;i<n;i++){
            cin>>a[i];
        }

        build(1, 0, n-1, 0);

        while(m--){
            cin>>i>>j;
            insert(1, 0, n-1, i-1, j, 0);
            cout<<query(1, 0, n-1, 0, n-1, 0)<<endl;
        }
    }
    return 0;
}