#include <iostream>
#include "BinaryTree.h"
#include "BinaryTree.cpp" // Для явного инстанцирования шаблона

int main() {
    BinaryTree<int> tree;

    // Вставка элементов
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Проверка содержимого
    std::cout << "In-order traversal: ";
    for (int elem : tree.inOrder()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Проверка поиска
    std::cout << "Contains 4: " << (tree.contains(4) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 10: " << (tree.contains(10) ? "Yes" : "No") << std::endl;

    // Удаление элемента
    tree.remove(3);
    std::cout << "After removing 3 (in-order): ";
    for (int elem : tree.inOrder()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Пример map и where
    BinaryTree<int> mappedTree = tree.map([](int x) { return x * 2; });
    std::cout << "Mapped tree (in-order): ";
    for (int elem : mappedTree.inOrder()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    BinaryTree<int> filteredTree = tree.where([](int x) { return x % 2 == 0; });
    std::cout << "Filtered tree (even numbers, x % 2 == 0): ";
    for (int elem : filteredTree.inOrder()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Сохранение и чтение из строки
    std::string serialized = tree.toString("inOrder");
    std::cout << "Serialized tree: " << serialized << std::endl;

    BinaryTree<int> newTree;
    newTree.fromString(serialized, "inOrder");
    std::cout << "Deserialized tree (in-order): ";
    for (int elem : newTree.inOrder()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
