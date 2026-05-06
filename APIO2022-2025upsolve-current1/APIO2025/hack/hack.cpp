//Code Based on solution from Ruiqi Yuan, really easy and can be promoted to other tasks.
/*
Number of collisions is to complex, consider just solve the task when we just check if it's not zero
It's just looks like binary search.
When we tried to check if x \in [l,r],x | n,we thought of 1,l + 1,l + 2,...,r + 1. 
But it's too large, consider that we can just get if x,x + 1,...,x + b exist, then we construct:
1,2,3,...,b,l + b, l + 2b,...,l + db,r + 1.
We've find a way to make it 2\sqrt(r - l + 1).
Just binary search to get n by checking [l,mid].
Approached a lot, but still, furthur approach needed.
We haven't made full use of x[i] \le 10 ^{18}, all multiplies 2 ^ {29}
n = 2^{o}n'
Bruteforce is enough to get o, just have to get n', which can be always not divided by 2.
We tried to find if x,x + 2,x + 4,...,x + 2b;
Construct x[i]/2^{29}:
2,4,6,...,2b,2l + 2b - 1, 2l + 4b - 1,...,2l + 2db - 1,2r + 1.
OK,got it.
*/

#include "hack.h"
#include <bits/stdc++.h>
using namespace std;

int hack();
long long collisions(std::vector<long long> x);

int hack(){
    int l = 0,r = 500000001;
    while(l + 1 < r){
    	int m = (l + r) >> 1;
    	vector<long long>v(0);
    	int o = __builtin_sqrt(m - l);
    	for(int i = 1; i <= o; i ++){
    		v.emplace_back((2ll * i) << 29);
		}
		for(int i = l + 1 + o; i <= m; i += o){
			v.emplace_back((2ll * i - 1) << 29);
		}
		v.emplace_back((2ll * m + 1) << 29);
		if(collisions(v))
			r = m;
		else
			l = m;
	}
	//cerr << 2 * r - 1 << endl;
	long long fr = (2ll * r - 1) << 29;
	while(collisions({1ll,(fr >> 1) + 1}))
		fr = fr >> 1;
//	cerr << fr << endl;
	return (int)fr;
}
