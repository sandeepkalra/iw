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
	
