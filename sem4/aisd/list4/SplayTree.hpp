
#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "Tree.hpp"

#include <string>

struct SplayNode {
    int key;
    SplayNode *parent, *left, *right;

    SplayNode(const int key) : key(key), left(nullptr), right(nullptr) {}
};

class SplayTree : public Tree {
public:
    SplayTree();
    ~SplayTree();

    void insertNode(const int key) override;
    void deleteNode(const int key) override;
    int height() const override;
    void print() const override;
    long long getKeyComparisons() const override;
    long long getPointerOperations() const override;
    void setPrintFlag(const bool value);

private:
    SplayNode *root_;
    int keyComparisons_;
    int pointerOperations_;
    bool printFlag_;

    void splay(SplayNode *node);
    void leftRotate(SplayNode *node);
    void rightRotate(SplayNode *node);
    SplayNode *search(const int key);
    void split(SplayNode *&node, SplayNode *&leftSubtree, SplayNode *&rightSubtree);
    SplayNode *join(SplayNode *leftSubtree, SplayNode *rightSubtree);
    SplayNode *findMinValueNode(SplayNode *node);
    SplayNode *findMaxValueNode(SplayNode *node);
    int height(const SplayNode *root) const;

    void printTree(const SplayNode *root, const int depth, const char prefix, std::string &leftTrace,
                   std::string &rightTrace) const;
    void printIfFlagSet(const std::string &text) const;
    void destroyTree(SplayNode *root);
};

#endif // SPLAY_TREE_HPP
