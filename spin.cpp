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
using namespace std;

#define ii pair<int,int>

long long encode (vector<vector<ii> > &wedges) {
    long long ret = 0;
	for (int i=0;i<5;i++) ret+=wedges[i][0].first*pow(360.0, i);
	return ret;
}

void rotate (vector<vector<ii> > &wedges, vector<int> &speed) {
	for (int i=0;i<5;i++) {
		for (int j=0;j<wedges[i].size();j++) wedges[i][j].first = (wedges[i][j].first+speed[i])%360;
	}
}

bool check (vector<vector<ii> > &wedges) {
	vector<ii> ref = wedges[0];
	for (int i=1;i<5;i++) {
		vector<ii> tmp;
		for (int j=0;j<wedges[i].size();j++) {
			ii p1 = wedges[i][j];
			for (int k=0;k<ref.size();k++) {
				ii p2= ref[k];
				if (p1.first>p2.first) swap(p1,p2);
				if (p1.first+p1.second>=p2.first) {
					if (p2.first+p2.second<=p1.first+p1.second) tmp.push_back (ii(p2.first, p2.second));
					else tmp.push_back (ii(p2.first, p1.first+p1.second-p2.first));
				}
				p1.first+=360;
				swap (p2,p1);
				if (p1.first+p1.second>=p2.first) {
					if (p2.first+p2.second<=p1.first+p1.second) tmp.push_back (ii(p2.first%360, p2.second));
					else tmp.push_back (ii(p2.first%360, (p1.first+p1.second-p2.first)));
				}
			}
		}
		ref = tmp;
	}
	return ref.empty();
}

void print (vector<vector<ii> > &wedges) {
	for (int i=0;i<5;i++) {
		for (int j=0;j<wedges[i].size();j++) {
			cout<<wedges[i][j].first<<" "<<wedges[i][j].second<<" ";
		}
		cout<<endl;
	}
}

void test (ii p1, ii p2) {
	if (p1.first>p2.first) swap(p1,p2);
	if (p1.first+p1.second>p2.first) {
		if (p2.first+p2.second<p1.first+p1.second) cout<<p2.first<<" "<< p2.second;
		else cout<<p2.first<<" "<< p1.first+p1.second-p2.first;
	}
	p1.first+=360;
	swap (p2,p1);
	if (p1.first+p1.second>p2.first) {
		if (p2.first+p2.second<p1.first+p1.second) cout<<p2.first%360<<" "<< p2.second;
		else cout<<p2.first%360<<" "<<p1.first+p1.second-p2.first;
	}
}

int main () {
	freopen ("spin.in","r",stdin);
	freopen ("spin.out","w",stdout);
	vector<vector<ii> > wedges (5);
	vector<int> speed(5);
	int w,start,extent;
	for (int i=0;i<5;i++) {
		cin>>speed[i]>>w;
		for (int j=0;j<w;j++) {
			cin>>start>>extent;
			wedges[i].push_back (make_pair(start, extent));
		}
	}

	int i=0;
    set<long long> s;
	bool sol = true;

	while (check(wedges)) {
		long long code = encode (wedges);
		if (s.find(code) != s.end()) {
			sol = false;
			break;
		}
		s.insert (code);
		rotate (wedges,speed);
		i++;
	}
	if (sol) cout<<i<<endl;
	else cout<<"none"<<endl;
	return 0;
}
