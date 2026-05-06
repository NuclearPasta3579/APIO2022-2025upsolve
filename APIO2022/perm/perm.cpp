#include "perm.h"
#include<bits/stdc++.h>
using namespace std;
int x = -1,y = 0;
vector<int>v;
int cnt; 
bool fp[65];
std::vector<int> construct_permutation(long long k)
{
	v.clear();
	long long s = k;
	cnt = 0;
	while(s){
		fp[++cnt] = s & 1;
		s = s >> 1;
	}
	x = -1,y = 0;
	int fr = -1,se = -1;
	auto chan = [&fr,&se](int x) -> void{
		if(se == -1 || v[x] < v[se]){
			se = x;
			if(fr == -1 || v[fr] > v[se])
				swap(fr,se);
		}
	};
	for(int i = cnt - 1; i > 0; i --){
		x ++;
		v.emplace_back(x);
		chan(v.size() - 1);
		if(fp[i]){
			if(i > 1 && fp[i - 1] && se != -1 && fr > se){
				x ++;
				v.emplace_back(x);
				chan(v.size() - 1);
				y --;
				v[fr] --;
				v[se] --;
				v.emplace_back(v[se] + 1);
				i --;
			}
			else
				y --,v.emplace_back(y),chan(v.size() - 1);
		}
	}
	for(int i = 0; i < v.size(); i ++){
		v[i] -= y;
	//	printf("%d\n",v[i]);
	}
	return v;
}
