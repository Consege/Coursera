#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int n,m;
    //ÂÒÊäÒ»¸öÊý
    cin>>n>>m;
    int cur[10]={0,5,1,2,3,4,6,5};
    int d[10][10] ;
    memset(d,0x3f,sizeof d);
    for(int i = 0 ;i<m ;i++){
        int u ,v ,w ;
        cin>>u>>v>>w ;
        d[u][v] = d[v][u] =  min(w,d[u][v]) ;
    }
    int flag = 1;
    while(flag){
        flag = 0 ;
        for(int u = 1;u<n;u++){
            for(int v = u+1;v<=n;v++){
                if(d[cur[u]][cur[u+1]]+d[cur[v]][cur[v+1]] > d[cur[u]][cur[v]]+d[cur[u+1]][cur[v+1]]){
                    cout<<u<<" "<<v<<endl;
                    swap(cur[u+1],cur[v]) ;
                    for(int i = 1 ;i<=n;i++){
                        cout<<cur[i]<<" ";
                    }
                    cout<<endl ;
                    flag = 1;
                }
            }
        }
    }
    int ans = 0 ;
    for(int i = 1 ;i<=n;i++){
        ans += d[cur[i]][cur[i+1]];
        cout<<cur[i]<<" ";
    }
    cout<<cur[n+1]<<endl;
    cout<<" "<<ans<<endl;
    return 0;
}
