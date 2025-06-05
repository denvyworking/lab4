#include "BinaryTree.h"
#include <algorithm>

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    root = copyTree(other.root);
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    clear(root);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) {
    if (this != &other) {
        clear(root);
        root = copyTree(other.root);
    }
    return *this;
}

template <typename T>
void BinaryTree<T>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insert(Node* node, const T& data) {
    if (!node) {
        return new Node(data);
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    return node;
}

template <typename T>
void BinaryTree<T>::insert(const T& data) {
    root = insert(root, data);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::remove(Node* node, const T& data) {
    if (!node) return nullptr;
    if (data < node->data) {
        node->left = remove(node->left, data);
    } else if (data > node->data) {
        node->right = remove(node->right, data);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = node->right;
        while (temp->left) {
            temp = temp->left;
        }
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }
    return node;
}

template <typename T>
void BinaryTree<T>::remove(const T& data) {
    root = remove(root, data);
}

template <typename T>
bool BinaryTree<T>::contains(Node* node, const T& data) const {
    if (!node) return false;
    if (data == node->data) return true;
    return data < node->data ? contains(node->left, data) : contains(node->right, data);
}

template <typename T>
bool BinaryTree<T>::contains(const T& data) const {
    return contains(root, data);
}

template <typename T>
bool BinaryTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::inOrder(Node* node, std::vector<T>& result) const {
    if (node) {
        inOrder(node->left, result);
        result.push_back(node->data);
        inOrder(node->right, result);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::inOrder() const {
    std::vector<T> result;
    inOrder(root, result);
    return result;
}

template <typename T>
void BinaryTree<T>::preOrder(Node* node, std::vector<T>& result) const {
    if (node) {
        result.push_back(node->data);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::preOrder() const {
    std::vector<T> result;
    preOrder(root, result);
    return result;
}

template <typename T>
void BinaryTree<T>::postOrder(Node* node, std::vector<T>& result) const {
    if (node) {
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->data);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::postOrder() const {
    std::vector<T> result;
    postOrder(root, result);
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::map(std::function<T(const T&)> func) const {
    BinaryTree<T> newTree;
    std::vector<T> elements = inOrder();
    for (const T& elem : elements) {
        newTree.insert(func(elem));
    }
    return newTree;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::where(std::function<bool(const T&)> predicate) const {
    BinaryTree<T> newTree;
    std::vector<T> elements = inOrder();
    for (const T& elem : elements) {
        if (predicate(elem)) {
            newTree.insert(elem);
        }
    }
    return newTree;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(Node* node) const {
    if (!node) return nullptr;
    Node* newNode = new Node(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

template <typename T>
std::string BinaryTree<T>::toString(const std::string& traversalType) const {
    std::vector<T> elements;
    if (traversalType == "inOrder") {
        elements = inOrder();
    } else if (traversalType == "preOrder") {
        elements = preOrder();
    } else if (traversalType == "postOrder") {
        elements = postOrder();
    } else {
        throw std::invalid_argument("Invalid traversal type");
    }

    std::string result;
    for (const T& elem : elements) {
        result += std::to_string(elem) + " ";
    }
    return result;
}

template <typename T>
void BinaryTree<T>::fromString(const std::string& str, const std::string& traversalType) {
    clear(root);
    std::vector<T> elements;
    size_t pos = 0;
    while (pos < str.size()) {
        size_t endPos = str.find(' ', pos);
        if (endPos == std::string::npos) endPos = str.size();
        std::string token = str.substr(pos, endPos - pos);
        if (!token.empty()) {
            elements.push_back(std::stoi(token));
        }
        pos = endPos + 1;
    }

    if (traversalType == "inOrder") {
        for (const T& elem : elements) {
            insert(elem);
        }
    } else {
        throw std::invalid_argument("Only inOrder traversal is supported for fromString");
    }
}
