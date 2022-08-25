//11/22/2021
//Kijan Daniel
//Dr. Plank
//binary tree
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

int BSTree::Depth(const string &key) const
{
	BSTNode *n;
	int counter = 0;
	n = sentinel->right;
	while(1) {
/*		if(n == sentinel) {
			return -1;
	    }
	    if(key == n->key) {
		    return counter;
	    }
		if(key < n->key) {
			n = n->left;
		}
		if(key > n->key) {
			n = n->right;
		}
		if(n == NULL) {
			return -1;
		} */
		if(n == sentinel) {
			return -1;
		}
		if(key == n->key) {
			return counter;
		}
		n = (key < n->key) ? n->left : n->right;
		counter++;
	}

	return -1;
}
           
int BSTree::Height() const
{
	int height = recursive_find_height(sentinel->right);
	return height;
}

vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right,rv);
  return rv;
}
    
BSTree::BSTree(const BSTree &t)        
{
	sentinel = new BSTNode;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;
	size = t.size;
	*this = t;
}	

BSTree& BSTree::operator= (const BSTree &t) {
	vector<string> vec;
	vector<void *> vec1;
	vec = t.Ordered_Keys();
	vec1 = t.Ordered_Vals();
	sentinel->right = make_balanced_tree(vec,vec1,0,t.size);//THis makes the copy for the new one
	sentinel->right->parent = sentinel;
	size = t.size;
	return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const
{
	if(n == sentinel) {
		return 0;
	}
	int height1 = recursive_find_height(n->left);
	int height2 = recursive_find_height(n->right);
	if(height1 > height2) {
		return (height1+1);
	}
	else {
		return (height2+1);
	}
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
	if(n == sentinel) {
		return;
	}
	make_key_vector(n->left,v);
	v.push_back(n->key);
	make_key_vector(n->right,v);
}

BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, const vector<void *> &vals, size_t first_index, size_t num_indices) const
{	
	BSTNode *node = new BSTNode;//This is a new node
	int specialnum = first_index + (num_indices/2) + 1;
	if(num_indices == 1) {//This is my base case
		node->left = sentinel;
		node->right = sentinel;
		node->key = sorted_keys[(first_index)];
		node->val = vals[first_index];
		return node;
	}
	if((num_indices % 2) == 1) {//
		node->left = make_balanced_tree(sorted_keys,vals,first_index,num_indices/2);
		node->right = make_balanced_tree(sorted_keys,vals,specialnum,num_indices/2);
		node->right->parent = node;
		node->left->parent = node;
	}
	else {
		if(num_indices == 2) {
			node->left = make_balanced_tree(sorted_keys,vals,first_index,num_indices/2);
			node->right = sentinel;
			node->left->parent = node;
		}
		else {
			node->left = make_balanced_tree(sorted_keys,vals,first_index,num_indices/2);
			node->right = make_balanced_tree(sorted_keys,vals,specialnum,num_indices/2 - 1);
			node->right->parent = node;
			node->left->parent = node;
		}
	}
	node->key = sorted_keys[(num_indices/2)+first_index];
	node->val = vals[(num_indices/2)+first_index];
	return node;
/*	
	if((num_indices != 2)) {
		node->left = make_balanced_tree(sorted_keys,vals,first_index,num_indices/2);
		if(first_index > num_indices) {
			specialnum = first_index + 2;
		}
		else {
			specialnum = num_indices - (num_indices/2);
		}
		node->right = make_balanced_tree(sorted_keys,vals, specialnum,num_indices/2);
	}
	if(num_indices == 2) {
		node->left = make_balanced_tree(sorted_keys,vals,first_index,num_indices/2);
		node->right = sentinel;
	}
	node->key = sorted_keys[(num_indices/2) + first_index];
	node->val = vals[(num_indices/2) + first_index];
	node->left->parent = node;
	return node;
	*/
}
