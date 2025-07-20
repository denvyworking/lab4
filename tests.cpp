#include <gtest/gtest.h>
#include "BinaryTree.h"
#include "BinaryTree.cpp" // Для явного инстанцирования шаблона

// Тесты для вставки и проверки наличия элементов
TEST(BinaryTreeTest, InsertAndContains) {
    BinaryTree<int> tree;
    EXPECT_FALSE(tree.contains(5));
    tree.insert(5);
    EXPECT_TRUE(tree.contains(5));
    tree.insert(3);
    tree.insert(7);
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_FALSE(tree.contains(10));
}

// Тесты для удаления элементов
TEST(BinaryTreeTest, Remove) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.remove(3);
    EXPECT_FALSE(tree.contains(3));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(7));
    tree.remove(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(7));
}

// Тесты для обходов дерева
TEST(BinaryTreeTest, Traversals) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // In-order: 2 3 4 5 6 7 8
    std::vector<int> expectedInOrder = {2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(tree.inOrder(), expectedInOrder);

    // Pre-order: 5 3 2 4 7 6 8
    std::vector<int> expectedPreOrder = {5, 3, 2, 4, 7, 6, 8};
    EXPECT_EQ(tree.preOrder(), expectedPreOrder);

    // Post-order: 2 4 3 6 8 7 5
    std::vector<int> expectedPostOrder = {2, 4, 3, 6, 8, 7, 5};
    EXPECT_EQ(tree.postOrder(), expectedPostOrder);
}

// Тесты для map и where
TEST(BinaryTreeTest, MapAndWhere) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    // Умножаем все элементы на 2
    auto mappedTree = tree.map([](int x) { return x * 2; });
    std::vector<int> expectedMapped = {6, 10, 14};
    EXPECT_EQ(mappedTree.inOrder(), expectedMapped);

    // Фильтруем только четные числа (в исходном дереве их нет)
    auto filteredTree = tree.where([](int x) { return x % 2 == 0; });
    EXPECT_TRUE(filteredTree.inOrder().empty());

    // Добавляем четное число и проверяем фильтрацию
    tree.insert(4);
    filteredTree = tree.where([](int x) { return x % 2 == 0; });
    std::vector<int> expectedFiltered = {4};
    EXPECT_EQ(filteredTree.inOrder(), expectedFiltered);
}

// Тесты для сериализации и десериализации
TEST(BinaryTreeTest, Serialization) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    // Сохраняем дерево в строку (in-order)
    std::string serialized = tree.toString("inOrder");
    EXPECT_EQ(serialized, "3 5 7 ");

    // Загружаем дерево из строки
    BinaryTree<int> newTree;
    newTree.fromString(serialized, "inOrder");
    EXPECT_EQ(newTree.inOrder(), tree.inOrder());
}

// Тест на пустое дерево
TEST(BinaryTreeTest, EmptyTree) {
    BinaryTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_TRUE(tree.inOrder().empty());
    EXPECT_TRUE(tree.preOrder().empty());
    EXPECT_TRUE(tree.postOrder().empty());
}

// Тест на копирование дерева
TEST(BinaryTreeTest, CopyConstructor) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BinaryTree<int> copyTree(tree);
    EXPECT_EQ(copyTree.inOrder(), tree.inOrder());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
