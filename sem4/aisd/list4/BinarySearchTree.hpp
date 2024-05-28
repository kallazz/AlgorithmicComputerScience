#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <string>

struct Node {
    int key;
    Node *left, *right;

    Node(const int key) : key(key), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insertNode(const int key, int &keyComparisons, int &pointerOperations, const bool printFlag = false);
    void deleteNode(const int key, int &keyComparisons, int &pointerOperations, const bool printFlag = false);
    int height() const;
    void print() const;

private:
    Node *root_;

    void insertNode(Node *&root, const int key, int &keyComparisons, int &pointerOperations, const bool printFlag);
    void deleteNode(Node *&root, const int key, int &keyComparisons, int &pointerOperations, const bool printFlag);
    Node *&findMinValueNode(Node *&root, int &pointerOperations) const;
    int height(const Node *root) const;
    void print(const Node *root, const int depth, const char prefix, std::string &leftTrace, std::string &rightTrace) const;
    void printIfFlagSet(const std::string &text, const bool printFlag) const;
    void destroyTree(Node *root);
};

#endif // BINARY_SEARCH_TREE_HPP