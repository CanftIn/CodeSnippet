#include <iostream>
#include <stack>

using namespace std;

typedef int TelemType;

typedef struct BinaryTreeNode
{
	TelemType data;
	struct BinaryTreeNode *Left;
	struct BinaryTreeNode *Right;
}Node;


Node* createBinaryTree()
{
	Node *p;
	TelemType ch;
	cin >> ch;
	if (ch == 0)
	{
		p = NULL;
	}
	else
	{
		p = (Node*)malloc(sizeof(Node));
		p->data = ch;
		p->Left = createBinaryTree();
		p->Right = createBinaryTree();
	}
	return p;
}

void preOrderTraverse(Node* root)
{
	if (root)
	{
		cout << root->data << ' ';
		preOrderTraverse(root->Left);
		preOrderTraverse(root->Right);
	}
}

void preOrderNoRecur(Node *root)
{
	stack<Node *> s;
	Node *p = root;
	while(p || !s.empty())
	{
		while(p)
		{
			cout << p->data << " ";
			s.push(p);
			p = p->Left;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->Right;
		}
	}
}

void inOrderTraverse(Node* root)
{
	if (root)
	{
		inOrderTraverse(root->Left);
		cout << root->data << ' ';
		inOrderTraverse(root->Right);
	}
}

void inOrderNoRecursive(Node* root)
{
	stack<Node *> s;
	Node *p = root;
	while(p || !s.empty())
	{
		while(p)
		{
			s.push(p);
			p = p->Left;
		}
		if(!s.empty())
		{
			p = s.top();
			cout << p->data << " ";
			s.pop();
			p = p->Right;
		}
	}
}

void postOrderTraverse(Node* root)
{
	if (root)
	{
		postOrderTraverse(root->Left);
		postOrderTraverse(root->Right);
		cout << root->data << ' ';
	}
}

// Recursive 
void postOrderNoRecursive(Node* root)
{
	int flag[20];
	stack<Node *> s;
	Node *p = root;
	while(p)
	{
		s.push(p);
		flag[s.size()] = 0;
		p = p->Left;
	}
	while(!s.empty())
	{
		p = s.top();
		while(p->Right && flag[s.size()] == 0)
		{
			flag[s.size()] = 1; // mark the node which has right child node. when stack finish
								// right list node and get back to this node, stack will pop due
								// to that the mark label is 1;
			p = p->Right;
			while(p)
			{
				s.push(p);
				flag[s.size()] = 0;
				p = p->Left;
			}
		}
		p = s.top();
		cout << p->data << " ";
		s.pop();
	}
}

int Nodenum(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + Nodenum(root->Left) + Nodenum(root->Right);

	}
}

int DepthOfTree(Node* root)
{
	if (root)
	{
		return DepthOfTree(root->Left)>DepthOfTree(root->Right) ? DepthOfTree(root->Left) + 1 : DepthOfTree(root->Right) + 1;
	}
	if (root == NULL)
	{
		return 0;
	}
}

int Leafnum(Node* root)
{
	if (!root)
	{
		return 0;
	}
	else if ((root->Left == NULL) && (root->Right == NULL))
	{
		return 1;
	}
	else
	{
		return  (Leafnum(root->Left) + Leafnum(root->Right));
	}
}


int main()
{
	Node *root = NULL;
	root = createBinaryTree();
	printf("build success");
	cout << endl;

	cout << "Node Number  " << Nodenum(root) << endl;

	cout << "depth " << DepthOfTree(root) << endl;

	cout << "leaf number" << Leafnum(root) << endl;

	cout << "pre order: " << endl;
	preOrderTraverse(root);
	cout << endl;

	cout << "pre order: " << endl;
	preOrderNoRecur(root);
	cout << endl;


	cout << "in order: " << endl;
	inOrderTraverse(root);
	cout << endl;

	cout << "in order: " << endl;
	inOrderNoRecursive(root);
	cout << endl;


	cout << "last order: " << endl;
	postOrderTraverse(root);
	cout << endl;

	cout << "last order: " << endl;
	postOrderNoRecursive(root);
	cout << endl;
	return 0;
}

/*
PS E:\2018\TEST\Algorithm\BinaryTree> .\BinaryTree.exe
	1 2 4 0 0 5 0 0 3 6 0 0 7 0 0
	build success
	Node Number  7
	depth 3
	leaf number4
	pre order:
	1 2 4 5 3 6 7
	pre order:
	1 2 4 5 3 6 7
	in order:
	4 2 5 1 6 3 7
	in order:
	4 2 5 1 6 3 7
	last order:
	4 5 2 6 7 3 1
	last order:
	4
*/