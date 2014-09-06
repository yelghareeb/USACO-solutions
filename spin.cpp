/*
ID: c.eng_j1
PROG: spin
LANG: C++
*/

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <stdio.h>
#include <cstring>
using namespace std;

void rotate (int arr[][360], int speed[5]) {
	for (int i=0;i<5;i++) {
		vector<int> tmp(360);
		for (int j=0;j<360;j++) tmp[j] = arr[i][(j-speed[i]+360)%360];
		for (int j=0;j<360;j++) arr[i][j] = tmp[j];
	}
}

bool check (int arr[][360]) {
	for (int i=0;i<360;i++) {
		int j;
		for (j=0;j<5;j++) if (arr[j][i]==0) break;
		if (j==5) return true;
	}
	return false;
}

int main () {
	freopen ("spin.in","r",stdin);
	freopen ("spin.out","w",stdout);
	int w,start,extent,arr[5][360], speed[5];
	memset (arr,0,sizeof(arr));
	for (int i=0;i<5;i++) {
		cin>>speed[i]>>w;
		for (int j=0;j<w;j++) {
			cin>>start>>extent;
			for (int j=start; j<=start+extent; j++) arr[i][j%360] = 1;
		}
	}

	int i=0;

	while (!check(arr) && i<360) {
		rotate (arr, speed);
		i++;
	}
	if (i<360) cout<<i<<endl;
	else cout<<"none"<<endl;
	return 0;
}
