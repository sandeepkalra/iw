#include <iostream>
#include <memory>
#include <list>
#include <array>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;


struct vertex {
	int number;
 	bool visited; 
};



array<vertex,20> pool;
array<list<vertex*>,20> aj_list;

void Init()
{
	for(int i=0;i<20;++i) pool[i].number=i;
}
void ReInit()
{
		for(int i=0;i<20;++i) pool[i].visited=false;
}

void AddEdge(int vertex, int end_vertex)
{
	aj_list[vertex].push_back(&pool[end_vertex]);
	aj_list[end_vertex].push_back(&pool[vertex]);
}

void Visit(vertex* v)
{
	cout<<"Vertex:"<<v->number <<" Visited\n";
	v->visited = true;
}

void BFS(int start_vertex)
{
	queue<vertex*> bfs;
	bfs.push(&pool[start_vertex]);	
	cout<<"BFS:\n";
	while(!bfs.empty())
	{
		vertex* current_node =  bfs.front(); bfs.pop();
		if(current_node->visited == false)
		{
			for(list<vertex*>::const_iterator i=aj_list[current_node->number].begin();
				i!=aj_list[current_node->number].end(); ++i)
			{
				bfs.push((*i));
			}
			Visit(current_node);
		}
	}
}

void DFS(int start_vertex)
{
	cout<<"DFS:\n";
	stack<vertex*> dfs;
	dfs.push(&pool[start_vertex]);
	while(!dfs.empty())
	{
		vertex* current_node =  dfs.top(); dfs.pop();
		if(current_node->visited == false)
		{
			for(list<vertex*>::const_iterator i=aj_list[current_node->number].begin();
				i!=aj_list[current_node->number].end(); ++i)
			{
				dfs.push((*i));
			}
			Visit(current_node);
		}
	}
}


int main()
{
	Init();
	AddEdge(0,1);
	AddEdge(0,2);
	AddEdge(1,2);
	AddEdge(4,2);
	AddEdge(1,3);
	//AddEdge(1,4);
	AddEdge(3,5);
	AddEdge(4,5);
	AddEdge(3,4);
	AddEdge(1,7);
	BFS(7);
	ReInit();
	DFS(0);
	return 0;
}
