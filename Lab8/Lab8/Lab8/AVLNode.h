#pragma once

template<typename T>
class AVLNode
{
public:
	T key;
	int balance;
	AVLNode *left, *right, *parent;
	AVLNode(T k, AVLNode *p)
	{
		key = k;
		balance = 0;
		parent = p;
		left = NULL;
		right = NULL;
	}

	~AVLNode()
	{
		delete right;
		delete left;
	}
};

