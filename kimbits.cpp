/*
	Problem: kimbits
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;

int n,l;
long long i;

int numones (int x) {
	int ret = 0;
	while (x>0) {
		ret+=x%2;
		x/=2;
	}
	return ret;
}

string binary (long long x) {
	string ret = "";
	while (x!=0) {
		char to_add = '0' + (x%2);
		x/=2;
		ret+= to_add;
	}
	for (int j=ret.length(); j<n;j++) ret+= "0";
	for (int j=0;j<ret.length()/2;j++) swap (ret[j], ret[ret.length()-j-1]);
	return ret;
}

int main() {
	// your code goes here
	freopen ("kimbits.in", "r", stdin);
	freopen ("kimbits.out", "w", stdout);
	
	int cum_freqs[34], left = 0;
	memset (cum_freqs, 0, sizeof(cum_freqs));
	cin>>n>>l>>i;
	
	for (int i=0;i<(1<<(n/2));i++) 	cum_freqs[numones(i)]++;
	for (int j=1;j<=n;j++) 	cum_freqs[j] += cum_freqs[j-1];

	while (i>0) {
		int ones = numones (left);
		if (n%2) {
			for (int j=0;j<2;j++) {
				left = (left<<1)+j;
				if (ones+j>l) break;
				ones += j;
				if (cum_freqs[l-ones]>=i) goto OUT;
				i -= cum_freqs [l-ones];
				left /= 2;
			}
		}
		else {
			if (ones<=l) {
				if (cum_freqs[l-ones]>=i) break;
				i -= cum_freqs [l-ones];
			}
		}
		left++;
	}
	
	OUT:
	int j, numleft = numones(left);
	for (j=0;j<(1<<(n/2)) && i!=0 ;j++) 	if (numones(j)<= l-numleft) i--;
	
	cout<<binary((long long)((long long)left<<(n/2))+j-1)<<endl;
	return 0;
}