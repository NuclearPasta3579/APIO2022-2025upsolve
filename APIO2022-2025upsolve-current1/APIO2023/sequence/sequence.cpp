#include "sequence.h"

#include <bits/stdc++.h>
using namespace std;
int a[500009],seg1[2000009],tag1[2000009],seg2[2000009],tag2[2000009],seg3[2000009],tag3[2000009],seg4[2000009],tag4[2000009];
vector<int>v[500009];
//线段树统一求最大值，需要最小值时取相反数 
void add(int k,int l,int r,int lq,int val,int *seg,int *tag){
	if(r < lq)
		return;
	if(l >= lq)
		seg[k] += val,tag[k] += val;
	else{
		int m = (l + r) >> 1;
		tag[k << 1] += tag[k],seg[k << 1] += tag[k];
		tag[k << 1 | 1] += tag[k],seg[k << 1 | 1] += tag[k];
		tag[k] = 0;
		add(k << 1,l,m,lq,val,seg,tag);
		add(k << 1 | 1,m + 1,r,lq,val,seg,tag);
		seg[k] = max(seg[k << 1],seg[k << 1 | 1]);
	}
}
int query(int k,int l,int r,int lq,int rq,int *seg,int *tag){
//	printf("%d %d %d %d %d\n",k,l,r,lq,rq);
	if(l > rq || r < lq)
		return ~0x3f3f3f3f;
	if(l >= lq && r <= rq){
//		puts("ret");
		return seg[k];
	} 
	int m = (l + r) >> 1;
	tag[k << 1] += tag[k],seg[k << 1] += tag[k];
	tag[k << 1 | 1] += tag[k],seg[k << 1 | 1] += tag[k];
	tag[k] = 0;
	return max(query(k << 1,l,m,lq,rq,seg,tag),query(k << 1 | 1,m + 1,r,lq,rq,seg,tag));
}
int bit[1000009];
void addbit(int pl,int val){
	for(int i = pl; i <= 1000005 && bit[i] > val; i += i & (-i)){
		bit[i] = val;
	}
}
void clrbit(int pl){
	for(int i = pl; i <= 1000005; i += i & (-i)){
		bit[i] = 0x3f3f3f3f;
	}
}
int querybit(int pl){
	int ans = 0x3f3f3f3f;
	for(int i = pl; i > 0; i &= (i - 1)){
		ans = min(ans,bit[i]);
	}
	return ans;
}
struct node{
	int x,y,tp,id;
	node(int _x = 0,int _y = 0,int _tp = 0,int _id = 0):
		x(_x),y(_y),tp(_tp),id(_id){}
	bool operator<(const node &b)const{
		return x < b.x || (x == b.x && (y < b.y || (y == b.y && tp < b.tp)));
	}
}nd[1000009];
int sequence(int N, std::vector<int> A) {
	memset(bit,0x3f,sizeof(bit));
	add(1,0,N,0,500001,seg1,tag1);
	add(1,0,N,0,-500001,seg2,tag2);
	add(1,0,N,0,500001,seg3,tag3);
	add(1,0,N,0,-500001,seg4,tag4);
	for(int i = 0; i < N; i ++){
		a[i + 1] = A[i];
	}
	for(int i = 1; i <= N; i ++){
		add(1,0,N,i,1,seg1,tag1);
		add(1,0,N,i,-1,seg2,tag2);
		add(1,0,N,i,-1,seg3,tag3);
		add(1,0,N,i,1,seg4,tag4);
		v[a[i]].emplace_back(i);
	}
	int ans = 0;
	for(int i = 1; i <= N; i ++){
	//	printf("%d\n",i);
		for(unsigned j = 0; j < v[i].size(); j ++){
			add(1,0,N,v[i][j],2,seg3,tag3);
			add(1,0,N,v[i][j],-2,seg4,tag4);
		}
		if((int)v[i].size() > ans){
		//	printf("%d\n",(int)v[i].size());
			int las = N + 1,cnt = 0;
			for(unsigned j = v[i].size() - 1; j < v[i].size(); j --){
				int o1 = query(1,0,N,v[i][j],las - 1,seg1,tag1),o2 = -query(1,0,N,v[i][j],las - 1,seg2,tag2),o3 = query(1,0,N,v[i][j],las - 1,seg3,tag3),o4 = -query(1,0,N,v[i][j],las - 1,seg4,tag4);
			//	printf("%d\n",cnt);
				nd[++cnt] = node(o2,o4,1,j + 1);
				nd[++cnt] = node(o1,o3,2,j + 1);
				las = v[i][j];
			}
			int o1 = query(1,0,N,0,las - 1,seg1,tag1),o2 = -query(1,0,N,0,las - 1,seg2,tag2),o3 = query(1,0,N,0,las - 1,seg3,tag3),o4 = -query(1,0,N,0,las - 1,seg4,tag4);
		//	printf("%d\n",cnt);
			nd[++cnt] = node(o2,o4,1,0);
			nd[++cnt] = node(o1,o3,2,0);
		//	puts("OK");
			sort(nd + 1,nd + cnt + 1);
		///	puts("OK");
			for(int j = 1; j <= cnt; j ++){
				if(nd[j].tp == 1)
					addbit(nd[j].y,nd[j].id);
				else{
				//	printf("%d %d %d\n",i,nd[j].id,querybit(nd[j].y));
					ans = max(ans,nd[j].id - querybit(nd[j].y));
				}
			}
			for(int j = 1; j <= cnt; j ++){
				if(nd[j].tp == 1)
					clrbit(nd[j].y);
			}
		}
		for(unsigned j = 0; j < v[i].size(); j ++){
			add(1,0,N,v[i][j],2,seg2,tag2);
			add(1,0,N,v[i][j],-2,seg1,tag1);
		}
	}
	return ans;
}
