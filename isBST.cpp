#include <iostream>

struct node {
	node*left;
	node*right;
	int data;
};

bool isBST(node *p)
{
	if(!p) return false;

	// check p first.
	if((p->left && p->left->data > p->data) ||
		(p->right && p->right->data < p->data)) return false;

	// check p->left.
	if(p->left && !isBST(p->left)) return false;

	// check p->right.
	if(p->right && !isBST(p->right)) return false;

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


