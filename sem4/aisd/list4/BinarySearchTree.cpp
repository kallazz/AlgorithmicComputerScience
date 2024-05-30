#include "BinarySearchTree.hpp"

#include <iostream>

BinarySearchTree::BinarySearchTree() : root_(nullptr), keyComparisons_(0), pointerOperations_(0), printFlag_(false) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root_);
}

void BinarySearchTree::insertNode(const int key) {
    printIfFlagSet("insert " + std::to_string(key) + '\n');

    pointerOperations_++;
    Node *currentNode = root_;
    Node *currentNodeParent = nullptr;

    while (currentNode != nullptr) {
        pointerOperations_++;
        currentNodeParent = currentNode;
        keyComparisons_++;
        if (key < currentNode->key) {
            pointerOperations_++;
            currentNode = currentNode->left;
        } else if (key > currentNode->key) {
            keyComparisons_++;
            pointerOperations_++;
            currentNode = currentNode->right;
        } else {
            keyComparisons_++;
            printIfFlagSet("Key " + std::to_string(key) + " already exists in the tree.\n");
            return;
        }
    }

    Node *newNode = new Node(key);
    pointerOperations_ += 2;
    if (currentNodeParent == nullptr) {
        root_ = newNode;
    } else if (key < currentNodeParent->key) {
        keyComparisons_++;
        currentNodeParent->left = newNode;
    } else {
        keyComparisons_++;
        currentNodeParent->right = newNode;
    }
}

void BinarySearchTree::deleteNode(const int key) {
    printIfFlagSet("delete " + std::to_string(key) + '\n');
    root_ = deleteNode(root_, key);
}

Node *BinarySearchTree::deleteNode(Node *root, const int key) {
    if (root == nullptr) {
        printIfFlagSet("value " + std::to_string(key) + " not found in the tree\n");
        return root;
    }

    keyComparisons_++;
    if (key < root->key) {
        pointerOperations_++;
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        keyComparisons_++;
        pointerOperations_++;
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            pointerOperations_ += 2;
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            pointerOperations_ += 2;
            Node *temp = root->left;
            delete root;
            return temp;
        }

        pointerOperations_ += 3;
        Node *temp = findMinValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

Node *BinarySearchTree::findMinValueNode(Node *node) {
    while (node->left != nullptr) {
        pointerOperations_++;
        node = node->left;
    }
    return node;
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

void BinarySearchTree::printTree(const Node *root, const int depth, const char prefix, std::string &leftTrace,
                                 std::string &rightTrace) const {
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
        delete root;
    }
}
