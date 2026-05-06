#include "cyberland.h"

#include <bits/stdc++.h>
using namespace std;

bool bfs[100009];
double dis[8500009];
priority_queue<pair<double,int>>pq;
queue<int>q;
vector<pair<int,int> >e[100009];

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
   	K = min(K,71);
   	for(unsigned i = 0; i < N; i ++)
   		e[i].clear();
    for(int i = 0; i < M; i ++){
    	e[x[i]].emplace_back(make_pair(y[i],c[i]));
    	e[y[i]].emplace_back(make_pair(x[i],c[i]));
	}
	for(int i = 0; i < N; i ++)
		bfs[i] = false;
	q.push(0);
	bfs[0] = true;
	while(!q.empty()){
		int d = q.front();
		q.pop();
		if(d == H)
			continue;
		for(unsigned i = 0; i < e[d].size(); i ++){
			if(!bfs[e[d][i].first]){
				bfs[e[d][i].first] = true;
				q.push(e[d][i].first);
			}
		}
	}
	if(!bfs[H])
		return -1;
	for(int i = 0; i < N * (K + 1); i ++){
		dis[i] = 9e18;
	}
	arr[0] = 0;
	for(int i = 0; i < N; i ++){
		if(arr[i] == 0 && bfs[i]){
			dis[i] = 0.;
			pq.push(make_pair(0.,i));
		}
	}
	double ans = 9e18;
	while(!pq.empty()){
		auto d = pq.top();
		pq.pop();
		//printf("%lf %d\n",-d.first,d.second);
		if(-d.first - 1e-9 > dis[d.second])
			continue;
		int nw = (d.second) / N,v = d.second - nw * N;
		if(v == H){
			ans = min(ans,dis[d.second]);
			continue; 
		} 
		for(unsigned i = 0; i < e[v].size(); i ++){
			double fd = dis[d.second] + e[v][i].second;
			if(fd < dis[e[v][i].first + nw * N]){
				dis[e[v][i].first + nw * N] = fd;
				pq.push(make_pair(-fd,e[v][i].first + nw * N));
				
			}
			if(arr[e[v][i].first] == 2 && nw < K && fd / 2 < dis[e[v][i].first + nw * N + N]){
					dis[e[v][i].first + nw * N + N] = fd / 2;
					pq.push(make_pair(-fd / 2,e[v][i].first + nw * N + N));
				}
		}
	}
	return ans;
}
