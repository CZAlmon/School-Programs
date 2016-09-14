// File: unionfind.h
// Author: for CS315 JWJ-CS-UK
// Description: simple union find class provided by instructor

// unionfind class
class unionfind 
{
	public:

	unionfind(int); 
	void unions(int i, int j); 
	int find(int i);

	private:
	int *p; // parent in the tree representing a set
	int *rank; //rank
	int size;
};
