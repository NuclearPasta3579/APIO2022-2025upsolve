#include "september.h"

#include <bits/stdc++.h>
using namespace std;

int cur[400009],mn[100009],mx[100009],nxt[100009];
void build(int k,int l,int r){
	cur[k] = r;
	if(l < r){
		int m = (l + r) >> 1;
		build(k << 1,l,m);
		build(k << 1 | 1,m + 1,r);
	}
}
void change(int k,int l,int r,int pl,int val){
	if(l > pl || r < pl)
		return;
	cur[k] = max(cur[k],val);
	if(l < r){
		int m = (l + r) >> 1;
		change(k << 1,l,m,pl,val);
		change(k << 1 | 1,m + 1,r,pl,val);
	}
}
int query(int k,int l,int r,int lq,int rq){
	if(l > rq || r < lq)
		return -1;
	if(l >= lq && r <= rq)
		return cur[k];
	int m = (l + r) >> 1;
	return max(query(k << 1,l,m,lq,rq),query(k << 1 | 1,m + 1,r,lq,rq));
}
int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
	mn[0] = mx[0] = N - 1;
	for(int i = 1; i < N; i ++)
		mx[i] = -1,mn[i] = N,nxt[i] = i;
		nxt[0] = 0;
	for(int i = 0; i < M; i ++){
		for(int j = 0; j < N - 1; j ++){
			mx[S[i][j]] = max(mx[S[i][j]],j);
			mn[S[i][j]] = min(mn[S[i][j]],j);
		}
	}
	for(int i = N - 1; i > 0; i --){
		mx[F[i]] = max(mx[F[i]],mx[i]);
	}
	for(int i = 1; i < N; i ++){
		nxt[mn[i]] = max(nxt[mn[i]],mx[i]);
	}
	build(1,0,N - 2);
	for(int i = N - 2; i >= 0; i --){
		nxt[i] = query(1,0,N - 2,i,nxt[i]);
		change(1,0,N - 2,i,nxt[i]);
	}
	int i = 0,cnt = 0;
	while(i < N - 1){
	//	printf("%d %d\n",i,nxt[i] + 1);
		i = nxt[i] + 1;
		cnt ++;
	}
	return cnt;
}
/*
2
3 1
0 0
1 2
5 2
0 0 1 1 
1 2 3 4
4 1 2 3
*/
