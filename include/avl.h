#pragma once
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    inline static long long rotations = 0;
    /// новое поле (количество узлов в поддереве)
    int size;
};

Node* insert(Node* root, int key);
Node* remove(Node* root, int key);
Node* find(Node* root, int key);
//число логов
int count_in_range(Node* root,int left,int right);
//глубина и количество поворотов
void printStats(Node *root);
