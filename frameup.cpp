#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

#define TEST
int h,w,numChars=0;

char grid[35][35];

vector<vector<int> > precedenceGraph;
vector<string> sols;
map<char,int> charsToInts;
map<int,char> intsToChars;
vector<int> boundaries[4]; //Left, right, up, down
vector<int> scrambled;


bool exists (char c, int x1, int x2, int y1, int y2) {
	for (int j=x1; j<=x2;j++) if (grid[y1][j]==c || grid[y2][j]==c) return true;
	for (int i=y1; i<=y2;i++) if (grid[i][x1]==c || grid[i][x2]==c) return true;
	return false;
}

void topologicalSort (string ans) {
	//Terminating condition
	if (ans.length()==numChars) {
		for (int j=0;j<numChars/2;j++) swap(ans[j], ans[numChars-j-1]);	//Reverse the string
		sols.push_back(ans);
		return;
	}

	//Get the character with no incoming edges
	for (int i=0;i<numChars;i++) {
		if (scrambled[i]) continue;
		int j;
		for (j=0;j<numChars;j++) {
			if (scrambled[j]) continue;
			if (precedenceGraph[i][j]==1) break;
		}
		if (j==numChars) {
			scrambled[i] = 1;
			topologicalSort (ans+intsToChars[i]);
			scrambled[i] = 0;
		}
	}
}

int main () {
	freopen ("frameup.in", "r", stdin);
	freopen ("frameup.out", "w", stdout);

	//1. Read the input
	cin>>h>>w;
	for (int i=0;i<h;i++) { 
		for(int j=0;j<w;j++) {
			cin>>grid[i][j];
			if (grid[i][j]!='.') {
				if (charsToInts.find(grid[i][j])==charsToInts.end() ) {
					charsToInts[grid[i][j]] = numChars++;//Not found in map
					intsToChars[numChars-1] = grid[i][j];
				}
			}
		}
	}

	#ifdef TEST_DONE
		for (auto it = charsToInts.begin(); it!=charsToInts.end();it++)
			printf ("%c %d\n", it->first, it->second);
	#endif

	//2. Get frame boundaries
	int initBounds [] = {w+1, -1, h+1, -1};
	for (int i=0;i<4;i++) boundaries[i] = vector<int> (numChars, initBounds[i]); //size, value
	
	for (int i=0;i<h;i++) {
		for (int j=0; j<w;j++) {
			if (grid[i][j]!='.') {
				int ind = charsToInts[grid[i][j]];
				boundaries[0][ind] = min (boundaries[0][ind], j) ;	//Left
				boundaries[1][ind] = max (boundaries[1][ind], j) ;	//Right
				boundaries[2][ind] = min (boundaries[2][ind], i) ;	//Up
				boundaries[3][ind] = max (boundaries[3][ind], i) ;	//Down
			}
		}
	}

	#ifdef TEST_DONE
		for (auto it = charsToInts.begin(); it!=charsToInts.end();it++) {
			int ind = it->second;
			printf ("Char=%c, Left=%d, Right=%d, Up=%d, Down=%d\n", it->first, boundaries[0][ind], \
				boundaries[1][ind], boundaries[2][ind], boundaries[3][ind]);
		}
	#endif


	//3. Construct precedence ordering
	precedenceGraph.resize(numChars);
	for (int i=0;i<numChars;i++) precedenceGraph[i] = vector<int> (numChars, 0);

	for (int i=0; i<numChars;i++) {
		for (int j=i+1;j<numChars;j++) {
			//Check if a character precedes the other
			if (exists (intsToChars[i], boundaries[0][j], \
				boundaries[1][j], boundaries[2][j], boundaries[3][j]) ) //Character j precedes character i
				precedenceGraph[j][i] = 1; 
			else if (exists (intsToChars[j], boundaries[0][i], \
				boundaries[1][i], boundaries[2][i], boundaries[3][i]) ) //Character i precedes character j
				precedenceGraph[i][j] = 1; 
		}
	}

	#ifdef TEST_DONE
		printf ("  ");
		for (int i=0;i<numChars;i++) 
			printf ("%c ", intsToChars[i]);
		printf ("\n");
		for (int i=0;i<numChars;i++) {
			printf ("%c ", intsToChars[i]);
			for (int j=0;j<numChars;j++) {
				printf ("%d ", precedenceGraph[i][j]);
			}
			printf ("\n");
		}
	#endif

	//4. Topological sort momanhaga
	scrambled = vector<int> (numChars, 0);
	topologicalSort ("");
	sort (sols.begin(), sols.end());
	
	//5. Print Answer
	int ansSize = sols.size();
	for (int i=0;i<ansSize;i++) cout<<sols[i]<<endl;

	return 0;
}