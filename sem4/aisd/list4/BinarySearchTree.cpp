#include "BinarySearchTree.hpp"

#include <iostream>

BinarySearchTree::BinarySearchTree() : root_(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root_);
}

void BinarySearchTree::insertNode(const int key, int &keyComparisons, int &pointerOperations, const bool printFlag) {
    printIfFlagSet("insert " + std::to_string(key) + '\n', printFlag);
    insertNode(root_, key, keyComparisons, pointerOperations, printFlag);
}

void BinarySearchTree::insertNode(Node *&root, const int key, int &keyComparisons, int &pointerOperations, const bool printFlag) {
    pointerOperations++;
    if (root == nullptr) {
        root = new Node(key);
        return;
    }

    keyComparisons++;
    if (key < root->key) {
        insertNode(root->left, key, keyComparisons, pointerOperations, printFlag);
    } else if (key > root->key) {
        insertNode(root->right, key, keyComparisons, pointerOperations, printFlag);
    } else {
        printIfFlagSet("Key " + std::to_string(key) + " already exists in the tree.\n", printFlag);
    }
}

void BinarySearchTree::deleteNode(const int key, int &keyComparisons, int &pointerOperations, const bool printFlag) {
    printIfFlagSet("delete " + std::to_string(key) + '\n', printFlag);
    deleteNode(root_, key, keyComparisons, pointerOperations, printFlag);
}

void BinarySearchTree::deleteNode(Node *&root, const int key, int &keyComparisons, int &pointerOperations, const bool printFlag) {
    pointerOperations++;
    if (root == nullptr) {
        printIfFlagSet("Key " + std::to_string(key) + " was not found in the tree\n", printFlag);
        return;
    }

    keyComparisons++;
    if (key < root->key) {
        deleteNode(root->left, key, keyComparisons, pointerOperations, printFlag);
    } else if (key > root->key) {
        deleteNode(root->right, key, keyComparisons, pointerOperations, printFlag);
    } else {
        pointerOperations++;
        if (root->left == nullptr) {
            pointerOperations++;
            Node *nodeToRemove = root;
            root = root->right;
            delete nodeToRemove;
        } else if (root->right == nullptr) {
            pointerOperations++;
            Node *nodeToRemove = root;
            root = root->left;
            delete nodeToRemove;
        } else {
            pointerOperations++;
            Node *&minValueNode = findMinValueNode(root->right, pointerOperations);
            root->key = minValueNode->key;
            deleteNode(minValueNode, minValueNode->key, keyComparisons, pointerOperations, printFlag);
        }
    }
}

Node *&BinarySearchTree::findMinValueNode(Node *&root, int &pointerOperations) const {
    pointerOperations++;
    if (root == nullptr) {
        std::cout << "Min value node not found.\n";
        return root;
    } else if (root->left == nullptr) {
        return root;
    } else {
        return findMinValueNode(root->left, pointerOperations);
    }
}

int BinarySearchTree::height() const {
    return height(root_);
}

int BinarySearchTree::height(const Node *root) const {
    if (root == nullptr) {
        return 0;
    }

    return 1 + std::max(height(root->left), height(root->right));
}

void BinarySearchTree::print() const {
    std::string leftTrace(1000, ' ');
    std::string rightTrace(1000, ' ');
    print(root_, 10, '-', leftTrace, rightTrace);
}

void BinarySearchTree::print(const Node *root, const int depth, const char prefix, std::string &leftTrace, std::string &rightTrace) const {
    if (root == nullptr)
        return;

    if (root->left != nullptr) {
        print(root->left, depth + 1, '/', leftTrace, rightTrace);
    }

    if (prefix == '/') {
        leftTrace[depth - 1] = '|';
    }
    if (prefix == '\\') {
        rightTrace[depth - 1] = ' ';
    }

    if (depth == 0) {
        std::cout << "-";
    }
    if (depth > 0) {
        std::cout << " ";
    }
    for (int i = 0; i < depth - 1; i++)
        if (leftTrace[i] == '|' || rightTrace[i] == '|') {
            std::cout << "| ";
        } else {
            std::cout << "  ";
        }
    if (depth > 0) {
        std::cout << prefix << '-';
    }

    std::cout << "[" << root->key << "]\n";
    leftTrace[depth] = ' ';
    if (root->right != nullptr) {
        rightTrace[depth] = '|';
        print(root->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}

void BinarySearchTree::printIfFlagSet(const std::string &text, const bool printFlag) const {
    if (printFlag) {
        std::cout << text;
    }
}

void BinarySearchTree::destroyTree(Node *root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
    }
    delete root;
}
