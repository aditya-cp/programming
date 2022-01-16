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

// https://codeforces.com/contest/145/problem/E
struct ele{
    int i_s4_e4, i_s4_e7, i_s7;
    int d_s4, d_s7_e7, d_s7_e4;
    int invertChilds;
};
int n;
vector<ele> segment_tree;
vi a;
int answer(int v){
    return max(segment_tree[v].i_s4_e4, max(segment_tree[v].i_s4_e7, segment_tree[v].i_s7));
}
void invertVertex(int v){
    ele a = segment_tree[v];
    segment_tree[v].d_s4 = a.i_s7;
    segment_tree[v].i_s7 = a.d_s4;
    segment_tree[v].d_s7_e4 = a.i_s4_e7;
    segment_tree[v].d_s7_e7 = a.i_s4_e4;
    segment_tree[v].i_s4_e4 = a.d_s7_e7;
    segment_tree[v].i_s4_e7 = a.d_s7_e4;
    segment_tree[v].invertChilds= (segment_tree[v].invertChilds+1)%2;
}
void propagate(int v){
    if(segment_tree[v].invertChilds){
        invertVertex(2*v);
        invertVertex(2*v+1);
        segment_tree[v].invertChilds = 0;
    }
}
void mergeForVertex(int v){
    ele a;
    a.invertChilds = 0;
    a.i_s4_e4 = segment_tree[2*v].i_s4_e4+segment_tree[2*v+1].i_s4_e4;
    a.i_s4_e7 = max(segment_tree[2*v].i_s4_e4+
    max(segment_tree[2*v+1].i_s4_e7, segment_tree[2*v+1].i_s7), segment_tree[2*v].i_s4_e7+segment_tree[2*v+1].i_s7);
    a.i_s7 = segment_tree[2*v].i_s7+segment_tree[2*v+1].i_s7;

    a.d_s4 = segment_tree[2*v].d_s4+segment_tree[2*v+1].d_s4;
    a.d_s7_e7 = segment_tree[2*v].d_s7_e7+segment_tree[2*v+1].d_s7_e7;
    a.d_s7_e4= max(segment_tree[2*v].d_s7_e4+ segment_tree[2*v+1].d_s4, 
    segment_tree[2*v].d_s7_e7+max(segment_tree[2*v+1].d_s7_e4, segment_tree[2*v+1].d_s4));
    segment_tree[v] = a;
}
void buildSegmentTree(int v, int vl, int vr){
    if(vl == vr){
        if(a[vl]==4){
            segment_tree[v].i_s4_e4=1;
            segment_tree[v].i_s4_e7=0;
            segment_tree[v].i_s7=0;
            segment_tree[v].d_s4=1;
            segment_tree[v].d_s7_e4=0;
            segment_tree[v].d_s7_e7=0;
            segment_tree[v].invertChilds = 0;
        }else{
            segment_tree[v].i_s4_e4=0;
            segment_tree[v].i_s4_e7=0;
            segment_tree[v].i_s7=1;
            segment_tree[v].d_s4=0;
            segment_tree[v].d_s7_e4=0;
            segment_tree[v].d_s7_e7=1;
            segment_tree[v].invertChilds = 0;
        }
        return;
    }

    int mid = (vl+vr)/2;
    buildSegmentTree(2*v, vl, mid);
    buildSegmentTree(2*v+1, mid+1, vr);
    mergeForVertex(v);
}
void switchPositions(int v, int vl, int vr, int ql, int qr){
    if(vl == vr){
        invertVertex(v);
        segment_tree[v].invertChilds = 0;
        return;
    }
    int mid = (vl+vr)/2;
    propagate(v);
    if(vl>=ql && vr<=qr){
        invertVertex(v); return;
    }else if(qr<=mid){
        switchPositions(2*v, vl, mid, ql, qr);
    }else if(ql>mid){
        switchPositions(2*v+1, mid+1, vr, ql, qr);
    }else{
        switchPositions(2*v, vl, mid, ql, qr);
        switchPositions(2*v+1, mid+1, vr, ql, qr);
    }

    mergeForVertex(v);
}

void print(ele a){
    // cout<<"i_s4_e4="<<a.i_s4_e4<<","<<"i_s4_e7="
    // <<a.i_s4_e7<<",i_s7="<<a.i_s7<<"  ";
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
        int i,j,q;
        cin>>n>>q;
        string s;
        cin>>s;
        a.assign(n, 0);
        ele k;
        k.i_s4_e4 = 0;
        k.i_s4_e7 = 0;
        k.i_s7 = 0;
        k.d_s4 = 0;
        k.d_s7_e4 = 0;
        k.d_s7_e7 = 0;
        segment_tree.assign(4*n, k);
        for(i=0;i<n;i++){
            a[i]=s[i]-'0';
        }
        // for(i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
        buildSegmentTree(1, 0, n-1);
        while(q--){
            int x,y;
            cin>>s;
            if(s=="count"){
                for(int p=1;p<4*n;p++) print(segment_tree[p]);
                cout<<answer(1)<<endl;
            }else{
                cin>>x>>y;
                x--;y--;
                switchPositions(1, 0, n-1, x, y);
            }
        }
    }
    return 0;
}