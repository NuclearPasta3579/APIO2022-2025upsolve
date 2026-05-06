#include "mars.h"
#include<bits/stdc++.h>
using namespace std;
 

std::string process(std::vector <std::vector<std::string>> a, int i, int j, int k, int n)
{
	while(a[0][0].size() < 100)
		a[0][0] += '0';
	int N = (2 * n + 1);
	if(2 * (n - k - 1) > i && 2 * (n - k - 1) > j)
		return a[0][0];
	else if(2 * (n - k - 1) > i && 2 * (n - k - 1) == j){
		a[0][0][1] = a[0][1][0];
		for(int si = 2; si <= N - j - 1; si ++){
			a[0][0][si] = a[0][2][si - 2];
		}
		a[0][0][N - j] = a[1][0][0];
		a[0][0][N - j + 1] = a[1][1][0];
	//	cout << a[1][0][0] << a[1][1][0] << endl;
		for(int si = N - j + 2; si <= 2 * (N - j) - 1; si ++){
			a[0][0][si] = a[1][2][si - N + j - 2];
		}
		//cerr << i << ' ' << j << ' ' << a[0][0] << endl;
		return a[0][0];
	}
	else if(2 * (n - k - 1) == i && 2 * (n - k - 1) > j){
		a[0][0][1] = a[1][0][0];
		for(int si = 2; si <= N - i - 1; si ++){
			a[0][0][si] = a[2][0][si - 2];
		}
		a[0][0][N - i] = a[0][1][0];
		a[0][0][N - i + 1] = a[1][1][0];
		for(int si = N - i + 2; si <= 2 * (N - i) - 1; si ++){
			a[0][0][si] = a[2][1][si - N + i - 2];
		}
	//	cerr << i << ' ' << j << ' ' << a[0][0] << endl;
		return a[0][0];
	}
	else{
		int cnt = 0;
		unsigned top = 0;
		char las = '0';
		int fsdt = 0;
		unsigned ocnt = cnt;
		unsigned nw = 1;
		int rsi = 1;
		//lambda存并查集
		vector<int>fa(3 * N + 2),sz(3 * N + 2);
		vector<int>l(3 * N + 2),r(3 * N + 2),stk(3 * N + 2);
		for(int i = 0; i <= 3 * N + 1; i ++){
			fa[i] = i,sz[i] = 1;
		} 
		auto fnd = [&fa](auto self,int x) -> int{
		//	printf("%d\n",x);
			return x == fa[x] ? x : fa[x] = self(self,fa[x]);
		};
		auto Union = [&fa,&sz,&fnd,&fsdt](int x,int y) -> void{
			int u = fnd(fnd,x),v = fnd(fnd,y);
			if(u == v)
				return;
			//printf("%d %d\n",u,v);
			fsdt --;
			if(sz[u] > sz[v])
				swap(u,v);
			fa[u] = v;
			sz[v] += sz[u];
		}; 
		//特判第一个 
		if(k == 0){
			for(int si = 0; si < 3; si ++){
				for(int sj = 0; sj < 3; sj ++){
					fa[si * 3 + sj] = si * 3 + sj;
					sz[si * 3 + sj] = 1;
					if(a[si][sj][0] == '1')
						fsdt ++;
				}
			}
		//	puts("OK");
			for(int si = 0; si < 2; si ++){
				for(int sj = 0; sj < 3; sj ++){
					if(a[si][sj][0] == '1' && a[si + 1][sj][0] == '1')
						Union(si * 3 + sj,si * 3 + sj + 3);
				}
			}
		//	puts("OK");
			for(int si = 0; si < 3; si ++){
				for(int sj = 0; sj < 2; sj ++){
					if(a[si][sj][0] == '1' && a[si][sj + 1][0] == '1')
						Union(si * 3 + sj,si * 3 + sj + 1);
				}
			}
		//	puts("OK");
			cnt = 0;
			top = 0;
			las = '0';
			char o = a[2][0][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					fa[cnt + 8] = cnt + 8,sz[cnt + 8] = 1;
			//		puts("bmrg");
					Union(cnt + 8,6);
			//		puts("mrg");
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
		//	puts("OK");
			las = o;
			rsi ++;
			o = a[1][0][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					fa[cnt + 8] = cnt + 8,sz[cnt + 8] = 1;
					Union(cnt + 8,3);
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
		//	puts("OK");
			las = o;
			rsi ++;
			o = a[0][0][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					fa[cnt + 8] = cnt + 8,sz[cnt + 8] = 1;
					Union(cnt + 8,0);
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
			las = o;
			rsi ++;
			o = a[0][1][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					fa[cnt + 8] = cnt + 8,sz[cnt + 8] = 1;
					Union(cnt + 8,1);
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
			las = o;
			rsi ++;
			o = a[0][2][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					fa[cnt + 8] = cnt + 8,sz[cnt + 8] = 1;
					Union(cnt + 8,2);
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
			las = o;
			rsi ++;
		//	puts("OK");
		}
		else{
			//解码
			cnt = 0;
			top = 0;
			las = '0';
			for(int si = 1; si <= (N - j - 2); si ++){
				char o = a[2][1][2 * (N - j) - 4 - si];
			//	printf("%d %d %c\n",si,2 * (N - j) - 4 - si,o);
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						r[cnt] = l[cnt] = si;
					}
					else
						r[cnt] = si;
				}
				las = o;
			}
			for(int si = N - j - 1; si <= 2 * (N - j) - 5; si ++){
				char o = a[1][2][si - (N - j - 2) + (N - j - 2)];
			//	printf("%d %d %c\n",si,si - (N - j - 2) + (N - j - 2),o);
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						r[cnt] = l[cnt] = si;
					}
					else
						r[cnt] = si;
				}
				las = o;
			}
			top = 0;
			for(int i = 1; i <= cnt; i ++){
				char o1 = a[2][2][i * 2 - 2],o2 = a[2][2][i * 2 - 1];
				if(o1 == '1'){//右括号
					assert(top > 0);
					Union(i,stk[top]);
					top --; 
				}
				if(o2 == '1'){//左括号
					stk[++top] = i; 
				}
			}
			fsdt = 0;
			for(int si = 99; si >= 2 * cnt; si --){
				fsdt = fsdt * 2 + (a[2][2][si] - '0');
			}
			//printf("%d\n",fsdt);
			//合并
			las = '0';
			ocnt = cnt;
			nw = 1;
			rsi = 1;
			for(; rsi <= N - j - 2; rsi ++){
				if(nw <= ocnt && r[nw] < rsi)
					nw ++;
				//printf("%d %d\n",rsi,nw);
				char o = a[2][1][(N - j - 2) - rsi];
				//printf("%d %d %c\n",rsi,(N - j - 2) - rsi,o);
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						fsdt ++;
						r[cnt] = l[cnt] = rsi;
					}
					else
						r[cnt] = rsi;
					if(nw <= ocnt && l[nw] <= rsi)
						Union(cnt,nw);
				}
				las = o;
			}
			//printf("%d\n",fsdt);
			char o = a[1][1][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
			las = o;
			rsi ++;
			for(; rsi <= N - j - 3 + N - j; rsi ++){
				if(nw <= ocnt && r[nw] < rsi - 2)
					nw ++;
				//printf("%d %d %d %d\n",rsi,cnt,nw,l[nw] < rsi - 1);
				char o = a[1][2][rsi - (N - j)];
				//printf("%d %d %c\n",rsi,rsi - (N - j),o);
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						fsdt ++;
						r[cnt] = l[cnt] = rsi;
					}
					else
						r[cnt] = rsi;
					if(nw <= ocnt && l[nw] < rsi - 1)
						Union(cnt,nw);
				}
				las = o;
			}
		//	printf("%d\n",fsdt);
				
			las = '0';
			nw = ocnt + 1;
			ocnt = cnt;
			rsi = 1;
			for(; rsi <= N - j - 2; rsi ++){
				if(nw <= ocnt && r[nw] < rsi)
					nw ++;
				char o = a[2][0][(N - j - 2) - rsi];
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						fsdt ++;
						r[cnt] = l[cnt] = rsi;
					}
					else
						r[cnt] = rsi;
					if(nw <= ocnt && l[nw] <= rsi)
						Union(cnt,nw);
				}
				las = o;
			}
			o = a[1][0][0];
			if(nw <= ocnt && r[nw] < rsi)
				nw ++;
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
				if(nw <= ocnt && l[nw] <= rsi)
					Union(cnt,nw);
			}
			las = o;
			rsi ++; 
			o = a[0][0][0];
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
			}
			las = o;
			rsi ++;
			o = a[0][1][0];
			if(nw <= ocnt && r[nw] < rsi - 2)
				nw ++;
			if(o == '1'){
				if(las == '0'){
					cnt ++;
					fsdt ++;
					r[cnt] = l[cnt] = rsi;
				}
				else
					r[cnt] = rsi;
				if(nw <= ocnt && l[nw] < rsi - 1)
					Union(cnt,nw);
			}
			las = o;
			rsi ++;
			for(; rsi <= N - j - 1 + N - j; rsi ++){
				if(nw <= ocnt && r[nw] < rsi - 2)
					nw ++;
				char o = a[0][2][rsi - (N - j) - 2];
			//	printf("%d %d %c\n",rsi,rsi - (N - j) - 2,o);
				if(o == '1'){
					if(las == '0'){
						cnt ++;
						fsdt ++;
						r[cnt] = l[cnt] = rsi;
					}
					else
						r[cnt] = rsi;
					if(nw <= ocnt && l[nw] < rsi - 1)
						Union(cnt,nw);
				}
				las = o;
			}
		}
		//重编码 
		int snw = 0,p = 0;
		if(i > 0 && k > 0){
			top = 0;
			for(int si = 0; si <= 99; si ++)
				a[0][0][si] = '0';
			for(int si = ocnt + 1; si <= cnt; si ++){
				for(int sj = si + 1; sj <= cnt; sj ++){
					if(fnd(fnd,si) == fnd(fnd,sj)){
						a[0][0][(si - ocnt) * 2 - 1] = '1';
						a[0][0][(sj - ocnt) * 2 - 2] = '1';
						break;
					}
				}
			}
			snw = 2 * (cnt - ocnt);
		}
		else if(i > 0){
			top = 0;
			for(int si = 0; si <= 99; si ++)
				a[0][0][si] = '0';
			for(int si = 1; si <= cnt; si ++){
				for(int sj = si + 1; sj <= cnt; sj ++){
					if(fnd(fnd,si + 8) == fnd(fnd,sj + 8)){
						a[0][0][(si) * 2 - 1] = '1';
						a[0][0][(sj) * 2 - 2] = '1';
						break;
					}
				}
			}
			snw = 2 * (cnt);
		}
	//	puts("OK");
		for(;snw < 100; snw ++,p ++){
		//	printf("%d %d\n",snw,p);
			a[0][0][snw] = p <= 12 ? ((fsdt >> p) & 1) ^ 48 : '0';
		//	puts("OK");
		}
	//	puts("OK");
	//	cerr << i << ' ' << j << ' ' << a[0][0] << endl;
		return a[0][0];
	}
}
/*
3
2
1 1 0 1 1
1 1 0 0 0
1 0 1 1 1
0 1 0 0 0
0 1 1 1 1
3
1 0 1 1 1 1 0
0 1 0 1 0 1 0
1 0 1 0 1 1 1
0 1 1 0 1 0 1
1 0 1 1 0 0 1
1 1 0 0 0 0 1
0 1 1 1 1 1 1
3
0 0 0 1 1 1 0
0 1 0 0 0 1 0
1 1 1 1 1 0 1
0 1 1 1 0 0 0
0 0 0 1 0 0 1
1 0 0 1 1 0 1
1 0 1 0 0 1 1

4
5
6
*/
