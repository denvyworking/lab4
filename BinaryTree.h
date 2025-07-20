#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <functional>
#include <stdexcept>
#include <string>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void clear(Node* node);
    Node* insert(Node* node, const T& data);
    Node* remove(Node* node, const T& data);
    bool contains(Node* node, const T& data) const;
    void inOrder(Node* node, std::vector<T>& result) const;
    void preOrder(Node* node, std::vector<T>& result) const;
    void postOrder(Node* node, std::vector<T>& result) const;
    Node* copyTree(Node* node) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);

    void insert(const T& data);
    void remove(const T& data);
    bool contains(const T& data) const;
    bool isEmpty() const;

    std::vector<T> inOrder() const;
    std::vector<T> preOrder() const;
    std::vector<T> postOrder() const;

    BinaryTree<T> map(std::function<T(const T&)> func) const;
    BinaryTree<T> where(std::function<bool(const T&)> predicate) const;

    std::string toString(const std::string& traversalType = "inOrder") const;
    void fromString(const std::string& str, const std::string& traversalType = "inOrder");
};

#endif
