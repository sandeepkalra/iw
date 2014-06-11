#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node* left;
	struct node* right;
	int data;
	int weight;//-1,0,1 means balanced. +2 or more -- left heavy, else right!
};

struct node *root;

void Insert(int n)
{
}

void Delete(int n)
{
}

#define FOUND (0)
#define NOTFOUND (-1)
int Find(int n)
{
	struct node*p = root;
	while(p && p->data != n) {
		if(p->data > n) p = p->left; else p = p->right;
	}
	if(p && p->data ==n) return FOUND;
return NOFOUND;
}


/*           * (+2) <=== unbalanced.
 *          /
 *         *(+1)
 *        /
 *       * (0)
 *
 *  Right Rotate : Node(+2)
 *  
 *
 */
struct node* RightRotate(struct node *p) 
{
	// 1. "right-subtree" of "left child" of p is now left child of "p"
	// 2. "left child of p become root node, and p becomes his right-child.

	struct node *right_subtree_of_left_child = p->left->right;
	struct node *p_left_child = p->left;
	
	p->left = right_subtree_of_left_child; p->weight --;
	p_left_child->right = p; 

	p_left_child->weight = p_left_child->left->weight - p_left_child->right->weight;
	return p_left_child;
}

/* 
 *  * (-2) <=== unbalanced
 *   \
 *    * (-1) 
 *     \
 *      * (0)
 *
 */
struct node * LeftRotate(struct node *p)
{
	// 1. left-subtree of p's right node becomes p's right.
    // 2. p's left become root, and root's right is p.
	struct node * left_subtree_of_right_node = p->right->left;
	struct node * right = p->right;

	p->right = left_subtree_of_right_node;
	p->right->weight --;
	right->right = p;
	right->weight = right->left->weight - right->right->weight;
	return right;

}
struct node * DoubleLeftRotate(struct node *p)
{
}

struct node * DoubleRightRotate(struct node *p)
{
}


void Balance()
{
}

void Destroy(struct node *p)
{
}


