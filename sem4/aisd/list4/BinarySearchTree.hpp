#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "Tree.hpp"

#include <string>

struct Node {
    int key;
    Node *left, *right;

    Node(const int key) : key(key), left(nullptr), right(nullptr) {}
};

class BinarySearchTree : public Tree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insertNode(const int key) override;
    void deleteNode(const int key) override;
    int height() const override;
    void print() const override;
    long long getKeyComparisons() const override;
    long long getPointerOperations() const override;
    void setPrintFlag(const bool value);

private:
    Node *root_;
    long long keyComparisons_;
    long long pointerOperations_;
    bool printFlag_;

    Node* deleteNode(Node *root, const int key);
    Node *findMinValueNode(Node *node);
    int height(const Node *root) const;

    void printTree(const Node *root, const int depth, const char prefix, std::string &leftTrace, std::string &rightTrace) const;
    void printIfFlagSet(const std::string &text) const;
    void destroyTree(Node *root);
};

#endif // BINARY_SEARCH_TREE_HPP