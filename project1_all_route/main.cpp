#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

using namespace std;

template<class C>
class Vertex
{
	bool flagSearched;
public:
	C data;
	list<Vertex<C>*> adjvex;
	Vertex() : flagSearched(false) {};
	Vertex(C dataInit);
	bool isSearched();
	void searched();
	void addAdj(Vertex<C>& adj);
	void deleteAdj(Vertex<C>& adj);
	template<class C>
	friend ostream& operator<<(ostream & os,const Vertex<C> & v);
};

template<class C>
ostream& operator<<(ostream & os,const Vertex<C> & v) {
	os << v.data<<" -> ";
	list<Vertex<C>*>::const_iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		os << (**it).data << " , ";
	}
	return os;
}

template<class C>
void Vertex<C>::deleteAdj(Vertex<C>& adj)
{
	list<Vertex<C>*>::iterator it;

	for (it = adjvex.begin(); it != adjvex.end();)
	{
		if (*it == &adj)
		{
			adjvex.erase(it);
			break;
		}
	}
}

template<class C>
void Vertex<C>::addAdj(Vertex<C>& adj)
{
	adjvex.push_back(&adj);
}

template<class C>
Vertex<C>::Vertex(C dataInit)
{
	data = dataInit;
	flagSearched = false;
}

template<class C>
bool Vertex<C>::isSearched()
{
	return flagSearched;
}

template<class C>
void Vertex<C>::searched()
{
	flagSearched = true;
}


template<class C>
class Graph
{
	int numVertex;
	vector<Vertex<C>> vertexes;
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(C dataInit);
	void addEdge(int src,int dst);
	void deleteEdge(int src, int dst);
	void depthFirstSearch(int src);
	void depthFirstSearch(Vertex<C> &v);
	template<class C>
	friend std::ostream& operator<<(std::ostream &os, const Graph<C> &g);
};

template<class C>
void Graph<C>::depthFirstSearch(Vertex<C> &v)
{
	v.searched();
	cout << v.data << endl;
	list<Vertex<C>*>::iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			depthFirstSearch(**it);
		}
	}
}

template<class C>
void Graph<C>::depthFirstSearch(int src)
{
	depthFirstSearch(vertexes[src]);
}

template<class C>
void Graph<C>::deleteEdge(int src, int dst)
{
	vertexes[src].deleteAdj(vertexes[dst]);
}

template<class C>
std::ostream& operator<<(std::ostream &os, const Graph<C> &g) {
	vector<Vertex<C>>::const_iterator it;
	for (it = g.vertexes.begin(); it != g.vertexes.end(); it++)
	{
		cout << *it << endl;
	}
	return os;
}

template<class C>
void Graph<C>::addVertex(C dataInit)
{
	vertexes.push_back(Vertex<C>(dataInit));
	numVertex++;
}

template<class C>
void Graph<C>::addEdge(int src, int dst)
{
	vertexes[src].addAdj(vertexes[dst]);
}

template<class C>
void Graph<C>::addVertex()
{
	vertexes.push_back(Vertex<C>());
	numVertex++;
}

int main()
{
	Graph<char> testGraph;
	for (int i = 0; i < 5; i++)
	{
		testGraph.addVertex('A' + i);
	}
	testGraph.addEdge(0, 4);
	testGraph.addEdge(4, 3);
	testGraph.addEdge(4, 1);
	testGraph.addEdge(1, 0);
	testGraph.addEdge(1, 2);
	testGraph.addEdge(2, 3);
	cout << testGraph<<endl;

	testGraph.depthFirstSearch(0);
	
	return 0;
}


