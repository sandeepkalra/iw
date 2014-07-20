#include <iostream>
using namespace std;
class Tree {

	Tree* left;
	Tree* right;
	int data;
	public:
		int DATA() { return data; }
		Tree(int a):data(a),left(0),right(0){}
		bool InsertNode(int a);
		Tree* findLCA(Tree* r, int a, int b);
};

static Tree* root=0;

bool
Tree::InsertNode(int a) {
	if(root==0) {
		root = new Tree(a);
		if(!root) return false;
		return true;
	}
	else {	
		Tree* p = root;
		while(p) {
			if((p->data < a) && (p->right!=0)) p=p->right;
			if((p->data >= a) && (p->left!=0)) p=p->left;
			else break;
		}
		if(p->data < a) {
				p->right = new Tree(a);
				if(!p->right) return false; return true;
		}
		if(p->data > a) {
				p->left = new Tree(a);
				if(!p->left) return false; return true;
		}
	}
}

Tree *Tree::findLCA(Tree* r, int a,int b)
{	
	if(r==0) return 0;
	if(r->data == a || r->data == b) 
	{
		return r;
	}
	Tree* root_left = findLCA(r->left, a, b);
	Tree* root_right = findLCA(r->right, a, b);
	if( root_left && root_right) 
	{
		cout<<"LCA("<<a<<", "<<b<<") Found. It is: "<<r->data<<endl;
		return r;
	}
	if(root_left!=0) return root_left;
	else if(root_right!=0) return root_right;
	else return 0;
}

int main()
{
	Tree t(33);
	root = &t;
	t.InsertNode(20);
	t.InsertNode(10);
	t.InsertNode(1);
	t.InsertNode(110);
	t.InsertNode(31);
	t.InsertNode(22);
	t.InsertNode(9);
	t.InsertNode(6);
	t.InsertNode(15);
	t.InsertNode(19);
	
	Tree *p = t.findLCA(root,19,110);
	if(p) {
	 cout<<"f: "<<p->DATA()<<endl;
	}
}
