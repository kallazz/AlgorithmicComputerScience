#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "Tree.hpp"

#include <string>

struct RedBlackNode {
    int key;
    int color; // 1 - red, 0 - black
    RedBlackNode *parent, *left, *right;

    RedBlackNode(const int key, const int color, RedBlackNode *parent, RedBlackNode *left, RedBlackNode *right)
        : key(key), color(color), parent(parent), left(left), right(right) {}
};

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_DEFAULT = "\033[0m";

class RedBlackTree : public Tree {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insertNode(const int key, const bool printFlag = false) override;
    void deleteNode(const int key, const bool printFlag = false) override;
    int height() const override;
    void print() const override;

    long long getKeyComparisons() const override;
    long long getPointerOperations() const override;

private:
    RedBlackNode *NIL_NODE_;
    RedBlackNode *root_;
    long long keyComparisons_;
    long long pointerOperations_;

    void insertFixup(RedBlackNode *node);
    void deleteFixup(RedBlackNode *node);
    void leftRotate(RedBlackNode *node);
    void rightRotate(RedBlackNode *node);
    void transplant(RedBlackNode *v, RedBlackNode *u);
    RedBlackNode *search(const int key);
    RedBlackNode *findMinValueNode(RedBlackNode *node);
    int height(const RedBlackNode *root) const;

    void printTree(const RedBlackNode *root, const int depth, const char prefix, std::string &leftTrace,
                   std::string &rightTrace) const;
    void printIfFlagSet(const std::string &text, const bool printFlag) const;
    void destroyTree(RedBlackNode *root);
};

#endif // RED_BLACK_TREE_HPP
