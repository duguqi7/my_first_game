#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

/*data structures definition*/
struct node;
struct element;
typedef struct node *Postion;
typedef struct node *Tree;

/*function definition*/
Tree MakeEmpty(Tree T);
Postion FindIndex(int index, Tree T);
Postion FindMaxIndex(Tree T);
Postion FindMinIndex(Tree T);
void Print(Tree T, int depth);
Tree Insert(struct element in_data, Tree T);
Tree Delete(int index, Tree T);
Postion FindMin(Tree T);
Postion FindMax(Tree T);

struct element{
    int index;
    int hp;
    int mp;
    int armor;
    int attack;
    int arts;
};

struct node{
    struct node *left;
    struct node *right;
    struct element attr;
    int height;
};


#endif // TREE_H_INCLUDED
