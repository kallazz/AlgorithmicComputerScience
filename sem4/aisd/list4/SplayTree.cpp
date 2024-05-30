#include "SplayTree.hpp"

#include <iostream>

SplayTree::SplayTree() : root_(nullptr), keyComparisons_(0), pointerOperations_(0), printFlag_(false) {}

SplayTree::~SplayTree() {
    destroyTree(root_);
}

void SplayTree::insertNode(const int key) {
    printIfFlagSet("insert " + std::to_string(key) + '\n');

    pointerOperations_++;
    SplayNode *currentNode = root_;
    SplayNode *currentNodeParent = nullptr;

    while (currentNode != nullptr) {
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
            printIfFlagSet("Key " + std::to_string(key) + " already exists in the tree.\n");
            return;
        }
    }

    currentNode = new SplayNode(key);
    currentNode->parent = currentNodeParent;
    pointerOperations_++;
    if (currentNodeParent == nullptr) {
        root_ = currentNode;
    } else if (key < currentNodeParent->key) {
        keyComparisons_++;
        currentNodeParent->left = currentNode;
    } else {
        keyComparisons_++;
        currentNodeParent->right = currentNode;
    }

    splay(currentNode);
}

void SplayTree::splay(SplayNode *node) {
    while (node->parent != nullptr) {
        if (node->parent->parent == nullptr) {
            if (node == node->parent->left) {
                // Zig Rotation
                rightRotate(node->parent);
            } else {
                // Zag Rotation
                leftRotate(node->parent);
            }
        } else if (node == node->parent->left && node->parent == node->parent->parent->left) {
            // Zig-Zig Rotation
            rightRotate(node->parent->parent);
            rightRotate(node->parent);
        } else if (node == node->parent->right && node->parent == node->parent->parent->right) {
            // Zag-Zag Rotation
            leftRotate(node->parent->parent);
            leftRotate(node->parent);
        } else if (node == node->parent->right && node->parent == node->parent->parent->left) {
            // Zig-Zag Rotation
            leftRotate(node->parent);
            rightRotate(node->parent);
        } else {
            // Zag-Zig Rotation
            rightRotate(node->parent);
            leftRotate(node->parent);
        }
    }
}

void SplayTree::deleteNode(const int key) {
    printIfFlagSet("delete " + std::to_string(key) + '\n');

    pointerOperations_++;
    SplayNode *nodeToDelete = search(key);
    SplayNode *leftSubtree, *rightSubtree;

    if (nodeToDelete == nullptr) {
        printIfFlagSet("Key " + std::to_string(key) + " was not found in the tree\n");
        return;
    }

    split(nodeToDelete, leftSubtree, rightSubtree);
    if (leftSubtree->left != nullptr) {
        pointerOperations_++;
        leftSubtree->left->parent = nullptr;
    }
    root_ = join(leftSubtree->left, rightSubtree);
    pointerOperations_++;
    delete leftSubtree;
    leftSubtree = nullptr;
}

void SplayTree::split(SplayNode *&node, SplayNode *&leftSubtree, SplayNode *&rightSubtree) {
    splay(node);

    pointerOperations_ += 3;
    if (node->right != nullptr) {
        rightSubtree = node->right;
        rightSubtree->parent = nullptr;
    } else {
        rightSubtree = nullptr;
    }
    leftSubtree = node;
    leftSubtree->right = nullptr;
    node = nullptr;
}

SplayNode *SplayTree::join(SplayNode *leftSubtree, SplayNode *rightSubtree) {
    if (leftSubtree == nullptr) {
        return rightSubtree;
    }
    if (rightSubtree == nullptr) {
        return leftSubtree;
    }

    pointerOperations_ += 3;
    SplayNode *maxNodeFromLeftSubtree = findMaxValueSplayNode(leftSubtree);
    splay(maxNodeFromLeftSubtree);
    maxNodeFromLeftSubtree->right = rightSubtree;
    rightSubtree->parent = maxNodeFromLeftSubtree;
    return maxNodeFromLeftSubtree;
}

SplayNode *SplayTree::findMaxValueSplayNode(SplayNode *node) {
    while (node->right != nullptr) {
        pointerOperations_++;
        node = node->right;
    }
    return node;
}

SplayNode *SplayTree::search(const int key) {
    pointerOperations_++;
    SplayNode *currentNode = root_;

    while (currentNode != nullptr && key != currentNode->key) {
        keyComparisons_ += 2;
        pointerOperations_++;
        if (key < currentNode->key) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    return currentNode;
}

void SplayTree::leftRotate(SplayNode *node) {
    pointerOperations_ += 6;
    SplayNode *rightNode = node->right;
    node->right = rightNode->left;
    if (rightNode->left != nullptr) {
        pointerOperations_++;
        rightNode->left->parent = node;
    }
    rightNode->parent = node->parent;
    if (node->parent == nullptr) {
        root_ = rightNode;
    } else if (node == node->parent->left) {
        node->parent->left = rightNode;
    } else {
        node->parent->right = rightNode;
    }
    rightNode->left = node;
    node->parent = rightNode;
}

void SplayTree::rightRotate(SplayNode *node) {
    pointerOperations_ += 6;
    SplayNode *leftNode = node->left;
    node->left = leftNode->right;
    if (leftNode->right != nullptr) {
        pointerOperations_++;
        leftNode->right->parent = node;
    }
    leftNode->parent = node->parent;
    if (node->parent == nullptr) {
        root_ = leftNode;
    } else if (node == node->parent->right) {
        node->parent->right = leftNode;
    } else {
        node->parent->left = leftNode;
    }
    leftNode->right = node;
    node->parent = leftNode;
}

int SplayTree::height() const {
    return height(root_);
}

int SplayTree::height(const SplayNode *root) const {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

long long SplayTree::getKeyComparisons() const {
    return keyComparisons_;
}

long long SplayTree::getPointerOperations() const {
    return pointerOperations_;
}

void SplayTree::setPrintFlag(const bool value) {
    printFlag_ = value;
}

void SplayTree::print() const {
    std::string leftTrace(1000, ' ');
    std::string rightTrace(1000, ' ');
    printTree(root_, 10, '-', leftTrace, rightTrace);
}

void SplayTree::printTree(const SplayNode *root, const int depth, const char prefix, std::string &leftTrace,
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

void SplayTree::printIfFlagSet(const std::string &text) const {
    if (printFlag_) {
        std::cout << text;
    }
}

void SplayTree::destroyTree(SplayNode *root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
    }
    delete root;
}