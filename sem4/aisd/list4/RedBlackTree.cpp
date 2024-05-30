#include "RedBlackTree.hpp"

#include <iostream>

RedBlackTree::RedBlackTree()
    : NIL_NODE_(new RedBlackNode(0, 0, nullptr, nullptr, nullptr)), root_(NIL_NODE_), keyComparisons_(0),
      pointerOperations_(0), printFlag_(false) {}

RedBlackTree::~RedBlackTree() {
    destroyTree(root_);
    delete NIL_NODE_;
}

void RedBlackTree::insertNode(const int key) {
    printIfFlagSet("insert " + std::to_string(key) + '\n');

    pointerOperations_++;
    RedBlackNode *currentNode = root_;
    RedBlackNode *currentNodeParent = nullptr;

    while (currentNode != NIL_NODE_) {
        currentNodeParent = currentNode;
        if (key < currentNode->key) {
            keyComparisons_++;
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

    RedBlackNode *newRedBlackNode = new RedBlackNode(key, 1, currentNodeParent, NIL_NODE_, NIL_NODE_);
    pointerOperations_++;
    if (currentNodeParent == nullptr) {
        root_ = newRedBlackNode;
    } else if (key < currentNodeParent->key) {
        keyComparisons_++;
        currentNodeParent->left = newRedBlackNode;
    } else {
        keyComparisons_++;
        currentNodeParent->right = newRedBlackNode;
    }

    if (newRedBlackNode->parent == nullptr) {
        newRedBlackNode->color = 0;
        return;
    }

    if (newRedBlackNode->parent->parent == nullptr) {
        return;
    }

    insertFixup(newRedBlackNode);
}

void RedBlackTree::insertFixup(RedBlackNode *node) {
    while (node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            pointerOperations_++;
            RedBlackNode *uncle = node->parent->parent->right;

            if (uncle->color == 1) {
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                pointerOperations_++;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    pointerOperations_++;
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotate(node->parent->parent);
            }
        } else {
            pointerOperations_++;
            RedBlackNode *uncle = node->parent->parent->left;

            if (uncle->color == 1) {
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                pointerOperations_++;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    pointerOperations_++;
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotate(node->parent->parent);
            }
        }

        if (node == root_) {
            break;
        }
    }

    root_->color = 0;
}

void RedBlackTree::leftRotate(RedBlackNode *node) {
    pointerOperations_ += 6;
    RedBlackNode *rightNode = node->right;
    node->right = rightNode->left;
    if (rightNode->left != NIL_NODE_) {
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

void RedBlackTree::rightRotate(RedBlackNode *node) {
    pointerOperations_ += 6;
    RedBlackNode *leftNode = node->left;
    node->left = leftNode->right;
    if (leftNode->right != NIL_NODE_) {
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

void RedBlackTree::deleteNode(const int key) {
    printIfFlagSet("delete " + std::to_string(key) + '\n');

    pointerOperations_++;
    RedBlackNode *nodeToDelete = search(key);

    if (nodeToDelete == NIL_NODE_) {
        printIfFlagSet("Key " + std::to_string(key) + " was not found in the tree\n");
        return;
    }

    int originalColor = nodeToDelete->color;
    RedBlackNode *childRedBlackNode = nullptr;

    pointerOperations_++;
    if (nodeToDelete->left == NIL_NODE_) {
        childRedBlackNode = nodeToDelete->right;
        transplant(nodeToDelete, nodeToDelete->right);
    } else if (nodeToDelete->right == NIL_NODE_) {
        childRedBlackNode = nodeToDelete->left;
        transplant(nodeToDelete, nodeToDelete->left);
    } else {
        RedBlackNode *minRedBlackNode = findMinValueNode(nodeToDelete->right);
        originalColor = minRedBlackNode->color;
        childRedBlackNode = minRedBlackNode->right;

        pointerOperations_++;
        if (minRedBlackNode->parent == nodeToDelete) {
            childRedBlackNode->parent = minRedBlackNode;
        } else {
            transplant(minRedBlackNode, minRedBlackNode->right);
            minRedBlackNode->right = nodeToDelete->right;
            minRedBlackNode->right->parent = minRedBlackNode;
        }

        pointerOperations_++;
        transplant(nodeToDelete, minRedBlackNode);
        minRedBlackNode->left = nodeToDelete->left;
        minRedBlackNode->left->parent = minRedBlackNode;
        minRedBlackNode->color = nodeToDelete->color;
    }

    pointerOperations_++;
    delete nodeToDelete;

    if (originalColor == 0) {
        deleteFixup(childRedBlackNode);
    }
}

RedBlackNode *RedBlackTree::search(const int key) {
    pointerOperations_++;
    RedBlackNode *currentNode = root_;

    while (currentNode != NIL_NODE_ && key != currentNode->key) {
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

RedBlackNode *RedBlackTree::findMinValueNode(RedBlackNode *node) {
    while (node->left != NIL_NODE_) {
        pointerOperations_++;
        node = node->left;
    }

    return node;
}

void RedBlackTree::deleteFixup(RedBlackNode *node) {
    RedBlackNode *sibling;
    while (node != root_ && node->color == 0) {
        if (node == node->parent->left) {
            pointerOperations_++;
            sibling = node->parent->right;
            if (sibling->color == 1) {
                pointerOperations_++;
                sibling->color = 0;
                node->parent->color = 1;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }

            pointerOperations_++;
            if (sibling->left->color == 0 && sibling->right->color == 0) {
                sibling->color = 1;
                node = node->parent;
            } else {
                if (sibling->right->color == 0) {
                    sibling->left->color = 0;
                    sibling->color = 1;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }

                pointerOperations_++;
                sibling->color = node->parent->color;
                node->parent->color = 0;
                sibling->right->color = 0;
                leftRotate(node->parent);
                node = root_;
            }
        } else {
            pointerOperations_++;
            sibling = node->parent->left;
            if (sibling->color == 1) {
                pointerOperations_++;
                sibling->color = 0;
                node->parent->color = 1;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }

            pointerOperations_++;
            if (sibling->left->color == 0 && sibling->right->color == 0) {
                sibling->color = 1;
                node = node->parent;
            } else {
                if (sibling->left->color == 0) {
                    sibling->right->color = 0;
                    sibling->color = 1;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }

                pointerOperations_++;
                sibling->color = node->parent->color;
                node->parent->color = 0;
                sibling->left->color = 0;
                rightRotate(node->parent);
                node = root_;
            }
        }
    }

    node->color = 0;
}

void RedBlackTree::transplant(RedBlackNode *u, RedBlackNode *v) {
    pointerOperations_ += 2;
    if (u->parent == nullptr) {
        root_ = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

int RedBlackTree::height() const {
    return height(root_);
}

int RedBlackTree::height(const RedBlackNode *root) const {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

long long RedBlackTree::getKeyComparisons() const {
    return keyComparisons_;
}

long long RedBlackTree::getPointerOperations() const {
    return pointerOperations_;
}

void RedBlackTree::setPrintFlag(const bool value) {
    printFlag_ = value;
}

void RedBlackTree::print() const {
    std::string leftTrace(1000, ' ');
    std::string rightTrace(1000, ' ');
    printTree(root_, 10, '-', leftTrace, rightTrace);
}

void RedBlackTree::printTree(const RedBlackNode *root, const int depth, const char prefix, std::string &leftTrace,
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

    if (root == NIL_NODE_) {
        std::cout << "o\n";
    } else if (root->color == 1) {
        std::cout << COLOR_RED << "[" << root->key << "]" << COLOR_DEFAULT << "\n";
    } else {
        std::cout << "[" << root->key << "]\n";
    }
    leftTrace[depth] = ' ';
    if (root->right != nullptr) {
        rightTrace[depth] = '|';
        printTree(root->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}

void RedBlackTree::printIfFlagSet(const std::string &text) const {
    if (printFlag_) {
        std::cout << text;
    }
}

void RedBlackTree::destroyTree(RedBlackNode *root) {
    if (root != nullptr && root != NIL_NODE_) {
        destroyTree(root->left);
        destroyTree(root->right);
    }
    if (root != NIL_NODE_) {
        delete root;
    }
}