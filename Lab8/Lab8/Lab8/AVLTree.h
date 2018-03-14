#pragma once
#include "AVLNode.h"
#include <algorithm>

using namespace std;

template <typename T>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();

private:
	// Get total height of the tree
	int Height(AVLNode<T> *n)
	{
		if (n == NULL) return -1;
		return 1 + max(Height(n->left), Height(n->right));)
	}

	// Sets the balance of a given node
	void SetBalance(AVLNode<T> *n)
	{
		n->balance = Height(n->right) - Height(n->left);
	}

	// Rotates nodes based on parameter a. Returns new root node that replaces parameter a's position.
	AVLNode<T>* RotateLeft(AVLNode<T> *a)
	{
		AVLNode<T> *b = a->right; // get a's right child

		b->parent = a->parent; // set b's parent to a
		a->right = b->left; // a's right child sets to b's left child. Anything right of a had to be bigger than it. So any node under b must be larger than a. Therefore, we assign a's right child to be b's left child, since it is bigger than a

		if (a->right)
			a->right->parent = a; // reassign b's former left child's parent to a if it exists.

		if (b->parent)
		{
			if (b->parent->right == a)
				// if a was the right child of its former parent, then we set b to be the new right child since b took a's place.
				b->parent->right = b;
			else
				b->parent->left = b; // if a was left child of former parent, then b is set to new left child of parent.
		}

		// update balances now that rotation is done.
		SetBalance(a);
		SetBalance(b);

		return b;
	}

	AVLNode<T>* RotateRight(AVLNode<T> *a)
	{
		AVLNode<T> *b = a->left; // get the left child of a. It will be the new root.
		b->parent = a->parent; // b is the new root of this part of the tree. Therefore, its parent is now what a's parent was.
		a->left = b->right;  // in this instance, b is always less than a. Therefore, any of b's children are smaller than a. This means we assign b's former right child as a's left child.

		if (a->left)
			a->left->parent = a; // assign a's new left node's parent to be a.

		b->right = a; // a goes on b's right because a is larger than b.
		a->parent = b; // a's new parent is b

		if (b->parent)
		{
			if (b->parent->right == a)
				b->parent->right = b; // if b's parent's former right child was a, then set it to be since a and b swapped
			else
				b->parent->left = b; // otherwise, a used to be the left child so set b as the left child.
		}

		// recalculate balance.
		SetBalance(a);
		SetBalance(b);

		return b; // return the new root of this part of the tree
	}

	AVLNode<T>* RotateLeftRight(AVLNode<T> *n)
	{
		n->left = RotateLeft(n->left); // first we need to reorganize this part of the tree so that we can actually rotate right. Take the left child of the root node and perform a left rotation on it
		return RotateRight(n); // now we rotate the original offending node to the right and return the new root.
	}

	AVLNode<T>* RotateRightLeft(AVLNode<T> *n)
	{
		n->right = RotateRight(n->right); // reorganize tree by taking right child of n and rotating it right.
		return RotateLeft(n); // now that we are in a valid position, rotate original root to the left and return new root
	}

	// this function will reset the balance of n and then check the rest of the tree for imbalance and correct it.
	void Rebalance(AVLNode<T> *n)
	{
		SetBalance(n); // set the balance of the node;

		if (n->balance == -2)
		{
			// Left side of tree is imbalanced. 
			if (Height(n->left->left) >= Height(n->left->right))
			{
				/*
				Case 1 checks if we have a left to left imbalance
						A
					   /
					  B
					 /
					C
				*/

				n = RotateRight(n); // case 1
			}
			else
			{
				/*
				case 2 checks if we have a left to right imbalance.
						A
					   /
					  B
					   \
						C
				*/

				n = RotateLeftRight(n); // case 2
			}
		}
		else if (n->balance == 2)
		{
			if (Height(n->right->right) >= Height(n->right->left))
			{
				/*
				case 3 checks if we have a right to right imbalance
						A
						 \
						  B
						   \
						    C
				*/

				n = RotateLeft(n);
			}
			else
			{
				/*
				case 4 checks if we have a right to left imbalance
						A
						 \
						  B
						 /
						C
				*/

				n = RotateRightLeft(n);
			}
		}

		if (n->parent)
			// now that the node n has changed. We want to check the parent and rebalance the parent node if necessary. Basically, we will work our way back up the tree and fix any imbalance.
			rebalance(n->parent);
		else
			root = n; // if we have no parent, then the new root node is n and we are balanced
	}
	
	bool Insert(T key)
	{
		if (!root)
			root = new AVLNode<T>(key, NULL); // if no root exists, then we can just create the root with the new key.
		else
		{
			AVLNode<T> *n = root;
			AVLNode<T> *parent;

			while (true)
			{
				if (n->key == key)
					return false; // if the key already exists in the tree, we cannot add it again.
				
				parent = n; // set parent to the current node before we iterate deeper.
				bool goLeft = n->key > key;

				n = goLeft ? n->left : n->right; // if our key is to smaller than n->key, then we go left and assign n to the left node.

				if (!n)
				{
					// if our new node n is null, then we found a spot to insert.
					if (goLeft)
						parent->left = new AVLNode<T>(key, parent); // remember, parent is the previous node in the tree
					else
						parent->right = newAVLNode<T>(key, parent);

					rebalance(parent); // now we need to ensure the tree remainds balanced after the insertion
					break;
				}
			}
		}
		return true;
	}

	void Delete(T key)
	{
		if (!root)
			return; // if no root exists, then we can just return because nothing exists in the tree.

		AVLNode<T>* n = root, parent = root, delNode = NULL, child = root;

		while (child)
		{
			// as long as the child is valid, keep iterating through tree to find node.
			parent = n; // move parent to current level
			n = child; // move n down
			child = key >= n->key ? n->right : n->left; // if key is larger than n's key, then we iterate right. Left otherwise

			if (key == n->key)
				delNode = n; // if the new node is the node to delete, assign it to delNode.
		}
		if (delNode)
		{
			delNode->key = n->key;
			child = n->left ? n->left : n->right; // check if left child of n exists. If it doesn't, assign child as n's right
			if (root->key == key)
				root = child; // if the root node is the one to delete, then set the new root to child.
			else
			{
				if (parent->left == n)
					// if we're going to delete the paren'ts left node, then set the new left child to n's child
					parent->left = child;
				else
					// if we're deleting parent's right node, then set the new right child to n's right child.
					parent->right = child;
				rebalance(parent); // now that we've removed the node, rebalance.
			}
		}
	}
};

