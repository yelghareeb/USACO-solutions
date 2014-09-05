/*
	Problem: msquare
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <stdio.h>
using namespace std;

struct State {
	vector<int> v;
	string moves;
	State (vector<int>& r_v, string r_moves) {
		v = r_v;
		moves = r_moves;
	}
};

int tonum (vector<int>& arr) {
	int sz = arr.size(), ret =0;
	for (int i=0;i<sz;i++) {
		ret += arr[i]*pow(10.0,sz-i-1);
	}
	return ret;
}
vector<int> A (const vector<int>& input) {
	vector<int> ret;
	ret.resize(8);
	ret[0] = input[7];
	ret[1] = input[6];
	ret[2] = input[5];
	ret[3] = input[4];
	ret[4] = input[3];
	ret[5] = input[2];
	ret[6] = input[1];
	ret[7] = input[0];
	return ret;
}

vector<int> B (const vector<int>& input) {
	vector<int> ret;
	ret.resize(8);
	ret[0] = input[3];
	ret[1] = input[0];
	ret[2] = input[1];
	ret[3] = input[2];
	ret[4] = input[5];
	ret[5] = input[6];
	ret[6] = input[7];
	ret[7] = input[4];
	return ret;
}

vector<int> C (const vector<int>& input) {
	vector<int> ret;
	ret.resize(8);
	ret[0] = input[0];
	ret[1] = input[6];
	ret[2] = input[1];
	ret[3] = input[3];
	ret[4] = input[4];
	ret[5] = input[2];
	ret[6] = input[5];
	ret[7] = input[7];
	return ret;
}

int main () {
	freopen ("msquare.in", "r", stdin);
	freopen ("msquare.out", "w", stdout);
	
	vector<int> target, init;
	target.resize(8);
	for (int i=0;i<8;i++) { cin>>target[i]; init.push_back(i+1); }
	queue<State> q;
	q.push (State (init, ""));
	set<int> visited;
	while (!q.empty()) {
		State v = q.front();
		q.pop ();
		int num = tonum (v.v);
		if (visited.find(num)!=visited.end()) continue;
		visited.insert (num);
		if (v.v==target) {
			cout<<v.moves.length()<<endl;
			for (int i=0;i<v.moves.length();i++) {
				if (i%60==0 && i!=0) cout<<endl;
				cout<<v.moves[i];
			}
			cout<<endl;
			return 0;
		}
		vector<int> v1 = A(v.v);
		vector<int> v2 = B(v.v);
		vector<int> v3 = C(v.v);
		q.push (State(v1,v.moves+"A"));
		q.push (State(v2,v.moves+"B"));
		q.push (State(v3,v.moves+"C"));
	}
	return 0;
}