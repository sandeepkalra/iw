#include <iostream>
#include <vector>
using namespace std;

struct node {
	node*left;
	node*right;
	int data;
};


node *successor(node *p) { /* leftmost in right node */
	node * ret = 0;
	if(p->right) {
		ret  = p->right;
		while(ret->left) ret = ret->left;
	}
	return ret;
}

node *predecessor (node *p) { /* rightmost in left node */
	node * ret  = 0;
	if(p->left) {
		ret = p->left;
		while(ret->right) ret = ret->right;
	}
	return ret;
}

/* Problem statment: 
	if there is a duplicate, then putting things in vector will not help!
	else , we must check pred and succ also , to see strict increasing order!
*/
bool isBST ( node *p )
{
	if(!p) return false;
	if ((p->left && p->left->data <= p->data ) && (p->right && p->right->data > p->data))
	{	/* node level is checked first */

		node *succ = successor(p);
		node *pred = predecessor(p);

		if(succ &&  p->data <= succ->data) return false; 
		if(pred &&  p->data > pred->data) return false;
			
		if(p->left) {
			if(!isBST(p->left)) return false;
		}
		if(p->right) {
			if(!isBST(p->right)) return false;
		}
		return true;
	}
	return false;
}

void FillInorder(node *p, vector<int> &v) 
{
	if(p) {
		if(p->left) FillInorder(p->left, v);
		v.push_back(p->data);
		if(p->right) FillInorder(p->right, v);
	}
}
bool isBST_NoDuplicates(node *p)
{
	if(!p) return 0;
	vector<int> v;
	FillInorder(p,v);
	
	int sz = v.size;
	int vPrev = v[0];

	for(auto i = 1; i < sz; i++) {
		if(vPrev >= v[i]) return false;
		vPrev = v[i];
	}
	return true;
}

int counter=0;
int n=10;
int find_nth_node(node *p) /* This is O(n) complexity */
{
	int k=-1;
	if(counter<n) { /* PREORDER */
		if(p->left) if((k = find_nth_node(p->left)) > 0) return k;
		counter++; /* visit p*/ if(counter == n) return p->data;
		if(p->right) if( (k = find_nth_node(p->right))>0) return k;
	} 
	return k;
}

#define MAX(a,b) ((a>b)?(a):(b))
int CntNodesInSubtree(node* p)
{
	if(!p) return 0;
	int left_cnt = CntNodesInSubtree(p->left);
	int right_cnt = CntNodesInSubtree(p->right);
	return (1 + left_cnt + right_cnt);
}

node* Find_Kth_node(node *p, int k) /* This is based on QuickSearch(Lg n).. Search */
{
	if(!p) return 0;
	int right=0;

	if(p->right) right=CntNodesInSubtree(p->right);

	if(k > right) /* The node is in left subtree */
		return Find_Kth_node(p->left, k-right);
	else if(k < right) /* Node is in right subtree */
		return Find_Kth_node(p->right, k - 1);
	/* else if (k== right) */
		return p;
}


