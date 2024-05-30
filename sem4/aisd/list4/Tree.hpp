#ifndef TREE_HPP
#define TREE_HPP

class Tree {
public:
    virtual void insertNode(const int key) = 0;
    virtual void deleteNode(const int key) = 0;
    virtual int height() const = 0;
    virtual void print() const = 0;
    virtual long long getKeyComparisons() const = 0;
    virtual long long getPointerOperations() const = 0;
    virtual ~Tree() = default;
};

#endif // TREE_HPP