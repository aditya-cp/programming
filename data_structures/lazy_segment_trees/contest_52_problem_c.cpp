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

// https://codeforces.com/contest/52/problem/C
ll n;
vll segment_tree;
vl a;
void propagate(ll v){
    segment_tree[2*v].first += segment_tree[v].second;
    segment_tree[2*v].second += segment_tree[v].second;
    segment_tree[2*v+1].first += segment_tree[v].second;
    segment_tree[2*v+1].second += segment_tree[v].second;
    segment_tree[v].second = 0;
}
void add(ll v, ll vl, ll vr, ll ql, ll qr, ll val){
    if(vl == vr) {
        segment_tree[v].first=segment_tree[v].first+val;
        segment_tree[v].second = 0;
        return;
    }
    propagate(v);
    ll mid = (vl+vr)/2;
    if(vl>=ql && vr<=qr){
        segment_tree[v] = {segment_tree[v].first+val, val};
    }else if(qr<=mid){
        add(2*v, vl, mid, ql, qr, val);
        segment_tree[v].first = min(segment_tree[2*v].first, segment_tree[2*v+1].first);
    }else if(ql>mid){
        add(2*v+1, mid+1, vr, ql, qr, val);
        segment_tree[v].first = min(segment_tree[2*v].first, segment_tree[2*v+1].first);
    }else{
        add(2*v, vl, mid, ql, qr, val);
        add(2*v+1, mid+1, vr, ql, qr, val);
        segment_tree[v].first = min(segment_tree[2*v].first, segment_tree[2*v+1].first);
    }
}
ll get(ll v, ll vl, ll vr, ll ql, ll qr){
    if(vl == vr) {
        segment_tree[v].second = 0;
        return segment_tree[v].first;
    }
    propagate(v);
    ll mid = (vl+vr)/2;
    if(vl>=ql && vr<=qr){
        return segment_tree[v].first;
    }else if(qr<=mid){
        return get(2*v, vl, mid, ql, qr);
    }else if(ql>mid){
        return get(2*v+1, mid+1, vr, ql, qr);
    }else{
        return min(get(2*v, vl, mid, ql, qr),
        get(2*v+1, mid+1, vr, ql, qr));
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
        ll i,j,q;
        cin>>n;
        a.assign(n, 0);
        segment_tree.assign(4*n, {0, 0});
        for(i=0;i<n;i++){
            cin>>a[i];
            add(1, 0, n-1, i, i, a[i]);
        }
        cin>>q;
        while(q--){
            ll p,q,r;
            cin>>p>>q;
            if(cin.get() == ' '){
                cin>>r;
                if(p>q){
                    add(1, 0, n-1, p, n-1, r);
                    add(1, 0, n-1, 0, q, r);
                }
                else add(1, 0, n-1, p, q,r);
            }else{
                if(p>q){
                    cout<<min(get(1, 0, n-1, p, n-1), get(1, 0, n-1, 0, q))<<endl;
                }else{
                    cout<<get(1, 0, n-1, p, q)<<endl;
                }
            }
        }
    }
    return 0;
}