
#ifndef MAIN_HPP
#define MAIN_HPP

#include<vector>
#include"Edge.hpp"
#include"Node.hpp"

void parseDataFromFile (std::vector<Edge> &edges);

void getInput(std::string &nodeA, std::string &nodeB);

void matchEdge(double curEdgeCost, std::vector<Node> &nodes, Node curNode, std::string nodeId);


void overwriteFile(std::vector<Edge> &edges);

int leastCostNode(std::vector<Node> &nodes);

class subGraph
{
public:
	int parent;
	int rank;
	subGraph(int par): parent(par) , rank(0)
	{

	}
};
int vertices(std::vector<Edge> edges, std::vector<std::string> & verticesNames);
int find(std::vector<subGraph> &subs, std::string vertice);
int find(std::vector<subGraph> &subs, int i);
void KruskalMST(std::vector<Edge> edges, int verticesNum, std::vector<std::string> verticesName);


#endif