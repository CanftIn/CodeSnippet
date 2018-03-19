#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Tree;
typedef struct Node* Node_t;
typedef int Type;

struct Node
{
    Node_t left;
    Node_t right;
    int height;
    Type data;
};

int Max(int a, int b)
{
    return (a > b) ? a : b;
}

int Height(Node_t node)
{
    return node->height;
}

Node_t RightRotate(Node_t a)
{
    Node_t b = a->left;
    a->left = b->right;
    b->right = a;
    a->height = Max(Height(a->left), Height(a->right));
    b->height = Max(Height(b->left), Height(b->right));
    return b;
}

Node_t LeftRotate(Node_t a)
{
    Node_t b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = Max(Height(a->left), Height(a->right));
    b->height = Max(Height(b->left), Height(b->right));
    return b;
}

Node_t LeftRightRotate(Node_t a)
{
    a->left = LeftRotate(a->left);
    return RightRotate(a);
}

Node_t RightLeftRotate(Node_t a)
{
    a->right = RightRotate(a->right);
    return LeftRotate(a);
}

Node_t Insert(Type x, Tree t)
{
    if(t == NULL)
    {
        t = (Node_t)malloc(sizeof(struct Node));
        t->data = x;
        t->height = 0;
        t->left = NULL;
        t->right = NULL;
    }
    else if(x == t->data)
    {
        return 0;
    }
    else if(x < t->data)
    {
        t->left = Insert(x, t->left);
        if(Height(t->left) - Height(t->right) == 2)
        {
            if(x < t->left->data)
                t = LeftRotate(t);
            else
                t = LeftRightRotate(t);
        }
    }
    else if(x > t->data)
    {
        t->right = Insert(x, t->right);
        if(Height(t->right) - Height(t->left) == 2)
        {
            if(x > t->right->data)
                t = RightRotate(t);
            else
                t = RightLeftRotate(t);
        }
    }
    t->height = Max(Height(t->left), Height(t->right)) + 1;
    return t;
}

void Inoreder(Node_t tree)//中序遍历
{
    if(tree == NULL)
    {
        return ;
    }
    else
    {
    Inoreder(tree->left);
    printf("%d  ",tree->data);
    Inoreder(tree->right);
    }
}


void main()
{
    Node_t root = NULL;
    Insert(3, root);
    Insert(2, root);
    Insert(1, root);
    Insert(4, root);
    Insert(5, root);
    Insert(6, root);
    Insert(7, root);
    Insert(1, root);
    Insert(9, root);
    Insert(8, root);
    printf("\n");
    Inoreder(root);
}