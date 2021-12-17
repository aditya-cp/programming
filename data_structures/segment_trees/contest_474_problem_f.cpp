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

// https://codeforces.com/contest/474/problem/F
struct ele{
    int gcd, count;
};
int __gcd(int a, int b)
{
    if (b == 0)
        return a;
    return __gcd(b, a % b);
     
}
vector<ele>segment_tree;
vi a;
int n;
ele merge(ele left, ele right){
    int g = __gcd(left.gcd, right.gcd);
    int count = 0;
    if(left.gcd == g) count+=left.count;
    if(right.gcd == g) count+=right.count;
    return (ele){.gcd = g, .count = count};
}
void insert(int v, int l, int r, int index, ele val){
    if(l==r) segment_tree[v] = val;
    else{
        int mid = (l+r)/2;
        if(index<=mid) insert(2*v, l, mid, index, val);
        else insert(2*v+1, mid+1, r, index, val);
        segment_tree[v] = merge(segment_tree[2*v], segment_tree[2*v+1]);
    }
}
ele query(int v, int l, int r, int ql, int qr){
    int mid = (l+r)/2;
    if(l>=ql && r<=qr) return segment_tree[v];
    else if(qr<=mid) return query(2*v, l, mid, ql, qr);
    else if(ql>mid) return query(2*v+1, mid+1, r, ql, qr);
    else return merge(query(2*v, l, mid, ql, qr), query(2*v+1, mid+1, r, ql, qr));
}
ele getEle(int gcd, int count){
    ele t;
    t.count = count;
    t.gcd = gcd;
    return t;
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
        segment_tree.assign(4*n, getEle(0, 0));
        a.assign(n, 0);
        for(i=0;i<n;i++){
            cin>>a[i];
            insert(1, 0, n-1, i, getEle(a[i], 1));
        }
        int m;
        cin>>m;
        while(m--){
            cin>>i>>j;
            cout<<(j-i+1)-query(1, 0, n-1, i-1, j-1).count<<endl;
        }

    }
    return 0;
}