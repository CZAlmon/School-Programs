// File: edge.h
// Author: written for CS315 JWJ-CS-UK
// Description: simple class to encapsulate an "edge"
// in a graph; see also graph.h


class edge
{
	public:
	edge();
	edge(int from, int to, int weight);

	int get_from(void) const;
	int get_to(void) const;
	int get_weight(void) const;

	bool operator< (const edge &y) const;

	private:
	int _from, _to, _weight;
};
