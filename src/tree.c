#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Postion SingleRotateWithLeft(Postion k2);
static Postion SingleRotateWithRight(Postion k2);
static Postion DoubleRotateWithLeft(Postion k3);
static Postion DoubleRotateWithRight(Postion k3);

static int Max(int a, int b)
{
    return ( a>b ? a:b);
}

static int getHeight(Tree T)
{
    if(NULL == T)
    {
        return -1;
    }
    return T->height;
}

Tree MakeEmpty(Tree T)
{
    if(T != NULL)
    {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}
Postion FindIndex(int index, Tree T)
{
    if(NULL == T)
    {
        return NULL;
    }

    if(T->attr.index == index)
    {
        return T;
    }
    else if(T->attr.index > index)
    {
        return FindIndex(index, T->left);
    }
    else
    {
        return FindIndex(index, T->right);
    }
}
Postion FindMaxIndex(Tree T)
{
    if(NULL == T)
    {
        return NULL;
    }
    else if(T->right != NULL)
    {
        return FindMaxIndex(T->right);
    }
    else
    {
        return T;
    }
}
Postion FindMinIndex(Tree T)
{
    if(NULL == T)
    {
        return NULL;
    }
    else if(T->left != NULL)
    {
        return FindMinIndex(T->left);
    }
    else
    {
        return T;
    }
}

void Print(Tree T, int depth)
{
    int i = 0;

    if(NULL == T)
    {
        //printf("T is NULL.\n");
        return;
    }

    Print(T->left, depth);
    Print(T->right, depth);
    for(i = 0; i < T->height; i++)
    {
        printf("-");
    }
    printf("%d\n", T->attr.index);
}

Tree Insert(struct element in_data, Tree T)
{
    if(NULL == T)
    {
        /*create a new tree*/
        T = (Tree)malloc(sizeof(struct node));
        if(NULL == T)
        {
            printf("fatal error: out of space\n");
            return NULL;
        }
        else
        {
            memcpy(&T->attr, &in_data, sizeof(struct element));
            T->height = 0;
            T->left = NULL;
            T->right = NULL;
        }
    }
    else if(in_data.index > T->attr.index)
    {
        T->right = Insert(in_data, T->right);
        if(getHeight(T->right) - getHeight(T->left) == 2)
        {
            if(in_data.index > T->right->attr.index)
            {
                T = SingleRotateWithRight(T);
            }
            else
            {
                T = DoubleRotateWithRight(T);
            }
        }
    }
    else if(in_data.index < T->attr.index)
    {
        T->left = Insert(in_data, T->left);
        if(getHeight(T->left) - getHeight(T->right) == 2)
        {
            if(in_data.index < T->left->attr.index)
            {
                T = SingleRotateWithLeft(T);
            }
            else
            {
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else
    {
        memcpy(&T->attr, &in_data, sizeof(struct element));
    }

    T->height = Max(getHeight(T->left), getHeight(T->right)) + 1;
    return T;
}

Tree Delete(int index, Tree T)
{
    Tree ptemp = NULL;
    if(NULL == T)
    {
        return NULL;
    }
    else if(index > T->attr.index)
    {
        T->right = Delete(index, T->right);
        if(getHeight(T->left) - getHeight(T->right) == 2)
        {
            if(T->left->left != NULL)
            {
                T = SingleRotateWithLeft(T);
            }
            else
            {
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else if(index < T->attr.index)
    {
        T->left = Delete(index, T->left);
        if(getHeight(T->right) - getHeight(T->left) == 2)
        {
            if(T->right->right != NULL)
            {
                T = SingleRotateWithRight(T);
            }
            else
            {
                T = DoubleRotateWithRight(T);
            }
        }
    }
    else
    {
        if(T->left && T->right)
        {
            ptemp = FindMin(T->right);
            memcpy(&T->attr, &ptemp->attr, sizeof(struct element));
            T->right = Delete(ptemp->attr.index, T->right);
        }
        else
        {
            if(T->left)
            {
                ptemp = T->left;
            }
            else if(T->right)
            {
                ptemp = T->right;
            }
            else
            {
                ptemp = NULL;
            }
            free(T);
            T = ptemp;
        }
    }

    if(T) T->height = Max(getHeight(T->left), getHeight(T->right)) + 1;
    return T;
}

Postion FindMin(Tree T)
{
    Postion p = T;

    if(T && T->left)
    {
        p = FindMin(T->left);
    }

    return p;
}

Postion FindMax(Tree T)
{
    Postion p = T;

    if(T && T->right)
    {
        p = FindMax(T->right);
    }

    return p;
}


static Postion SingleRotateWithLeft(Postion k2)
{
    Postion k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = Max(getHeight(k1->left), getHeight(k1->right)) + 1;
    return k1;
}
static Postion SingleRotateWithRight(Postion k2)
{
    printf("test:%d\n", k2->attr.index);
    Postion k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;


    k2->height = Max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = Max(getHeight(k1->left), getHeight(k1->right)) + 1;
    return k1;
}
static Postion DoubleRotateWithLeft(Postion k3)
{
    ///left child has a right child condition
    k3->left = SingleRotateWithRight(k3->left);
    k3 = SingleRotateWithLeft(k3);
    return k3;
}
static Postion DoubleRotateWithRight(Postion k3)
{
    ///right child has a left child condition
    k3->right = SingleRotateWithLeft(k3->right);
    k3 = SingleRotateWithRight(k3);
    return k3;
}
