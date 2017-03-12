#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>

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
	void unSearched();
	void addAdj(Vertex<C>& adj);
	void deleteAdj(Vertex<C>& adj);
	bool operator==(Vertex const & v);
	template<class C>
	friend ostream& operator<<(ostream & os,const Vertex<C> & v);
};

template<class C>
ostream& operator<<(ostream & os, const vector<Vertex<C>*> v) {
	vector<Vertex<C>*>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		os << (*it)->data;
	}
	return os;
}

template<class C>
void Vertex<C>::unSearched()
{
	flagSearched = false;
}

template<class C>
bool Vertex<C>::operator==(Vertex<C> const & v)
{
	return this == &v;
}

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
	void depthFirstSearch(Vertex<C> &v);
	void findAllRoute(Vertex<C> &src, Vertex<C> &dst, vector<vector<Vertex<C>*>> &searchRoutes);
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(C dataInit);
	void addArc(int src,int dst);
	void deleteEdge(int src, int dst);
	void unSearchAll();
	void depthFirstSearch(int src);
	void findAllRoute(int src, int dst, vector<vector<Vertex<C>*>> &searchRoutes);
	template<class C>
	friend std::ostream& operator<<(std::ostream &os, const Graph<C> &g);
};

template<class C>
void Graph<C>::unSearchAll()
{
	vector<Vertex<C>>::iterator it;
	for (it = vertexes.begin(); it != vertexes.end(); it++)
	{
		(*it).unSearched();
	}
}

template<class C>
void Graph<C>::findAllRoute(Vertex<C> &src, Vertex<C> &dst, vector<vector<Vertex<C>*>> &searchRoutes)
{
	static vector<Vertex<C>*> searchRoute;
	src.searched();
	searchRoute.push_back(&src);
	//cout << src.data;
	if (src == dst)
	{
		searchRoutes.push_back(searchRoute);
		//cout << searchRoute << endl;
		searchRoute.pop_back();
		return;
	}
	list<Vertex<C>*>::iterator it;
	for (it = src.adjvex.begin(); it != src.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			findAllRoute(**it, dst, searchRoutes);
			(*it)->unSearched();
		}
	}
	searchRoute.pop_back();
}

template<class C>
void Graph<C>::findAllRoute(int src, int dst, vector<vector<Vertex<C>*>> &searchRoutes)
{
	unSearchAll();
	searchRoutes.clear();
	findAllRoute(vertexes[src], vertexes[dst], searchRoutes);
}

//递归实现
template<class C>
void Graph<C>::depthFirstSearch(Vertex<C> &v)
{
	v.searched();
	cout << v.data;
	list<Vertex<C>*>::iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			depthFirstSearch(**it);
		}
	}
}

////堆栈实现
//template<class C>
//void Graph<C>::depthFirstSearch(Vertex<C> &v)
//{
//	stack<Vertex<C>*> searchStack;
//	searchStack.push(&v);
//	v.searched();
//	Vertex<C>*nowVertex;
//	while (!searchStack.empty())
//	{
//		nowVertex = searchStack.top();
//		searchStack.pop();
//		cout << nowVertex->data;
//		list<Vertex<C>*>::iterator it;
//		for (it = nowVertex->adjvex.begin(); it != nowVertex->adjvex.end(); it++)
//		{
//			if (!(*it)->isSearched())
//			{
//				searchStack.push(*it);
//				(*it)->searched();
//			}
//		}
//	}
//}

template<class C>
void Graph<C>::depthFirstSearch(int src)
{
	unSearchAll();
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
void Graph<C>::addArc(int src, int dst)
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
	testGraph.addArc(0, 4);
	testGraph.addArc(4, 3);
	testGraph.addArc(4, 1);
	testGraph.addArc(1, 0);
	testGraph.addArc(1, 2);
	testGraph.addArc(2, 3);
	cout << testGraph<<endl;

	//testGraph.depthFirstSearch(0);
	//cout << endl;
	vector<vector<Vertex<char>*>> searchRoutes;
	testGraph.findAllRoute(0, 3, searchRoutes);
	for (int i = 0; i < searchRoutes.size(); i++)
	{
		cout << searchRoutes[i] << endl;
	}
	return 0;
}


