//1.Suppose we have an array of size 26 filled with english alphabets and is sorted in ascending order.
//	It looks like A, B, C, D, E, ...., Z.Write an algorithm to unsort the array.Make sure that the unsorted list
//	doesn't contain sub sorted lists of size greater than 2.
//	e - g X, A, R, T, G, L, M, N , E, W, E, Q, .... (this unsorted list contains a sub sorted list [L, M, N]  which has size
//	greater than 2, such sorted lists within unsorted list are not allowed) but it's ok to have a sorted list of
//	size 2 within unsorted list e - g X, A, R, T, G, L, M ‚ E, W, E, Q, .... (L, M) is a sorted list of size 2 which is
//	allowed).
//	Your solution should be creative.
//	
//2.Take the unsorted list from Q1 and insert all its elements 1 by 1 in a binary tree, now take out all the
//	elements from the root of the tree one by oneand add them to the list again, once the array is full it
//	should be sorted again.i - e A, B, C, D, E, F, G, ........, Z.



#include <iostream>
using namespace std;


char sorted[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
char unsorted[26];

class LabExam {
public:



	void function1()
	{
		for (int i = 0; i < 26; i = i + 3)
		{
			if (i < 24)
			{
				unsorted[i] = sorted[i];
				unsorted[i + 1] = sorted[i + 2];
				unsorted[i + 2] = sorted[i + 1];
			}
			else {
				unsorted[i] = sorted[i];
				unsorted[i + 1] = sorted[i + 1];
			}
		}

	}

	void printlist()
	{
		cout << "SORTED LIST" << endl;
		for (int i = 0; i < 26; i++)
		{
			cout << sorted[i] << " ";
		}

		cout << "\nUNSORTED LIST" << endl;
		for (int i = 0; i < 26; i++)
		{
			cout << unsorted[i] << " ";
		}
	}


};


class node
{
public:
	int data;
	node* left;
	node* right;

	node()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}
};


///////-----------------  Printing Tree code  -------------------///////////
struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p)
{
	if (p == NULL)
		return;

	showTrunks(p->prev);

	cout << p->str;
}

char toalpha(int no)
	{
		char alpha = (int)no;
		return alpha;
	}

// Recursive function to print binary tree
// It uses inorder traversal
void printTree(node* root, Trunk* prev, bool isRight)
{
	if (root == NULL)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isRight)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << toalpha(root->data) << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}





///////////////-------------------------------////////////////////////////


class BST : public node
{
	node* root;
	int duplicate;

public:

	BST()
	{
		root = NULL;
		duplicate = 0;
	}



	node* insert(int val, node* current)
	{
		node* ans = find(current, val);
		if (ans == NULL)
		{
			if (current == NULL)
			{
				current = new node;
				current->data = val;
				current->left = current->right = NULL;
			}
			else if (val < current->data)
				current->left = insert(val, current->left);
			else if (val > current->data)
				current->right = insert(val, current->right);
			return current;
		}
		else
		{
			cout << "\n\n Duplicate occured!   Value = " << val << "\n\n\n";
			return NULL;
		}

	}

	////finds the num to replace for the deleted one///
	node* inorderSuccessor(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return inorderSuccessor(t->left);
	}

	node* inorderPredecessor(node* p) {
		if (p == NULL)
			return NULL;
		else if (p->right == NULL)
			return p;
		else
			return inorderPredecessor(p->right);
	}

	/////////--------------------/////

	node* remove(int x, node* t) {
		node* temp;
		if (t == NULL)
			return NULL;
		else if (x < t->data)
			t->left = remove(x, t->left);
		else if (x > t->data)
			t->right = remove(x, t->right);
		else if (t->left && t->right)
		{

			temp = inorderSuccessor(t->left);//for successor ,  for predecessor:   temp = inorderPredecessor(t->left); 
			t->data = temp->data;
			root = temp;
			t->left = remove(t->data, t->left);
		}
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}

		return t;
	}

	node* find(node* nod, int value) {
		if (nod == NULL)
			return NULL;
		else if (value < nod->data)
			return find(nod->left, value);
		else if (value > nod->data)
			return find(nod->right, value);
		else
			return nod;
	}

	int tonum(char x) {
		int num = (char)'x';
		return num;
	}
	
	
	char toalpha(int no)
	{
		char alpha = (int)no;
		return alpha;
	}
	
	void inorder(node* treehead)
	{
		if (treehead == NULL)
		{
			return;
		}
		inorder(treehead->left);
		cout << toalpha(treehead->data) << " ";
		inorder(treehead->right);
	}
};


int main()
{
	node* root = NULL;


	LabExam l;
	l.function1();
	l.printlist();


	BST b;
	for (int i = 0; i < 26; i++)
	{
		root = b.insert(unsorted[i], root);
	}
	cout << "\n\n"; cout << "\n\n";


	printTree(root, NULL, false);

	cout << "\n\n";
	cout<<"Displaying by Root : ";
	b.inorder(root);

}
