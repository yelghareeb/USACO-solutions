// Add a header file to butter.cpp

/*
	Problem: butter
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <stdio.h>
using namespace std;

typedef pair<int, int> ii;
const int INF = 100000000;

int main() {
	// your code goes here
	freopen ("butter.in", "r", stdin);
	freopen ("butter.out", "w", stdout);
	
	int n,p,c,f,t,cost,ret=INF;
	
	cin>>n>>p>>c;	//n: number of cows, p: number of pastures, c: number of connecting paths
	vector<int> cows (p+1, 0);
	vector<vector<ii> > grid (p+1);
	
	for (int i=0;i<n;i++) { cin>>f;	cows[f]++; }
	
	for (int i=0;i<c;i++) {
		cin>>f>>t>>cost;
		grid [f].push_back (make_pair(t,cost));
		grid [t].push_back (make_pair(f,cost));
	}
	
	// Make a modification to the code
	for (int i=1;i<=p;i++) {
		//Choose location i as the meeting point, now do Disjkstra
		int visited [805], dist[805];
		memset (visited, 0, sizeof(visited));
		for (int j=1;j<=p;j++) dist[j] = INF;
		dist [i] = 0;
		priority_queue <ii, vector<ii>, greater<ii> > q;
		q.push (ii(0,i));
		while (!q.empty()) {
			ii front = q.top();
			q.pop();
			if (visited[front.second]) continue;
			visited [front.second] = 1;
			
			int this_node = front.second, this_cost=front.first;
			//Relax edges
			for (int j=0;j<grid[this_node].size();j++) {
				q.push (ii(this_cost+grid[this_node][j].second, grid[this_node][j].first));
				dist [grid[this_node][j].first] = 
				min (dist [grid[this_node][j].first], this_cost+grid[this_node][j].second);
			}
		}
		//Evaluate results
		int count = 0;
		for (int j=1; j<=p;j++)  count += cows[j]*dist[j];

		ret = min (ret, count);
	}
	cout<<ret<<endl;
	return 0;
}
