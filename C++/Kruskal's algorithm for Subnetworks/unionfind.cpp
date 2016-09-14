// File: unionfind.cpp
// Description: implementation of union find class from instructor cs315 JWJ
//Does not use good heuristics for union and find (rank, path compression)
#include "unionfind.h"

unionfind:: unionfind(int n)
{
 size = n;
 p = new int[size];
 rank = new int[size];
 for (int i = 0; i < size; i++){
	 p[i] = i; // p[i]==i  stands for "no parent"
	 rank[i] = 0;
 }
 
}

void unionfind::unions(int i, int j)
//unites sets rooted at i and j making j the root, i not equal to j
{

	int iroot = find(i);
	int jroot = find(j);

	if (jroot == iroot){
		return;
	}



	/*
		// x and y are not already in same set. Merge them.
		 if xRoot.rank < yRoot.rank
			 xRoot.parent := yRoot
		 else if xRoot.rank > yRoot.rank
			 yRoot.parent := xRoot
		 else
			 yRoot.parent := xRoot
			 xRoot.rank := xRoot.rank + 1
		
	*/

	if (rank[iroot] < rank[jroot]){
		p[iroot] = jroot;
	}
	else if (rank[jroot] < rank[iroot]){
		p[jroot] = iroot;
	}
	else{
		p[jroot] = iroot;
		rank[iroot] += 1;
	}


}

int unionfind::find(int i)
//find the root (representative) of the set containing i
{
	if (p[i] != i){

		p[i] = find(p[i]);

	}
	return p[i];
}
