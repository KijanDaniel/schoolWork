#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS202::AVLTree;
using CS202::AVLNode;


void rotate(AVLNode *n);
int find_height(const AVLNode *n);
bool imbalance(const AVLNode * n);
void fix_height(AVLNode *n);
void fix_imbalance(AVLNode *n);
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
  sentinel->right = recursive_postorder_copy(t.sentinel->right);
  sentinel->right->parent = sentinel;
  size = t.size;
  return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;
  AVLNode *t;
  parent = sentinel;
  n = sentinel->right;
  
  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }
	
  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->height = 1;
  n->left = sentinel;
  n->right = sentinel;
  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }
  t = n->parent;
  while(t != sentinel) {
	  t->height = t->height + 1;
	  t = t->parent;
  }
  t = n->parent;
  fix_height(sentinel->right);
  while(t != sentinel) {
	  if(imbalance(t)) {
		  fix_imbalance(t);
		  break;
	  }
	  t = t->parent;
	}

  fix_height(sentinel->right);
  /* Increment the size */
  size++;
  return true;
}
    
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc, *rep;
  string tmpkey;
  void *tmpval;
  AVLNode *t;
  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;


  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
	  rep = n->right;
    } else {
      parent->right = n->right;
	  rep = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
	t = parent;
    while(t != sentinel) {
	  t->height = t->height - 1;
	  t = t->parent;
    }
  rep = parent;
  while(rep != sentinel) {
	  if(imbalance(rep)) {
		  fix_imbalance(rep);
		  break;
	  }
	  rep = rep->parent;
	}
	fix_height(sentinel->right);

    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
	  rep = n->left;
    } else {
      parent->right = n->left;
	  rep = n->left;
    }
    n->left->parent = parent;
	t = parent;
    while(t != sentinel) {
    	t->height = t->height - 1;
	    t = t->parent;
    }
  rep = parent;
  while(rep != sentinel) {
	  if(imbalance(rep)) {
		  fix_imbalance(rep);
		  break;
	  }
	  rep = rep->parent;
	}
	fix_height(sentinel->right);

    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     Tht node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
	rep = parent;
	while(rep != sentinel) {
	  if(imbalance(rep)) {
		  fix_imbalance(rep);
		  break;
	  }
	  rep = rep->parent;
	}
	fix_height(sentinel->right);
    n->key = tmpkey;
    n->val = tmpval;
    return true;
}
	rep = parent;
	while(rep != sentinel) {
	  if(imbalance(rep)) {
		  fix_imbalance(rep);
		  break;
	  }
	  rep = rep->parent;
	}
	fix_height(sentinel->right);


  return true;
}
               
/* You need to write these two.  You can lift them verbatim from your
   binary search tree lab. */

vector <string> AVLTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right,rv);
  return rv;
}
    
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{
	if(n == sentinel) {
		return;
	}
	make_key_vector(n->left,v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}
     
size_t AVLTree::Height() const
{
	return sentinel->right->height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
	if(n->height == 0) {
		return sentinel;
	}
	AVLNode *node = new AVLNode;
	if(n->height == 1) {
		node->height = n->height;
		node->right = sentinel;
		node->left = sentinel;
		node->key = n->key;
		node->val = n->val;
		return node;
	}
	node->key = n->key;
	node->val = n->val;
	node->height = n->height;
	node->right = recursive_postorder_copy(n->right);
	node->left = recursive_postorder_copy(n->left);
	node->right->parent = node;
	node->left->parent = node;
	return node;
}

bool imbalance(const AVLNode *n) {
	if((((int)n->right->height - (int)n->left->height) < -1) || (((int)n->right->height - (int)n->left->height) > 1)) {
		return true;
	}
	return false;
}

void rotate(AVLNode *n) {
	
	AVLNode *parent = n->parent;
	AVLNode *grandparent = parent->parent;
	AVLNode *child;
	if(parent->height == 0) {
		return;
	}
	if(parent->right == n) {
		child = n->left;
		n->parent = grandparent;
		if(grandparent->right == parent) {
			grandparent->right = n;
		}
		else {
			grandparent->left = n;
		}
		parent->parent = n;
		n->left = parent;
		parent->right = child;
		child->parent = parent;
	}
	else {
		child = n->right;
		n->parent = grandparent;
		if(grandparent->right == parent) {
			grandparent->right = n;
		}
		else {
			grandparent->left = n;
		}
		parent->parent = n;
		n->right = parent;
		parent->left = child;
		child->parent = parent;
	}
/*	AVLNode *middle = new AVLNode;
	AVLNode *child = new AVLNode;
	if(n->right->height > n->left->height) {
		middle = n->right;
		child = n->right->left;
		middle->left = n;
		middle->parent = n->parent;
		middle->parent->right = middle;
		n->parent = middle;
		n->right = child;
		child->parent = n;
	}
	if(n->right->height < n->left->height)  {
		middle = n->left;
		child = middle->left;
		middle->right = n;
		middle->parent = n->parent;
		if(middle->parent->height == 0){
		  middle->parent->right = middle;
		}
		else {
			middle->parent->left = middle;
		}
		n->parent = middle;
		n->left = child;
		child->parent = n;
	}*/
}

void fix_imbalance(AVLNode *n) {


	if(n->height == 0) {
		return;
	}
	if(imbalance(n)) {
//	if((n->right->height > n->left->height) && (n->right->right->height > n->right->left->height)) {
	if((n->right->height == (n->height -1)) && (n->right->right->height == (n->height -2))) {
	
		rotate(n->right);
	}
//	else if((n->right->height < n->left->height) && (n->left->right->height < n->left->left->height)) {
	else if((n->left->height == (n->height -1)) && (n->left->left->height == (n->height -2))) {	
		rotate(n->left);
	}
//	else if((n->right->height > n->left->height) && (n->right->right->height < n->right->left->height)) {
	 else if((n->right->height == (n->height -1)) && (n->right->left->height == (n->height -2))) {

	
		rotate(n->right->left);
		rotate(n->right);
	}
//    else if((n->right->height < n->left->height) && (n->left->right->height > n->left->left->height)) {
	if((n->left->height == (n->height -1)) && (n->left->right->height == (n->height -2))) {
	
		rotate(n->left->right);
		rotate(n->left);
	}
	}	
	else {
		return;
	}
	fix_height(n->parent);
	fix_imbalance(n->parent);
}

void fix_height(AVLNode *n) {
/*	if((n->right->height == 0) && (n->left->height == 0)) {
		n->height = 1;
		return;
	}  */
	if(n->height == 0) {
		return;
	}
	if((n->right->height == 0) && (n->left->height == 0)) {
		n->height = 1;
		return;
	}
	fix_height(n->left);
	fix_height(n->right);
	if(n->right->height > n->left->height) {
		n->height = n->right->height+1;
	}
	else {
		n->height = n->left->height+1;
	}
	return;
}
