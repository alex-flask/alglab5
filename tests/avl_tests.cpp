#include "avl.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void testInsert() {
    Node* root = insert(nullptr, 10);
    assert(root != nullptr && root->key == 10);
    assert(root->height == 1 && root->size == 1);

    Node* originalRoot = root;
    root = insert(root, 10);
    assert(root == originalRoot && root->size == 1);

    deleteTree(root);
}

void testInsertionRotation(int first, int second, int third, int expectedRotations) {
    Node::rotations = 0;
    Node* root = insert(nullptr, first);
    root = insert(root, second);
    root = insert(root, third);

    assert(root != nullptr && root->key == 20);
    assert(root->height == 2 && root->size == 3);
    assert(root->left != nullptr && root->left->key == 10);
    assert(root->right != nullptr && root->right->key == 30);
    assert(Node::rotations == expectedRotations);

    deleteTree(root);
}

void testFind() {
    assert(find(nullptr, 10) == nullptr);

    Node* root = insert(nullptr, 10);
    root = insert(root, 5);
    assert(root->left != nullptr);
    assert(find(root, 5) == root->left);
    assert(find(root, 8) == nullptr);

    deleteTree(root);
}

void testRemove() {
    Node* root = insert(nullptr, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 25);
    root = insert(root, 40);

    root = remove(root, 40); // Leaf
    assert(root != nullptr && root->size == 5);
    assert(find(root, 40) == nullptr);

    root = remove(root, 10); // One child
    assert(root != nullptr && root->size == 4);
    assert(root->left != nullptr && root->left->key == 5);

    root = remove(root, 20); // Two children
    assert(root != nullptr && root->size == 3 && root->height == 2);
    assert(find(root, 20) == nullptr);
    assert(find(root, 5) != nullptr);
    assert(find(root, 25) != nullptr);
    assert(find(root, 30) != nullptr);

    deleteTree(root);
}

void testRemovalRotation() {
    Node* root = insert(nullptr, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);

    Node::rotations = 0;
    root = remove(root, 40);
    assert(root != nullptr && root->key == 20);
    assert(root->height == 3 && root->size == 4);
    assert(find(root, 40) == nullptr);
    assert(Node::rotations == 1);

    deleteTree(root);
}

std::string statsOutput(Node* root) {
    std::ostringstream output;
    std::streambuf* originalBuffer = std::cout.rdbuf(output.rdbuf());
    printStats(root);
    std::cout.rdbuf(originalBuffer);
    return output.str();
}

void testPrintStats() {
    Node::rotations = 0;
    assert(statsOutput(nullptr) == "Depth: 0\nRotations: 0\nSize: 0");

    Node* root = insert(nullptr, 10);

    root = insert(root, 20);
    root = insert(root, 30);
    assert(statsOutput(root) == "Depth: 2\nRotations: 1\nSize: 3");

    deleteTree(root);
}

int main() {
    testInsert();
    testInsertionRotation(10, 20, 30, 1);
    testInsertionRotation(30, 10, 20, 2);
    testFind();
    testRemove();
    testRemovalRotation();
    testPrintStats();

    std::cout << "All AVL tests passed.\n";
}
