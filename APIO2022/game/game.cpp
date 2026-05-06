#include "game.h"
#include<bits/stdc++.h>
using namespace std;
int K;//ina[i]为可到达i的最大特殊点，ota[i]为可被i到达的最小特殊点，ina[i] + (i >= k) >  ota[i]则返回1 
vector<int>e[300009],el[300009];
long long st[300009];
void build(int k,int c,int l,int r){
	assert(c < 20);
	if(l < r){
		int m = (l + r) >> 1;
		for(int i = l; i <= m; i ++){
			st[i] |= (1ll << (c << 1));
		}
		for(int i = m + 1; i <= r; i ++){
			st[i] |= (1ll << (c << 1 | 1));
		}
		build(k << 1,c + 1,l,m);
		build(k << 1 | 1,c + 1,m + 1,r);
	}
	else{
		st[l] |= (1ll << (c << 1));
		st[l] |= (1ll << (c << 1 | 1));
	//	printf("%d %d %d\n",k,l,(st[l] >> (c << 1)) & 3);
	}
}
queue<int>q[20];
int add(int k,int c,int l,int r,int u,int v){
//	printf("%d %d %d %d %d %d %d\n",k,l,r,u,v,(st[u] >> (c << 1)) & 3,(st[v] >> (c << 1)) & 3);
	int m = (l + r) >> 1;
	if(((st[v] >> (c << 1)) & 1) && ((st[u] >> (c << 1 | 1)) & 1))
		return 1;
	if(((st[v] >> (c << 1)) & 1)){
		if(!((st[u] >> (c << 1)) & 1)){
			q[c].push(u);
			while(!q[c].empty()){
				int d = q[c].front();
				q[c].pop();
		//	printf("%d %d %d\n",k,1,d);
				st[d] |= (1ll << (c << 1));
				for(unsigned i = 0; i < el[d].size(); i ++){
					if((st[d] ^ st[el[d][i]]) & ((1ll << (c << 1)) - 1))
						continue;
					if((l < r && add(k << 1,c + 1,l,m,el[d][i],d)))
						return 1;
					if(!((st[el[d][i]] >> (c << 1)) & 1))
						q[c].push(el[d][i]);
				}
				//printf("%d %d\n",q.empty(),q.front());
			}
		}
		if(l < r && add(k << 1,c + 1,l,m,u,v))
			return 1;
	}
	if(((st[u] >> (c << 1 | 1)) & 1)){
	//	puts("to1");
		if(!((st[v] >> (c << 1 | 1)) & 1)){
			q[c].push(v);
			while(!q[c].empty()){
				int d = q[c].front();
				q[c].pop();
				st[d] |= (1ll << (c << 1 | 1));
		//		printf("%d %d %d %d\n",k,2,d,(st[d] >> (c << 1 | 1)) & 1);
				for(unsigned i = 0; i < e[d].size(); i ++){
					if((st[d] ^ st[e[d][i]]) & ((1ll << (c << 1)) - 1))
						continue;
    				if((l < r && add(k << 1 | 1,c + 1,m + 1,r,d,e[d][i]))){
						return 1;
					}
					if(!((st[e[d][i]] >> (c << 1 | 1)) & 1))
						q[c].push(e[d][i]);
				//	printf("%d %d %d %d\n",k,2,d,e[d][i]);
					
				}
			}
		}
		if(l < r && (add(k << 1 | 1,c + 1,m + 1,r,u,v)))
			return 1;
	}
//	puts("ret0");
	return 0;
}
void init(int n, int k) {
	K = k;
	build(1,0,0,k - 1);
}
int add_teleporter(int u, int v) {
	//printf("add %d %d\n",u,v);
	e[u].emplace_back(v);
	el[v].emplace_back(u);
	if(u == v)
		return u < K;
	int o = add(1,0,0,K - 1,u,v);
	return o;
}
/*
7 12 3
0 2
4 3
6 2
6 6
0 2
1 5
6 3
5 1
6 6
5 1
5 1
1 4
*/
