#include<bits/stdc++.h>
#define make_pair mp
using namespace std ;

typedef long long ll ;

/*
 * ģ���˻��㷨���TSP
 * ���룬��ĸ���n,�ߵ�����m
 * ������m��ÿ����3����u,v,s����ʾ��u,v֮����һ������Ϊs��˫���
 * һ���tsp�����������ɴ��
 */
int g[2000][2000] ;
int ans[10000] ;
void Init(int n){
	for(int i =1 ;i<=n ;i++){
		ans[i] = i ;
	}
}
int main()
{
	int n,m;
	srand((unsigned)time(NULL));
	while(cin>>n>>m){
		memset(g,0x3f,sizeof g);
		for(int i = 0 ;i<m ;i++){
			int u,v,w ;

			scanf("%d%d%d",&u,&v,&w);
			g[u][v] = g[v][u] = min(w,g[u][v]);
		}
		//��ʼ��һ��·��
		Init(n);
		double r = 1 ;
		int res = 0;
		double de = 0.99 ;
		for(int i = 1;i<n;i++){
			res += g[ans[i]][ans[i+1]];
		}
		res+=g[ans[n]][ans[1]];
		cout<<res<<endl;
		while(r >1e-18){
			//cout<<r<<endl;
			int len = 0 ;
			int x = rand()%n+1 ;
			int y = rand()%n ;
			swap(ans[x],ans[y]);
			for(int i=1;i<n;i++){
				len+= g[ans[i]][ans[i+1]];
			}
			len+=g[ans[n]][ans[1]];
			if(len<res){
				res = len ;
				r = r*de ;
				continue ;
			}
			else{
				double ac = ((double)rand()/RAND_MAX)  ;
				//exp�еĲ�ֵ���Ǹ���
				if(exp((res-len)/r )> ac){
					//�����ƶ�
					res = len ;
				}
				else{
					//�������ƶ����˻�ԭ��
					swap(ans[x],ans[y]);
				}
				r = r*de ;
			}
		}
		cout<<res<<endl;
		for(int i = 1 ;i<=n ;i++){
            cout<<ans[i]<<" ";
		}
		cout<<endl;
	}

	return 0 ;
}

/*

6
15
1 2 56
1 3 35
1 4 21
1 5 51
1 6 60
2 3 21
2 4 57
2 5 78
2 6 70
3 4 36
3 5 68
3 6 68
4 5 51
4 6 61
5 6 13
*/
