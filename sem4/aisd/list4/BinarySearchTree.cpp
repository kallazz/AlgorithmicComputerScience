#include "BinarySearchTree.hpp"

#include <iostream>

BinarySearchTree::BinarySearchTree() : root_(nullptr), keyComparisons_(0), pointerOperations_(0), printFlag_(false) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root_);
}

void BinarySearchTree::insertNode(const int key) {
    printIfFlagSet("insert " + std::to_string(key) + '\n');
    insertNode(root_, key);
}

void BinarySearchTree::insertNode(Node *&root, const int key) {
    if (root == nullptr) {
        pointerOperations_++;
        root = new Node(key);
        return;
    }

    keyComparisons_++;
    if (key < root->key) {
        insertNode(root->left, key);
    } else if (key > root->key) {
        keyComparisons_++;
        insertNode(root->right, key);
    } else {
        keyComparisons_++;
        printIfFlagSet("Key " + std::to_string(key) + " already exists in the tree.\n");
    }
}

void BinarySearchTree::deleteNode(const int key) {
    printIfFlagSet("delete " + std::to_string(key) + '\n');
    deleteNode(root_, key);
}

void BinarySearchTree::deleteNode(Node *&root, const int key) {
    pointerOperations_++;
    if (root == nullptr) {
        printIfFlagSet("Key " + std::to_string(key) + " was not found in the tree\n");
        return;
    }

    keyComparisons_++;
    if (key < root->key) {
        deleteNode(root->left, key);
    } else if (key > root->key) {
        keyComparisons_++;
        deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            pointerOperations_ += 2;
            Node *nodeToRemove = root;
            root = root->right;
            delete nodeToRemove;
        } else if (root->right == nullptr) {
            pointerOperations_ += 2;
            Node *nodeToRemove = root;
            root = root->left;
            delete nodeToRemove;
        } else {
            pointerOperations_++;
            Node *&minValueNode = findMinValueNode(root->right);
            root->key = minValueNode->key;
            deleteNode(minValueNode, minValueNode->key);
        }
    }
}

Node *&BinarySearchTree::findMinValueNode(Node *&root) {
    pointerOperations_++;
    if (root == nullptr) {
        std::cout << "Min value node not found.\n";
        return root;
    } else if (root->left == nullptr) {
        return root;
    } else {
        return findMinValueNode(root->left);
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

long long BinarySearchTree::getKeyComparisons() const {
    return keyComparisons_;
}

long long BinarySearchTree::getPointerOperations() const {
    return pointerOperations_;
}

void BinarySearchTree::setPrintFlag(const bool value) {
    printFlag_ = value;
}

void BinarySearchTree::print() const {
    std::string leftTrace(1000, ' ');
    std::string rightTrace(1000, ' ');
    printTree(root_, 10, '-', leftTrace, rightTrace);
}

void BinarySearchTree::printTree(const Node *root, const int depth, const char prefix, std::string &leftTrace, std::string &rightTrace) const {
    if (root == nullptr)
        return;

    if (root->left != nullptr) {
        printTree(root->left, depth + 1, '/', leftTrace, rightTrace);
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
        printTree(root->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}

void BinarySearchTree::printIfFlagSet(const std::string &text) const {
    if (printFlag_) {
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
