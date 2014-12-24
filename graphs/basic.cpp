#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <deque>
#include <stack>
#include <set>
using namespace std;


////////////////////////////////////////
////// globals 
////////////////////////////////////////
 struct node{
    int level;
    int data;
    bool visited;
	int via;
  node(int v):data(v),visited(false),level(0),via(-1){}
 };

 struct edge {
	int from;
	int cost;//can be negative in Belman Ford, but not in Dijkstra
	edge(int f,int c):from(f), cost(c) {}
 };
	
class cHeap {

public:
	void Insert(node*) {}
	void MakeHeap() {}
	node* MinExtract() { return 0; }
};




class cGraph 
{

 map<int, node*> VertexPool;
 map<int, edge*> EdgePool;
 map<int,list<int>> ajList;
 bool has_triangle;

public:

  bool HasTriangle() { return has_triangle; }

  ///////////////////////////////////////////////////
  //////////////////    AddEdge   ///////////////////
  ///////////////////////////////////////////////////
  void AddEdge(int u, int v, int cost=1)
  {
	// VECTOR objects are not exactly ARRAY. So, Insert is not very simple.
	if(VertexPool[u] == nullptr)
			VertexPool[u] = new node(v);
	if(VertexPool[v] == nullptr)
			VertexPool[v] = new node(u);
	
	ajList[u].push_back(v); 
	ajList[v].push_back(u);
	
    EdgePool[u] = new edge(v,cost); 
    EdgePool[v] = new edge(u,cost);

	
	if(!has_triangle) 
	{
		auto i= ajList[u];
		auto j= ajList[v];
		for(auto elem:i)
		{
			auto found = find(j.begin(),j.end(),elem);
			if(*found==elem) 
			{
				has_triangle=true;
			}
		}
	}//has_triangle	
  }
 
 
  ///////////////////////////////////////////////////
  //////////////////     B F S  /////////////////////
  ///////////////////////////////////////////////////
  void BFS(int v)
  {
	deque<int> q;
    q.push_back(v);
	VertexPool[v]->level=1;
    
	while(!q.empty())
	{
		int n=q.front(); //peek before we pop it!
		q.pop_front();

		if(VertexPool[n]->visited==false)
		{
			for(auto i: ajList[n])
			{ // all ajecent VertexPool.i = int
				//cout<<"n="<<n<<" i="<<i<< " i->visited="<<VertexPool[i]->visited<<endl;
				if(VertexPool[i]->visited==false) 
				{
					/* Note: This check prevents overwriting of level in case some 
					 *	unexplored VertexPool later also points to this node 
					 */
					if(VertexPool[i]->level==0) {
						VertexPool[i]->level = VertexPool[n]->level + 1;
					}
					q.push_back(i);
				}
			}
			VertexPool[n]->visited=true;
			cout<<"vertex: " <<n<<" is visited @ level "<< VertexPool[n]->level<<endl;
		}
		
	}//while q.empty!=true
  }//BFS

  ///////////////////////////////////////////////////
  //////////////////     D F S  /////////////////////
  ///////////////////////////////////////////////////
 void DFS(int v)
 {
	stack<int> q;
    q.push(v);
	VertexPool[v]->level=1;
    
	while(!q.empty())
	{
		
		int n=q.top(); //peek before we pop it!
		q.pop();
		if(VertexPool[n]->visited==false)
		{
			for(auto i: ajList[n])
			{ // all ajecent VertexPool.i = int
				if(VertexPool[i]->visited==false) 
				{
					/* Note: This check prevents overwriting of level in case some 
					 *	unexplored VertexPool later also points to this node 
					 */
					if(VertexPool[i]->level==0) {
						VertexPool[i]->level = VertexPool[n]->level + 1;
					}
					q.push(i);
				}
			}
			VertexPool[n]->visited=true;
			cout<<"vertex: " <<n<<" is visited @ level "<< VertexPool[n]->level<<endl;
		}
		
	}//while q.empty!=true
	
 }//DFS

 vector<int>  SecondDegree(int u) {
	vector<int> v;
 	for(auto i: ajList[u])
		for(auto j: ajList[i])
			if(j!=u) // u is also mutual friend.
				v.push_back(j);
	return v;
 }
 vector<int> ThirdDegree(int u) {
	vector<int> v2 = SecondDegree(u);
	vector<int> v3;
	for(auto i: v2)
		for(auto j: ajList[i])
			if(j != u) v3.push_back(j);
	// Note: V3 may have duplicates.
	// The suggested technique is to put in SET, and BACK!
	set<int> s( v3.begin(), v3.end() );
	v3.assign( s.begin(), s.end() );
	return v3;
} // Most of the People in this world are less than 7 degree apart.

 /////////////////////////////////////////////////////////
 //////////////// Dijkstra's  ////////////////////////////
 /////////////////////////////////////////////////////////
 void Dijktra_SingleSourceShortestPath(int u, int v)
 { 
	
     /*  Dijkstra's : map, and many utilities uses it.
     *
     *  1. Assign 0 cost to u, and all others Infinity! (in HEAP). 
     *  2. Mark u-visited.
     *  3. For all possible ajList[u], push in new Values of cost. Update via if cost is updated.
     *  4. MinExtract() from Heap. This is new u. 
     *  5. Repeat from Step-2 untill heap is empty!
     *
     * STL make_heap, pop_heap, push_heap can be used. The verticies must have comparision function.
     *                            OR
     * we can write our own Heap Mechanism.
     */
	
	#if defined(USE_STL)
	
	#else
	
	#endif
	
	
 }
 /////////////////////////////////////////////////////////
 //////////////// Bellman Ford  //////////////////////////
 /////////////////////////////////////////////////////////
 void BelmanFord_SingleSourceShortestPath(int u, int v)
 { 

	/*  Belman Ford -- Basic of RIP Protocol.
     * 1. for i=0 to n-1, relax(vertex_id);
     * 2. for i=0 to n-1, every vertex exchange cost of reaching other vertex.
     * 3.      if cost of reaching u,v is less in neighbors vertex, use it.
     *
     *
     */
	

	
 }
 
}; //cGraph






int main()
{
	cGraph g;
	g.AddEdge(1,2);
	g.AddEdge(1,3);
	g.AddEdge(2,4);
	g.AddEdge(3,5);
	g.AddEdge(4,5);
	g.AddEdge(4,6);
	g.AddEdge(5,6);
	g.BFS(1);
	cout<<"graph "<< ((g.HasTriangle())?"HAS triangle":"has NO triangle")<<endl;
}
