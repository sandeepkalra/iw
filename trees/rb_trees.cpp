#include <iostream>
using namespace std;

enum { BLACK, RED };
class rbt 
{
	struct node{
		node *left;
		node *right;
		node *parent;
		int color;
		int value;
		node(int i):value(i),color(RED),parent(0),left(0),right(0){ }
	};
	node *root;
	
	node *RotateLeft(node *p) {
		node *superparent = parent(p);
		node* right = p->right;
		p->right = right->left;
		right->left = p;
		right->parent = p->parent;
		p->parent = right;
		if(superparent && superparent->left==p) superparent->left=right;
		else if(superparent) superparent->right=right;
		return right;	
	}
	node *RotateRight(node*p){
		node *superparent = parent(p);
		node *left = p->left;
		p->left=left->right;
		left->right=p;
		left->parent = p->parent;
		p->parent = left;
		if(superparent && superparent->left==p) superparent->left=left;
		else if(superparent) superparent->right=left;
		return left;
	}
	node *grandparent(node *p) {
		if(p->parent) return p->parent->parent;
		return 0;
	}
	node *uncle(node *p) {
		node * g = grandparent(p);
		if(!g) return 0;
		if(g->left==p) return g->right; 
		else return g->left;
	}
	node *parent(node *p) {
		return p->parent;
	}
	void BalanceInserts(node *c)
	{
		// case - 1. c is root!
		if(!parent(c)) {root->color=BLACK; return ; }
		// case - 2. parent of C is black!
		if(parent(c)->color==BLACK) return;

		node *G = grandparent(c);
		node *P = parent(c);
		node *C = c;//Case -4 acts on p. case-3 modifies it (if cond.apply)
		// case - 3. If G->P->c are not in line, then rotate P to make them in line.
		if(G->left == P && P->right==c)
		{	
			RotateLeft(P);
			C = P;
		}
		else if(G->right == P && P->left==c )
		{
			RotateRight(P);
			C = P;
		}
		// We fall back to yet another case now!
		// case - 4.A Uncle Exist!
		// we are here because parent()->color is RED, grandparent()->color is BLACK!
		// 2 possible sub - cases here. Uncle is BLACK or Uncle is  RED.
		if(grandparent(C) && uncle(C)) {
			if(uncle(C)->color==BLACK)
			{
				uncle(C)->color=RED;
				parent(C)->color=BLACK;
				C->color = BLACK;
				if(grandparent(C)->right == parent(C)) RotateLeft(grandparent(C));
				else RotateRight(grandparent(C));
				
			} 
			else // Uncle Exist and is RED!
			{
				uncle(C)->color = BLACK;
				parent(C)->color= BLACK;
				grandparent(C)->color=RED;
				BalanceInserts(G);// go up!
			}
		} else
		{
			// Case 4.B: Uncle Does not Exist!
			// Note: GrandParent(BLACK), Parent(RED) exist if you have reached here.
			node *g = grandparent(C);
			node *p = grandparent(C);
			g->color=RED;
			p->color=BLACK;
			if(g->left == C)
			{
				node *temp =	RotateRight(g);
				if(!g->parent) { root = temp; root->color = BLACK; }
				
			} else
			{
				node *temp =	RotateLeft(g);
				if(!g->parent) { root = temp; root->color = BLACK; }
			}
		}
	}
	void print_all(node *p)
	{	
		if(!p) return;
		print_all(p->left);
		cout<< " "<<p->value;
		print_all(p->right);
	}
public:
	rbt() { root=0;}
	void Insert(int i)
	{
		node *temp = new node(i);
		if(!root) 
		{
			root=temp;
		} 
		else 
		{
			node *p = root;
			while(p) {
				if(p->value < i && p->right) p=p->right;
				else if (p->left) p=p->left;
				else break;
			}
			if(p->value < i) p->right = temp;
			else p->left = temp;
		}
		BalanceInserts(temp);
	}
	void PrintAll()
	{
		print_all(root);
	}
};

int main()
{	
	rbt t;
	t.Insert(10);
	t.Insert(20);
	t.Insert(30);
	t.Insert(4);
	t.PrintAll(); cout<<endl;
	return 0;
}
