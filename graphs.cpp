#include <iostream>
#include <memory>
#include <list>
#include <array>
#include <queue>
using namespace std;

struct node {
	bool visited;
	int  number;
	node(int v) :number(v), visited(false) { }
};

using Graph = array<list<unique_ptr<node>>, 10>;

void AddEdge(Graph &g, int u, int v)
{
	unique_ptr<node> uptr_u (new node(u));
	unique_ptr<node> uptr_v (new node(v));
	g[u].push_back(move(uptr_v));
	g[v].push_back(move(uptr_u));
}

void print_all(Graph& g)
{
	for (int i = 0; i < g.size(); ++i)
	{
		cout << "[" << i << "]";
		for (list<unique_ptr<node>>::const_iterator j = g[i].begin(); j != g[i].end(); ++j)
		{
			node* p = (*j).get();
			cout << "->[" << p->number << "],[" << boolalpha << p->visited << "]";
		}
		cout << endl;
	}
}
int main()
{
	Graph mygraph;
	AddEdge(mygraph, 0, 1);
	AddEdge(mygraph, 0, 2);
	AddEdge(mygraph, 1, 2);
	AddEdge(mygraph, 1, 3);
	AddEdge(mygraph, 2, 3);
	AddEdge(mygraph, 2, 4);
	AddEdge(mygraph, 4, 3);
	AddEdge(mygraph, 4, 1);
	AddEdge(mygraph, 4, 5);
	AddEdge(mygraph, 5, 3);
	print_all(mygraph);
	cout << "goodbye!";
}

