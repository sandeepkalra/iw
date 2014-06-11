#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node *left;
	struct node *right;
	int data;
};

struct node *root=0;

void Insert(int v)
{
	if(!root) {
		root = (struct node *) malloc(sizeof(struct node));
		root->left = root->right =0; root->data =v;
	} else {
		struct node *p = root;
		struct node *old = p;

		while(p) {
			old = p;
			if(p->data < v) p=p->right;
			else p = p->left;
		}

		if(old->data > v) {
			old->left = (struct node*) malloc(sizeof(struct node));
			old->left->left = old->left->right =0;
			old->left->data = v;
		} else {
			old->right = (struct node*) malloc(sizeof(struct node));
			old->right->left = old->right->right =0;
			old->right->data = v;
		} 
	}
}

#define FOUND (0)
#define NOTFOUND (-1) 

int Find(int v)
{
	struct node *p = root;
	while(p)
	{
		if(p->data == v) return FOUND;
		if(p->data < v) p=p->right;
		else p=p->left;
	}
	return NOTFOUND;
}


void MirrorTree(struct node *n)
{
	if(n)
	{
		//swap!
		struct node *temp = n->left;
		n->left = n->right;
		n->right = temp;
		//repeat on subtree.
		MirrorTree(n->left);
		MirrorTree(n->right);
	}
}

void ReverseTree()
{
	MirrorTree(root); //Mirror is just a reverse of the tree!
}

void InOrderPrint(struct node *n)
{
	if(n)
	{
		InOrderPrint(n->left);
		printf("\n %d ",n->data);
		InOrderPrint(n->right);
	}
}

void PostOrderPrint(struct node *n)
{
	if(n)
	{
		PostOrderPrint(n->left);
		PostOrderPrint(n->right);
		printf("\n %d ",n->data);
	}
}

void PreOrderPrint(struct node *n)
{
	if(n)
	{
		printf("\n %d ",n->data);
		PreOrderPrint(n->left);
		PreOrderPrint(n->right);
	}
}

struct node *DetachAndReturnLeftMost(struct node *root)
{ // we have guarantee that the root has atleast one leaf!
	struct node * old = 0;
	struct node * p = root;
	while(p && (p->left || p->right)) {
		old = p;
		if(p->left) p = p->left;
		else p=p->right;
	}
	if(old->left == p) old->left =0; 
	else old->right =0;
	return p;
}

struct node *DetachAndReturnRightMost(struct node *root)
{ // we have guarantee that the root has atleast one leaf!
	struct node * old = 0;
	struct node * p = root;
	while(p && (p->left || p->right)) {
		old = p;
		if(p->right) p = p->right;
		else p=p->left;
	}
	if(old->left == p) old->left =0; 
	else old->right =0;
	return p;
}

void Delete(int v) // Tricky
{
	struct node *p = root;
	struct node *old = 0;
	// Algo: 
	// Search the node. keep record of old node.
	// if found, and its leaf.. good.. remove and old->pointer to p=0;
	// if found, and not leaf..
	// -A-	if(left subtree exist) find RIGHT MOST in left-subtee. detach it 
	//      and swap to this node. free this node.
	// -B-   if(right subtree only exist), find LEFTMOST in right-subtee
    //  and replace this node, free this node.

	while(p){
		if(p->data == v) break;//Note:do-NOT update old&SuperOld before this.
		old = p;
		if(p->data < v) p=p->right;
		else p = p->left;
	}

	if(!p) /* not-found */ return ;

	if(!p->left && !p->right) {
		// if the deleting node is leaf, good.. we do it!
		if(old->left == p) { old->left=0;}
		else if(old->right==p) {old->right=0; }
	} else {
		struct node *left = p->left;
		struct node *right = p->right;
		struct node *replacement = 0;
		if(p->left) { // CASE -- A --	
			replacement = DetachAndReturnRightMost(p->left);

		} else { // CASE -- B --
			replacement = DetachAndReturnLeftMost(p->right);
		}

		replacement->left = left; 
		replacement->right = right;

		if(old->left == p) {
			old->left = replacement;
		} else {
			old->right=replacement;
		}
	}
	free(p);
}


void DestroyTree(struct node *p)
{
	if(p)
	{
		DestroyTree(p->left);
		DestroyTree(p->right);
		free(p);
	}
}


struct node * FindCommonAncestorByValue(struct node *r,int a, int b)
{
	struct node *p  = r;
	if(p->data == a || p->data == b) return 0;
	if(p->data > a && p->data > b) return FindCommonAncestorByValue(p->left,a,b);
	else if(p->data < a && p->data <b) return FindCommonAncestorByValue(p->right,a,b);
	else if((a<b && p->data >a && p->data <b ) || (b>a && p->data >b && p->data <a))
	{
		return p;
	}
return 0;
}

struct node * FindCommonAncestorByPointer(struct node*a , struct node*b)
{
// do in-order traversal. record nodes after a or b is hit, keep recording till the other is found.
// if there is 0 element recorded, there is no common ansestor. one is parent of other.
// if there is 1 element recorded, then that is the common ancestor.
// if more than 1 is recorded.
	// then do - pre-order. (root, left, right). record till first of a or b is found. stop.
    // do the recording comparision with in-order. if 1 common, that's it, if more than 1 then
       // then do -post-order(left,right,root). record after a and b are both found. 
       // do another diff betwen all 3 list. just one of the answer will appear.
// O(nlogn)x3...worst case!
return 0;
}

struct node *BFS(struct node *r, int v)
{
	// create Queue, and then
    // for each element starting with r, push r, 
   // then pop top, say r. if r==v return else if r->left, r->right. push them.
   // again pop , value compare, if not, and r->left and r->right, push again.
  // till end of Q.
return 0;
}
   

int main ()
{
	Insert(10);
	Insert(20);
	Insert(3);
	Insert(5);
	Insert(1);
	Insert(80);
	Insert(60);
	Insert(100);
	InOrderPrint(root);
	printf("Deleting : 100, 20");
	Delete(100);
	Delete(20);
	printf("InOrder\n");
	InOrderPrint(root);
	printf("Mirroring and Printing\n");
	MirrorTree(root);
	InOrderPrint(root);
	DestroyTree(root);
}
	
