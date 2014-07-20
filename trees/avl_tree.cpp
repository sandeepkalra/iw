#include <iostream>
using namespace std;

#define MAX(a,b) ((a>b)?(a):(b))

class cAVL {
	struct node{
		node*left;
		node*right;
		node*parent;
		int data;
		node(int d):data(d),left(0),right(0),parent(0){}
	};
	node *root;
	int ComputeHeight(node *p)
	{	
		if(!p) return 0;
		int left = ComputeHeight(p->left);
		int right = ComputeHeight(p->right);
		return (1 + MAX(left,right));
	}
	int ComputeWt(node *p)
	{
		if(!p) return 0;
		int L = ComputeHeight(p->left);
		int R = ComputeHeight(p->right);
		return (L-R);
	}
	node *RotateLeft(node* g)
	{
		node *p = g->right;
		g->right  = p->left;
		p->left = g;
		// Correct ParentHood.
		p->parent = g->parent;
		g->parent = p;
		return p;
	}
	node *RotateRight(node*g) 
	{	
		node *p = g->left;
		g->left = p->right;
		p->right = g ;
		// Correct ParentHood.
		p->parent = g->parent;
		g->parent = p;
		return p;
	}
	node *Pred(node *p)
	{	
		if(!p) return 0;
		//rightmost in left subtree.
		node *pred = p->left;
		while(pred->right) {
			pred = pred->right;
		}
		return pred;
	}
	node *Succ(node *p)
	{
		if(!p) return 0;
		node *succ = p->right;
		while(succ->left) {
			succ = succ->left;
		}
		return succ;
	}
	void Delete(node *p)
	{
		node * replacement = 0;
		if(p->left)
			replacement = Pred(p);
		else if(p->right)
			replacement = Succ(p);
		if(!replacement) return;
		//Swap content.
		int t = p->data;
		p->data = replacement->data;
		replacement->data = t;
		//Correct the Parenthood and remove the replacement node.
		node * parent_of_replacement = replacement->parent;
		if(parent_of_replacement->left == replacement) parent_of_replacement->left = 0;
		else if (parent_of_replacement->right == replacement) parent_of_replacement->right = 0;
		delete replacement;
	}
	node * Balance(node *r) {

		int W = ComputeWt(r);

		if(W == 0 || W == -1 || W == 1) return r;

		if(W == -2 ) //right heavy. Left Rotate
		{
			int W_rt = ComputeWt(r->right);
			if(W_rt == 1) //left heavy. Right Rotate first.
			{
				r->right  = RotateRight(r->right);
			}
			r =  RotateLeft(r);
		}
		else if(W == +2) //left Heavy. Right Rotate.
		{	
			int W_lt = ComputeWt(r->left);
			if(W_lt == -1) //Right Heavy. Left Rotate Firs .
			{	
				r->left = RotateLeft(r->left);
			}
			r = RotateRight(r);
		}
		return r;
	}
	
	void PrintInOrder(node *p)
	{
		if(!p) return;
		PrintInOrder(p->left);
			cout<< " "<< p->data << endl;	
		PrintInOrder(p->right);
	}

public:
	cAVL():root(0){}
	void Print() {	
		PrintInOrder(root);
	}
	
	void Insert(int v){
		node *temp = new node(v);
		node *p=root;
		
		if(!root) 
		{
			root=temp;
			return ; // Insert as Root. Return.
		}
		while(p){
			if(p->data >v && p->left) {//Traverse to left. 
				p = p->left; 
			}
			else if(p->right) {//Traverse to right subtree. 
				p = p->right;
			}
			else break;
		}
		if(p->data > v)
		{	
			p->left = temp; //Insert as Right Subchild.
		}
		else {
			p->right = temp; //Insert as Left Subchild.
		}
		temp->parent = p; //Assign Parent to temp.	

		if(temp->parent && temp->parent->parent) 
		{
			if(root != temp->parent->parent)
			{
				node *super_parent = temp->parent->parent->parent;
				if(super_parent->left == temp->parent->parent) 
					super_parent->left = Balance(temp->parent->parent);
				else 
					super_parent->right = Balance(temp->parent->parent);
			}
			else
				root = Balance(temp->parent->parent);
		}
	}
	void Delete(int v)
	{	
		if(!root) return;
		node *p = root;
		while(p && p->data != v) 
		{
			if(p->data > v) p=p->left;
			else p = p->right;
		}
		if(p && p->data == v)
			Delete(p);
	}
};

int main()
{	
	cAVL t;
	t.Insert(62);
	t.Insert(8);
	t.Insert(9);
	t.Insert(7);
	t.Insert(13);
	t.Insert(12);
	t.Insert(6);
	t.Insert(17);
	t.Insert(25);
	t.Insert(98);
	t.Insert(2);
	t.Insert(4);
	t.Print();
	t.Delete(4);
	cout<<" \n"; t.Print();
}
