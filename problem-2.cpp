#include<iostream>
#include<vector>
using namespace std;
 
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin) ;
    freopen("output.txt", "w", stdout) ;
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ; cout.tie(NULL) ;
    int i,j,n,k;
    cin>>n>>k;
    vector<int>l,r,l_r;
    for(i=0;i<n;i++){
        int t,x,y;
        cin>>t>>x>>y;
        if(x==1&&y==1)l_r.push_back(t);
        else if(x==1&&y==0)l.push_back(t);
        else if(x==0 && y==1)r.push_back(t);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    sort(l_r.begin(),l_r.end());
    int p=0,q=0,s=0;
    int lc=0,rc=0, sum=0;
    while((lc < k || rc < k) && (p<l_r.size() || (q<l.size() && s< r.size())) ){
        if(p<l_r.size() && (q<l.size() && s< r.size())) {
            if(l_r[p] < l[q]+r[s]){sum+=l_r[p];p++;}
            else {sum+=l[q]+r[s];q++;s++;}
            lc++;rc++;
        }else if(p<l_r.size()){
            sum+=l_r[p];rc++;lc++;p++;
        }else{
            sum+=l[q]+r[s];q++;s++;lc++;rc++;
        }
    }
    if(lc==k&&rc==k)cout<<sum<<endl;
    else cout<<-1<<endl;
    return 0;
}