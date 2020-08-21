#include<bits/stdc++.h>
using namespace std;
long long n;
vector<long long>st;
vector<long long>a;
vector<long long>l;
vector<long long>r;
vector<vector<long long>>range;
long long minn=0;
void setRange(long long index, long long s, long long e){
    range[0][index]=s;
    range[1][index]=e;
    if(s!=e){
        long long mid=(s+e)/2;
        setRange(2*index, s, mid);
        setRange(2*index+1, mid+1, e);
    }
}
void insert(long long s, long long val, long long index){
    if(range[0][index]==s && range[1][index]==s){
        st[index]=val;
        a[index]=val;
        r[index]=val;
        l[index]=val;
    }else if(range[0][index]>s || range[1][index]<s) return;
    else{
        insert(s,val,2*index);
        insert(s,val,2*index+1);
        st[index]=st[2*index]+st[2*index+1];
        l[index]=max(l[2*index],st[2*index]+l[2*index+1]);
        r[index]=max(r[2*index+1],st[2*index+1]+r[2*index]);
        a[index]=max(max(a[2*index], a[2*index+1]), r[2*index]+l[2*index+1]);
    }
}
vector<long long> query(long long s, long long e, long long index){
    vector<long long>ans;
    if(e<range[0][index] || s>range[1][index]){
        ans.push_back(-1);
    }
    else if(range[0][index]>=s&&range[1][index]<=e){
        ans.push_back(index);
        ans.push_back(l[index]);ans.push_back(r[index]);ans.push_back(a[index]);
        ans.push_back(st[index]);
    }
    else{
        ans.push_back(index);
        vector<long long>l1=query(s,e,2*index);
        vector<long long>l2=query(s,e,2*index+1);
        if(l2[0]==-1)swap(l1,l2);
        if(l1[0]==-1){
            l2[0]=index;
            return l2;    
        }
        ans.push_back(max(l1[1], l1[4]+l2[1]));
        ans.push_back(max(l2[2], l2[4]+l1[2]));
        ans.push_back(max(max(l1[3], l2[3]), l1[2]+l2[1]));
        ans.push_back(l1[4]+l2[4]);
    }
    return ans;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(NULL) ;
    long long i,j,q,k;
    // scanf("%lld",&n);
    cin>>n;
    range.assign(2, vector<long long>(4*n+1));
    st.assign(4*n+1, 0);
    a.assign(4*n+1, minn);
    l.assign(4*n+1, minn);
    r.assign(4*n+1, minn);
    setRange(1,0, n-1);
    for(i=0;i<n;i++){
        // scanf("%lld",&j);
        cin>>j;
        insert(i, j, 1);
    }
    // scanf("%lld",&q);
    cin>>q;
    while(q--){
        // scanf("%lld %lld",&i,&j);
        cin>>i>>j;
        printf("%lld\n", query(i-1,j-1,1)[3]);
        // cout<<query(i-1,j-1,1)[3]<<endl;
    }
    return 0;
}