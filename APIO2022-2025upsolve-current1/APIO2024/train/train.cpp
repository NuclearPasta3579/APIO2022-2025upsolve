#include "train.h"

#include <bits/stdc++.h>
using namespace std;
struct node{
	int yid,id,tim;
	node(int _yid = 0,int _id = 0,int _tim = 0):
		yid(_yid),id(_id),tim(_tim){}
	bool operator<(const node &b)const{
		return tim < b.tim || (tim == b.tim && (id & 1) > (b.id & 1));
	}
}nd[200009];
const long long INF = 500000000000000ll;
long long dis[200009],wdis[200009];
vector<int>v[100009];
unsigned head[100009],tail[100009];
int lsh[400009],lshcnt,segcnt,tag[4000009],lc[4000009],rc[4000009],root[100009];
unsigned tme[200009];
int add(int k,int l,int r,int rq,int val){
	if(l > rq)
		return k;
	int u = ++segcnt;
	tag[u] = tag[k];
	lc[u] = lc[k],rc[u] = rc[k];
	if(r <= rq)
		tag[u] += val;
	else{
		int m = (l + r) >> 1;
		lc[u] = add(lc[k],l,m,rq,val);
		rc[u] = add(rc[k],m + 1,r,rq,val);
	}
	return u;
}
int query(int k,int l,int r,int pl){
	if(l > pl || r < pl || k == 0)
		return 0;
	int t = tag[k];
	if(l < r){
		int m = (l + r) >> 1;
		t += query(lc[k],l,m,pl) + query(rc[k],m + 1,r,pl);
	}
	return t;
}
long long solve(int N, int M, int W, std::vector<int> T, std::vector<int> X, std::vector<int> Y,
                std::vector<int> A, std::vector<int> B, std::vector<int> C, std::vector<int> L,
                std::vector<int> R) {
    vector<int> ft(0);
    for(int i = 0; i < W; i ++){
    	ft.emplace_back(i);
	}
	sort(ft.begin(),ft.end(),[&R](int x,int y){return R[x] < R[y];});
	//cerr << "stp1" << endl;
	for(int i = 0; i < M; i ++){
		nd[i << 1] = node(X[i],i << 1,A[i]);
		nd[i << 1 | 1] = node(Y[i],i << 1 | 1,B[i]);
		lsh[++lshcnt] = A[i];
		lsh[++lshcnt] = B[i];
		dis[i << 1] = wdis[i << 1] = INF + 1;
		
		dis[i << 1 | 1] = wdis[i << 1 | 1] = INF + 1;
	}
	lsh[++lshcnt] = 0;
	lsh[++lshcnt] = 1000000001;
	for(int i = 0; i < W; i ++){
		lsh[++lshcnt] = L[i] - 1;
	}
	sort(lsh + 1,lsh + lshcnt + 1);
	lshcnt = unique(lsh + 1,lsh + lshcnt + 1) - (lsh + 1);
	for(int i = 0; i < W; i ++){
		int o3 = lower_bound(lsh + 1,lsh + lshcnt + 1,L[ft[i]] - 1) - lsh;
		root[i + 1] = add(root[i],1,lshcnt,o3,1);
	}
	nd[2 * M] = node(0,2 * M,0);
	sort(nd,nd + 2 * M + 1);
	for(int i = 0; i < N; i ++){
		head[i] = 1,tail[i] = 0;
		v[i].emplace_back(0x3f3f3f3f);
	}
	wdis[2 * M] = dis[2 * M] = 0;
	unsigned nw = 0;
	long long ans = INF + 1;
	for(int i = 0; i < 2 * M + 1; i ++){
		int o1 = nd[i].yid,o2 = nd[i].id,o3 = nd[i].tim;
		while(nw < ft.size() && R[ft[nw]] < o3){
			nw ++;
		}
		nd[i].tim = lower_bound(lsh + 1,lsh + lshcnt + 1,nd[i].tim) - lsh;
		if(head[o1] <= tail[o1]){
			while(head[o1] < tail[o1] && nw >= tme[nd[v[o1][head[o1] + 1]].id])
				head[o1] ++;
			dis[o2] = min(dis[o2],wdis[nd[v[o1][head[o1]]].id] + 1ll * T[o1] * query(root[nw],1,lshcnt,nd[v[o1][head[o1]]].tim));
		}
		if(o2 & 1){
			wdis[o2] = min(wdis[o2],dis[o2 ^ 1] + C[o2 >> 1]);
			dis[o2] = min(dis[o2],dis[o2 ^ 1] + C[o2 >> 1]);
		}
		if(wdis[o2] <= INF && (tail[o1] < head[o1] || wdis[nd[v[o1][tail[o1]]].id] + 1ll * T[o1] * query(root[W],1,lshcnt,nd[v[o1][tail[o1]]].tim) >= wdis[nd[i].id] + 1ll * T[o1] * query(root[W],1,lshcnt,nd[i].tim))){
			while(head[o1] <= tail[o1] && wdis[nd[v[o1][tail[o1]]].id] + 1ll * query(root[tme[nd[v[o1][tail[o1]]].id]],1,lshcnt,nd[v[o1][tail[o1]]].tim) * T[o1] >= wdis[nd[i].id] + 1ll * query(root[tme[nd[v[o1][tail[o1]]].id]],1,lshcnt,nd[i].tim) * T[o1])
				tail[o1] --;
			tail[o1] ++;
			if(tail[o1] == v[o1].size())
				v[o1].emplace_back(0);
			tme[nd[i].id] = nw;
			if(tail[o1] > head[o1]){
				int l = tme[nd[v[o1][tail[o1] - 1]].id],r = W;
				while(l + 1 < r){
					int m = (l + r) >> 1;
					if(wdis[nd[v[o1][tail[o1] - 1]].id] + 1ll * T[o1] * query(root[m],1,lshcnt,nd[v[o1][tail[o1] - 1]].tim) >= wdis[nd[i].id] + 1ll * T[o1] * query(root[m],1,lshcnt,nd[i].tim))
						r = m;
					else
						l = m;
				} 
				tme[nd[i].id] = r;
			}
			v[o1][tail[o1]] = i;
		}
	//	printf("%d %d %lld %lld\n",o1,o2,dis[o2],wdis[o2]);
	}
	while(nw < ft.size()){
		nw ++;
	}
	int o1 = N - 1;
	if(head[o1] <= tail[o1]){
		while(head[o1] < tail[o1] && nw >= tme[nd[v[o1][head[o1] + 1]].id])
			head[o1] ++;
		ans = min(ans,wdis[nd[v[o1][head[o1]]].id] + 1ll * T[o1] * query(root[nw],1,lshcnt,nd[v[o1][head[o1]]].tim));
	}
	return ans > INF ? -1 : ans;
}
