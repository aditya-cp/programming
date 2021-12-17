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

// https://codeforces.com/contest/380/problem/C
struct ele{
    int ans, l, r;
};
vector<ele>segment_tree;
int n;
string s;
ele merge(ele left, ele right){
    int ans = left.ans + right.ans;
    int addition = min(left.l, right.r);
    int l = right.l - addition + left.l;
    int r = left.r - addition + right.r;
    ele result;
    result.ans = ans+addition;
    result.l = l;
    result.r = r;
    return result;
}
void insert(int v, int l, int r, int index, ele val){
    if(l==r)segment_tree[v]=val;
    else {
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
void printEle(ele t){
    cout<<"ans: "<<t.ans<<", l: "<<t.l<<", r: "<<t.r;
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
        int i,j,k,m;
        cin>>s;
        n=s.length();
        segment_tree.assign(4*n, (ele){.ans = 0, .l = 0, .r = 0});
        for(i=0;i<n;i++){
            ele t;
            t.ans = 0;
            t.l = s[i] == '(' ? 1: 0;
            t.r = s[i] ==')' ? 1: 0;
            insert(1, 0, n-1, i, t);
        }
        // for(i=1;i<4*n;i++) {
        //     printEle(segment_tree[i]);
        //     cout<<" => ";
        // }
        // cout<<endl;
        cin>>m;
        while(m--){
            cin>>i>>j;
            cout<<2*query(1, 0, n-1, i-1, j-1).ans<<endl;
        }
    }
    return 0;
}