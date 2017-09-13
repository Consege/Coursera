#include <bits/stdc++.h>
#define pb push_back
#define sz(x) x.size()
#define mp make_pair
#define FI first
#define SE second
using namespace std ;
int g[2000][2000] ;

bool cmp(pair<vector<int>,int> a ,pair<vector<int>,int> b)
{
    return a.SE<b.SE ;
}
int main()
{
    int t = 10;
    srand((unsigned)time(NULL));
    int n,m;
    while(cin>>n>>m){

            memset(g,0x3f,sizeof g);
            for(int i = 0 ;i<m ;i++){
                int u,v,w ;
                scanf("%d%d%d",&u,&v,&w);
                g[u][v] = g[v][u] = min(w,g[u][v]);
            }
        while(t--){
            int num[1000];
            for(int i = 0 ;i<n ;i++){
                num[i] = i +1;
            }
            pair<vector<int>,int> ans[1000] ;
            //生成10*n个初始序列
            int cnt =  1;
            do{
                double r = (rand()%n)/(1.0*n) ;
                if(r<0.3){
                    ans[cnt].FI.pb(0) ;
                    for(int j=0;j<n;j++){
                        ans[cnt].FI.pb(num[j]) ;
                    }
                    ans[cnt].FI.pb(num[0]);
                    cnt++;
                }
                if(cnt==10*n+1){
                    break ;
                }
            }while(next_permutation(num,num+n));
            cout<<cnt<<endl;
            //改良圈产生初始染色体
            for(int i =1 ;i<=10*n;i++){
                int flag = 1;
                while(flag){
                    flag = 0 ;
                    for(int u = 1;u<sz(ans[i].FI)-2;u++){
                        for(int v = u+1;v<=sz(ans[i].FI)-2;v++){
                            if(g[(ans[i].FI)[u]][(ans[i].FI)[u+1]]+g[(ans[i].FI)[v]][(ans[i].FI)[v+1]] > g[(ans[i].FI)[u]][(ans[i].FI)[v]]+g[(ans[i].FI)[u+1]][(ans[i].FI)[v+1]]){
                                swap((ans[i].FI)[u+1],(ans[i].FI)[v]) ;
                                flag = 1;
                            }
                        }
                    }
                }
            }
            //cout<<1<<endl;
            //算法遗传100代
            //交叉
            //先将染色体按照适应度排序
            double hundun1 = (rand()%n)/(1.0*n) ;
            double hundun2 = (rand()%n)/(1.0*n) ;
            for(int i = 1 ;i<=100 ;i++){

                for(int j = 1 ;j<=10*n ;j++){
                    int len  = 0 ;
                    for(int k = 1 ; k<sz(ans[j].FI)-1;k++){
                        len+=g[(ans[j].FI)[k]][(ans[j].FI)[k+1]];
                    }
                    ans[j].SE = len ;
                }
                sort(ans+1,ans+10*n+1,cmp);
                //cout<<ans[1].SE<<endl;
                //cout<<ans[1].SE<<endl;
                //将交叉点1和交叉点2之间的基因交换
                //如果有n个点，则交叉点应该在2~n
                int jiaochadian1 = hundun1*(n-1)+2 ;
                int jiaochadian2 = hundun2*(n-1)+2 ;
                for(int j = 1 ;j<=10*n ;j++){
                    ans[10*n+j] = ans[j];
                }
                for(int j = 1 ;j<=10*n;j+=2){
                   // cout<<j<<endl;
                    if(jiaochadian2<jiaochadian1){
                        swap(jiaochadian1,jiaochadian2) ;
                    }
                    //cout<<jiaochadian1<<" "<<jiaochadian2<<endl;
                    for(int k = jiaochadian1;k<=jiaochadian2;k++){
                        int l1 ;
                        for(l1 = 2 ; l1<sz(ans[10*n+j].FI);l1++){
                            if((ans[10*n+j].FI)[l1] == (ans[10*n+j+1].FI)[k]){
                                break ;
                            }
                        }
                        if(l1 == sz(ans[10*n+j].FI)-1){
                            continue ;
                        }
                      //  cout<<"l1 "<<l1<<endl;
                        int x = (ans[10*n+j].FI)[l1] ;
                        swap((ans[10*n+j].FI)[l1],(ans[10*n+j].FI)[k]) ;
                        int l2 ;
                        for(l2 = 2 ;l2<sz(ans[10*n+j+1].FI) ; l2++){
                            if((ans[10*n+j+1].FI)[l2] == x ){
                                break ;
                            }
                        }
                        if(l2 == sz(ans[10*n+j+1].FI)-1){
                            continue ;
                        }
                    //    cout<<"l2 "<<l2<<endl;
                        swap((ans[10*n+j+1].FI)[l2],(ans[10*n+j+1].FI)[k]);
                    }
                }
                //变异

                //交换变异点上的基因
                double bianyilv = 0.1 ;
                for(int j = 1 ;j<= 20*n ;j++){
                    double aaa = (rand()%n)/(1.0*n);
                    if(aaa>bianyilv){
                        int bianyidian1 = (rand()%n)/(1.0*n) * (n-1)+2 ;
                        int bianyidian2 = (rand()%n)/(1.0*n) * (n-1)+2 ;
                        //cout<<bianyidian1<<" "<<bianyidian2<<endl;
                        swap((ans[j].FI)[bianyidian1] , (ans[j].FI)[bianyidian2]) ;
                    }
                }
                //选择
                for(int j = 1 ;j<=20*n ;j++){
                    int len  = 0 ;
                    for(int k = 1 ; k<sz(ans[j].FI)-1;k++){
                        len+=g[(ans[j].FI)[k]][(ans[j].FI)[k+1]];
                    }
                    ans[j].SE = len ;
                }
                sort(ans+1,ans+20*n+1,cmp) ;
                //更新混沌值
                hundun1 = hundun1*4*(1-hundun1) ;
                hundun2 = hundun2*4*(1-hundun2) ;
            }
            for(int j = 1 ;j<=20*n ;j++){
                    int len  = 0 ;
                    for(int k = 1 ; k<sz(ans[j].FI)-1;k++){
                        len+=g[(ans[j].FI)[k]][(ans[j].FI)[k+1]];
                    }
                    ans[j].SE = len ;
             }
             sort(ans+1,ans+20*n+1,cmp);
             for(int i = 1 ; i<sz(ans[1].FI);i++){
                cout<<(ans[1].FI)[i]<<" ";
             }
             cout<<endl;
             cout<<ans[1].SE<<endl;
        }
    }
    return 0 ;
}

/*
10 45
1 2 8
1 3 5
1 4 9
1 5 12
1 6 14
1 7 12
1 8 16
1 9 17
1 10 22
2 3 9
2 4 15
2 5 17
2 6 8
2 7 11
2 8 18
2 9 14
2 10 22
3 4 7
3 5 9
3 6 11
3 7 7
3 8 12
3 9 12
3 10 17
4 5 3
4 6 17
4 7 10
4 8 7
4 9 15
4 10 18
5 6 8
5 7 10
5 8 6
5 9 15
5 10 15
6 7 9
6 8 14
6 9 8
6 10 16
7 8 8
7 9 6
7 10 11
8 9 11
8 10 11
9 10 10
*/
