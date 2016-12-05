/*
Mohd Sabra
dijkstra 


*/

#include<iostream>
#include <map>
#include<string>
#include<fstream>
#include <vector>
#include"Main.hpp"
#include<algorithm>
#include"Node.hpp"

using namespace std;

string FILE_NAME = "test.txt";
int Edge::numOfEdges = 0;
map<string, int> mHash;

int main() 
{

	vector<Edge> edges;
	vector<Node> nodes;
	string nodeA, nodeB;

	parseDataFromFile(edges);
	sort(edges.begin(), edges.end()); // sort the edge vector
	overwriteFile(edges); 
	vector<string> verticesNames;
	KruskalMST(edges, vertices(edges, verticesNames), verticesNames);


	int ends;
	cin >> ends;

	return 1;
}


// read the entire edge vector and overright the file
// O(E)
void overwriteFile(vector<Edge> &edges)
{
	ofstream file(FILE_NAME);
	for (unsigned int curEdge = 0; curEdge < edges.size(); curEdge++)
	{
		file << edges[curEdge].getNodeA() << " " << edges[curEdge].getNodeB() << " " << edges[curEdge].getCost() << endl;
	}
}

// Extract all vectors from file and place them to the reference vector
// O(E)
void parseDataFromFile(vector<Edge> &edges)
{
	ifstream file;

	string nodeA, nodeB;
	double cost;

	file.open(FILE_NAME.c_str());

	if (file.is_open())
	{
		while (file >> nodeA )
		{
			file >> nodeB;
			file >> cost;
			if (nodeA == nodeB) {} // i dont want the disntace of a node to itself
			else
			{
				Edge newEdge(nodeA, nodeB, cost);
				edges.push_back(newEdge);
			}

		}
		file.close();
	}
	else
	{
		std::cout << " failed to open file";
	}

}

int vertices(vector<Edge> edges, vector<string> & verticesNames)
{
	int counter = 1;

	for (int i = 0; i < edges.size(); i++)
	{
		string A = edges[i].getNodeA();
		string B = edges[i].getNodeB();
		if (mHash[A] == 0)
		{
			mHash[A] = counter++;
			verticesNames.push_back(A);
		}
		if (mHash[B] == 0)
		{
			mHash[B] = counter++;
			verticesNames.push_back(B);
		}
	}
	return counter - 1;
	
}


int find(vector<subGraph> &subs, string vertice)
{
	int i = mHash[vertice] - 1; // decode the string into index
	if (subs[i].parent != i)
		subs[i].parent = find(subs, subs[i].parent);

	return subs[i].parent;
}
int find(vector<subGraph> &subs, int i)
{
	if (subs[i].parent != i)
		subs[i].parent = find(subs, subs[i].parent);

	return subs[i].parent;
}

void merge(vector<subGraph> &sub, int a, int b)
{
	int A = find(sub, a);
	int B = find(sub, b);

	if (sub[A].rank < sub[B].rank)
		sub[A].parent = B;
	else if (sub[A].rank > sub[B].rank)
		sub[B].parent = A;

	else
	{
		sub[B].parent = A;
		sub[A].rank++;
	}
}

void KruskalMST(vector<Edge> edges, int verticesNum, vector<string> verticesName)
{
vector<subGraph> sub;
vector<Edge> ans;
int ansIndex = 0;  
int edgeIndex = 0;  

for (int v = 0; v < verticesNum; ++v)
{
	subGraph temp(v);
	sub.push_back(temp);
}

while (ansIndex < verticesNum - 1)
{
Edge nextEdge(edges[edgeIndex++]);

int x = find(sub, nextEdge.getNodeA());
int y = find(sub, nextEdge.getNodeB());

if (x != y)
{
	Edge temp(nextEdge);
	ans.push_back(temp);
	ansIndex++;
	merge(sub, x, y);
}

}

ofstream file;
file.open("graph.gv");
if (!file.is_open()) return;
file << "  digraph graphname {" << endl;


for (int i = 0; i < ansIndex; ++i)
{
	cout << ans[i].getNodeA() << " <---> " << ans[i].getNodeB() << " ===> Weight: " << ans[i].getCost() << endl;
	file << ans[i].getNodeA() << " ->" << ans[i].getNodeB() << "  [weight=" << ans[i].getCost() << "];" << endl;
}
file << "}";
file.close();
return;
}


