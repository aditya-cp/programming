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

// https://codeforces.com/contest/356/problem/A
vi segment_tree;
vi ans;
void update(int v, int vl, int vr, int x, int ql, int qr){
    // cout<<"v: "<<v<<",  vl: "<<vl<<", vr: "<<vr<<", x: "<<x<<", ql: "<<ql<<", qr: "<<qr;
    // cout<<", segment_tree[v]: "<<segment_tree[v]<<endl;
    if(segment_tree[v]){
        if(segment_tree[v] == ans[segment_tree[v]]) ans[segment_tree[v]] = x;
        segment_tree[v]=x;
    }else {
        int mid = (vl + vr)/2;
        if(qr<=mid){
            update(2*v, vl, mid, x, ql, qr);
        }else if(ql>mid){
            update(2*v+1, mid+1, vr, x, ql, qr);
        }else{
            update(2*v, vl, mid, x, ql, qr);
            update(2*v+1, mid+1, vr, x, ql, qr);
            // cout<<segment_tree[2*v]<<" "<<segment_tree[2*v+1]<<endl;
            if(segment_tree[2*v] == segment_tree[2*v+1]){
                segment_tree[v] = segment_tree[2*v];
            }
        }
    }
}

void build(int v, int vl, int vr){
    if(vl == vr) {
        segment_tree[v] = vl;
        return;
    }

    int mid = (vl+vr)/2;
    build(2*v, vl, mid);
    build(2*v+1, mid+1, vr);
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
        cin>>n>>m;
        segment_tree.assign(4*n, 0);
        build(1, 1, n);
        ans.assign(n+1, 0);
        for(i=1;i<=n;i++)ans[i]=i;
        // for(i=1;i<4*n;i++)cout<<i<<" ";cout<<endl;
        // for(i=1;i<4*n;i++)cout<<segment_tree[i]<<" ";cout<<endl;
        // for(i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<endl;
        while(m--){
            int x;
            cin>>i>>j>>x;
            update(1, 1, n, x, i, j);
            // for(i=1;i<4*n;i++)cout<<segment_tree[i]<<" ";cout<<endl;
            // for(i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<endl;
        }
        for(i=1;i<=n;i++){
            if(ans[i]==i)ans[i]=0;
            cout<<ans[i]<<" ";}cout<<endl;
    }
    return 0;
}