#include "avl.h"
#include <iostream>
#include <cassert>
#include <algorithm>

//вспомогательные функции для реализации avl-дерева
namespace {
//высота узла
int getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}
int getSize(Node *node) {
    return node == nullptr ? 0 : node->size;
}

//обновить высоту узла
void updateHeight(Node* node) {
    node->height = 1 + std::max(
        getHeight(node->left),
        getHeight(node->right)
    );
}

void updateSize(Node *node) {
    node->size = 1 + getSize(node->left) + getSize(node->right);
}

//получить фактор балансировки
int getBalance(Node* node) {
    return getHeight(node->left)
         - getHeight(node->right);
}

//поворот вправо
Node *rotateRight(Node *y) {
    Node* x = y->left;
    Node* b = x->right;

    x->right = y;
    y->left = b;

    updateHeight(y);
    updateHeight(x);

    updateSize(y);
    updateSize(x);

    Node::rotations++;
    return x;
}

//поворот влево
Node *rotateLeft(Node *y) {
    Node *x = y->right;
    Node *b = x->left;

    x->left = y;
    y->right = b;
    
    updateHeight(y);
    updateHeight(x);

    updateSize(y);
    updateSize(x);

    Node::rotations++;
    return x;
}

//балансировка узла
Node *balance(Node *y) {
    assert(y != nullptr);
    updateHeight(y);
    updateSize(y);
    int bf = getBalance(y);

    if (bf > 1) {
        if (getBalance(y->left) < 0)
            y->left = rotateLeft(y->left);
        return rotateRight(y);
    } else if (bf < -1) {
        if (getBalance(y->right) > 0)
            y->right = rotateRight(y->right);
        return rotateLeft(y);
    }
    return y;
}
int countLessOrEqual(Node* root,int key){
    if(!root) return 0;

    if(root->key <= key){
        int sizeL = (root->left) ? root->left->size : 0;
        return sizeL + 1 + countLessOrEqual(root->right,key);
    }else{
        return countLessOrEqual(root->left,key);
    }
}
}
Node *insert(Node* root, int key)
{
    if (root == nullptr) {
        Node *res = new Node{key, nullptr, nullptr, 1, 1};
        return res;
    }
    if (key < root->key) 
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;
    
    root = balance(root);
    return root;
}
int count_in_range(Node* root,int left,int right){
    if(left>right) return 0;

    int countR = countLessOrEqual(root,right);
    int countL = countLessOrEqual(root,left-1);
    return countR - countL;
}
Node* remove(Node* root, int key)
{
    if(root == nullptr) return nullptr;

    if(key < root->key) root->left = remove(root->left, key);
    else if(key > root->key) root->right = remove(root->right, key);
    else{
        if(root->left == nullptr || root->right == nullptr){
             Node* child = root->left ? root->left : root->right;
             
             if(child == nullptr){
                delete root;
                return nullptr;
             }else{
                *root = *child;   
                delete child;
            }
        }else{
            Node* kid = root->right;
            while(kid->left != nullptr){kid = kid->left;}
            root->key = kid->key;
            root->right = remove(root->right, kid->key);
            }
        }
    root = balance(root);
    return root;
}  
Node* find(Node* root, int key) {
    while (root != nullptr && root->key != key) {
        root = key < root->key ? root->left : root->right;
    }
    return root;
}

void printStats(Node *root) {
    std::cout << "Depth: " << getHeight(root) << '\n'
              << "Rotations: " << Node::rotations << '\n'
              << "Size: " << getSize(root);
}
