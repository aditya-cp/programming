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

// https://codeforces.com/contest/459/problem/D
int n;
vi segement_tree;
vi a;
vi f_frequency, b_frequency;
void assignFrequencies(){
    map<int,int>m;
    for(int i=0;i<n;i++){
        if(m.find(a[i])==m.end()){
            f_frequency[i]=1;
            m[a[i]]=1;
        }else{
            f_frequency[i]=m[a[i]]+1;
            m[a[i]]++;
        }
    }
    m.clear();
    for(int i=n-1;i>=0;i--){
        if(m.find(a[i])==m.end()){
            b_frequency[i]=1;
            m[a[i]]=1;
        }else{
            m[a[i]]++;
            b_frequency[i]=m[a[i]];
        }
    }
}
void update(int v, int l, int r, int index, int val){
    if(l==r) segement_tree[v]+=val;
    else{
        int mid = (l+r)/2;
        if(index<=mid){
            update(2*v, l, mid, index, val);
        }else{
            update(2*v+1, mid+1, r, index, val);
        }
        segement_tree[v]=segement_tree[2*v]+segement_tree[2*v+1];
    }
}
int query(int v, int l, int r, int ql, int qr){
    int mid = (l+r)/2;
    if(l>=ql && r<=qr) return segement_tree[v];
    else if(qr<=mid) return query(2*v, l, mid, ql, qr);
    else if(ql>mid) return query(2*v+1, mid+1, r, ql, qr);
    else return query(2*v, l, mid, ql, qr) + query(2*v+1, mid+1, r, ql, qr);
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
        int i,j;
        cin>>n;
        a.assign(n, 0);
        f_frequency.assign(n, 1), b_frequency.assign(n, 1);
        segement_tree.assign(4*n+4, 0);
        for(i=0;i<n;i++)cin>>a[i];
        assignFrequencies();
        for(i=n-1;i>0;i--){
            update(1, 0, n, b_frequency[i], 1);
        }
        // for(i=1;i<4*n+4;i++)cout<<i<<" ";cout<<endl;
        // for(i=1;i<4*n+4;i++)cout<<segement_tree[i]<<" ";cout<<endl;
        ll ans=0;
        for(i=1;i<n;i++){
            update(1, 0, n, b_frequency[i], -1);
            if(f_frequency[i]>1){
                ans+=query(1, 0, n, 1, f_frequency[i]-1);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}