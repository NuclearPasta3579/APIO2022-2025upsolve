#include <bits/stdc++.h>
#include "Alice.h"

// you may define some global variables, but it does not work if you try to transfer any information from function Alice() to function Bob() through these variables.
// you had better not use the same global variables in function Alice() and in function Bob().
long long setN(int n);
std::vector<std::pair<int,int>> Alice(){
	// add your code here
	
	// change below into your code
    long long x = setN(5000);
    std :: vector<std :: pair<int,int> >ret;
    ret.emplace_back(std :: make_pair(1,2));
    for(long long i = 2; i <= 4999; i ++){
    	ret.emplace_back(std :: make_pair(x % i + 1,i + 1));
	}
	return ret;
}
/*
2
23 15
1 2
2 3
1 4
4 5
4 6
4 7
4 8
4 9
4 10
4 16
4 17
4 19
4 21
4 22
4 23
*/
