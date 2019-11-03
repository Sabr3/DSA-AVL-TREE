//
// Created by Sabr3 on 30/10/2019.
//


#include <stdio.h>
#include <stdlib.h>

struct AVL_Node{
    int data;
    int height;
    struct AVL_Node *l_child, *r_child;
}*root = NULL;

int AVL_Height(struct AVL_Node *ptr);
int BalanceFactor(struct AVL_Node *ptr);

int BalanceFactor(struct AVL_Node *ptr){
    int l_height, r_height;

    l_height = ptr && ptr->l_child ? ptr->l_child->height : 0;
    r_height = ptr && ptr->r_child ? ptr->r_child->height : 0;

    return l_height - r_height;
}

int AVL_Height(struct AVL_Node *ptr)
{
    int l_height, r_height;

    l_height = ptr && ptr->l_child ? ptr->l_child->height : 0;
    r_height = ptr && ptr->r_child ? ptr->r_child->height : 0;
    return l_height > r_height ? l_height + 1 : r_height + 1;
}

struct AVL_Node *LLRotation(struct AVL_Node *ptr){
    struct AVL_Node *ptr_left = ptr->l_child;
    struct AVL_Node *ptr_left_left = ptr_left->l_child;
    struct AVL_Node *ptr_left_right = ptr_left->r_child;

    ptr_left->r_child = ptr;
    ptr_left->l_child = ptr_left_left;

    if(ptr_left_right)
        ptr->l_child = ptr_left_right;
    else
        ptr->l_child = NULL;

    ptr->height = AVL_Height(ptr);
    ptr_left->height = AVL_Height(ptr_left);

    if (root == NULL)
        root = ptr_left;

    return ptr_left;
}
//DOROBIT
struct AVL_Node *LRRotation(struct AVL_Node *ptr){
    struct AVL_Node *ptr_left = ptr->l_child;
    struct AVL_Node *ptr_left_right = ptr_left->r_child;

    ptr_left->r_child = ptr_left_right->l_child;
    ptr->l_child = ptr_left_right->r_child;
    ptr_left_right->r_child = ptr;
    ptr_left_right->l_child = ptr_left;

    ptr->height = AVL_Height(ptr);
    ptr_left->height = AVL_Height(ptr_left);
    ptr_left_right->height = AVL_Height(ptr_left_right);

    if (root == ptr)
        root = ptr_left_right;

    return ptr_left_right;
}

struct AVL_Node * RRRotation(struct AVL_Node *ptr){

    struct AVL_Node *ptr_right = ptr->r_child;
    struct AVL_Node *ptr_right_right = ptr_right->r_child;
    struct AVL_Node *ptr_right_left = ptr_right->l_child;

    ptr_right->l_child = ptr;
    ptr_right->r_child = ptr_right_right;

    if(ptr_right_left)
        ptr->r_child = ptr_right_left;
    else
        ptr->r_child = NULL;

    ptr->height = AVL_Height(ptr);
    ptr_right->height = AVL_Height(ptr_right);

    if (root == NULL)
        root = ptr_right;

    return ptr_right;
}

struct AVL_Node * RLRotation(struct AVL_Node *ptr){

    struct AVL_Node *ptr_right = ptr->r_child;
    struct AVL_Node *ptr_right_left = ptr_right->l_child;

    ptr_right->l_child = ptr_right_left->r_child;
    ptr->r_child = ptr_right_left->l_child;
    ptr_right_left->l_child = ptr;
    ptr_right_left->r_child = ptr_right;

    ptr->height = AVL_Height(ptr);
    ptr_right->height = AVL_Height(ptr_right);
    ptr_right_left->height = AVL_Height(ptr_right_left);

    if (root == ptr)
        root = ptr_right_left;

    return ptr_right_left;
}

struct AVL_Node* AVL_Insert(struct AVL_Node* ptr, int key){

    struct AVL_Node *t = NULL;

    if (ptr == NULL){
        t = (struct AVL_Node*) malloc(sizeof(struct AVL_Node));
        t->data = key;
        t->height = 1;
        t->l_child = t->r_child = NULL;
        return t;
    }
    if (key < ptr->data) {
        ptr->l_child = AVL_Insert(ptr->l_child, key);
    } else if (key > ptr->data) {
        ptr->r_child = AVL_Insert(ptr->r_child, key);
    }

    ptr->height = AVL_Height(ptr);

    if (BalanceFactor(ptr) == 2 && BalanceFactor(ptr->l_child) == 1){
        return LLRotation(ptr);
    }
    else if (BalanceFactor(ptr) == 2 && BalanceFactor(ptr->l_child) == -1){
        return LRRotation(ptr);
    }
    if (BalanceFactor(ptr) == -2 && BalanceFactor(ptr->r_child) == -1){
        return RRRotation(ptr);
    }
    else if (BalanceFactor(ptr) == -2 && BalanceFactor(ptr->r_child) == 1){
        return RLRotation(ptr);
    }

    return ptr;
}

struct AVL_Node * AVL_Search(struct AVL_Node* root, int key) {
    struct AVL_Node *t = root;

    while (t != NULL) {
        if (key == t->data)
            return t;
        else if (key < t->data)
            t = t->l_child;
        else
            t = t->r_child;
    }
    return NULL;
}