#include <iostream> 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;
//ofstream cout("data.in");
int n,x,y;
int main()
{	
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	srand(time(0));
	n = rand()%10+2;
	cout << n << '\n';
	for(int i=0;i<n;i++){
		x = rand()%100 - 50;
		y = rand()%100 - 50;
		cout << x << ' ' << y << '\n';
	}
}
