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

// https://codeforces.com/contest/61/problem/E
int n;
vl segment_tree;
vl a;
void update(int v, int l, int r, int index, ll val){
    if(l==r)segment_tree[v]=val;
    else{
        int mid = (l+r)/2;
        if(index<=mid) update(2*v, l, mid, index, val);
        else update(2*v+1, mid+1, r, index, val);
        segment_tree[v] = segment_tree[2*v]+segment_tree[2*v+1];
    }
}

ll query(int v, int l, int r, int ql, int qr){
    if(ql>qr) return 0;
    // cout<<v<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
    int mid = (l+r)/2;
    if(l>=ql && r<=qr) return segment_tree[v];
    else if(qr<=mid) return query(2*v, l, mid, ql, qr);
    else if(ql>mid) return query(2*v+1, mid+1, r, ql, qr);
    else return query(2*v, l, mid, ql, qr)+query(2*v+1, mid+1, r, ql, qr);
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
        int i,j,k;
        cin>>n;
        a.assign(n, 0);
        vll temp(n);
        segment_tree.assign(4*(n+1), 0);
        for(i=0;i<n;i++){
            cin>>j;
            temp[i]={j, i};
        }
        sort(temp.begin(), temp.end());
        for(i=0;i<n;i++){
            a[temp[i].second]=i+1;
        }
        // for(i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
        vl first_round(n, 0);
        for(i=n-1;i>=0;i--){
            // cout<<"query_starts"<<endl;
            first_round[i] = query(1, 0, n, 1, a[i]-1);
            // cout<<"query_ends"<<endl;
            update(1, 0, n, a[i], 1);
        }
        for(i=n-1;i>=0;i--){
            update(1, 0, n, a[i], 0);
        }
        ll ans=0;
        for(i=n-1;i>=0;i--){
            ans += query(1, 0, n, 1, a[i]-1);
            update(1, 0, n, a[i], first_round[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}