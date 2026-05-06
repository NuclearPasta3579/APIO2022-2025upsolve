#include <bits/stdc++.h>
#include "Bob.h"

const __int128 I = 1;

// you may define some global variables, but it does not work if you try to transfer any information from function Alice() to function Bob() through these variables.
// you had better not use the same global variables in function Alice() and in function Bob().
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(b == 0){
		x = 1,y = 0;
		return a;
	}
	long long d = exgcd(b,a % b,y,x);
	y -= a / b * x;
	return d;
}
long long Bob(std::vector<std::pair<int,int>> V){
	// add your code here
	long long na = 1,nb = 0;
	for(unsigned i = 0; i < V.size(); i ++){
		long long at,bt;
		long long ft = (V[i].second - 1) / exgcd(na,V[i].second - 1,at,bt);
		for(int j = 0; j < ft; j ++){
			if((nb + I * j * na) % (V[i].second - 1) == V[i].first - 1){
				nb = (long long)((nb + I * j * na) % (I * ft * na));
				if(na > (1000000000000000000ll) / ft)
					return nb;
				else
					na *= ft;
				break;
			}
		}
		//printf("%lld %lld\n",na,nb);
	}
    return nb; // change this into your code
}
