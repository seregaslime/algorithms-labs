#include "tree.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Создание нового узла
Node* createNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// BST

Node* insertBST(Node* root, int key) {
    if (root == nullptr) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insertBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }

    return root;
}

Node* searchBST(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return searchBST(root->left, key);
    }

    return searchBST(root->right, key);
}

Node* findMin(Node* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* deleteBST(Node* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }

    return root;
}

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}

int countNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Рандом дерево
void splitTree(Node* root, int key, Node** left, Node** right) {
    if (root == nullptr) {
        *left = nullptr;
        *right = nullptr;
        return;
    }

    if (root->key < key) {
        // Текущий узел идет в левое дерево
        *left = root;
        Node* tempRight = nullptr;
        splitTree(root->right, key, &(root->right), &tempRight);
        *right = tempRight;
    }
    else {
        // Текущий узел идет в правое дерево
        *right = root;
        Node* tempLeft = nullptr;
        splitTree(root->left, key, &tempLeft, &(root->left));
        *left = tempLeft;
    }
}

Node* mergeTrees(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    // Случайно выбираем корень из left или right
    if (rand() % (countNodes(left) + countNodes(right)) < countNodes(left)) {
        // Корнем становится корень left
        left->right = mergeTrees(left->right, right);
        return left;
    }
    else {
        // Корнем становится корень right
        right->left = mergeTrees(left, right->left);
        return right;
    }
}


Node* insertRandomized(Node* root, int key) {
    // Случайно решаем, будет ли новый узел корнем
    if (root == nullptr || (rand() % (countNodes(root) + 1)) == 0) {
        // Создаем новый узел как корень
        Node* newNode = createNode(key);

        if (root != nullptr) {
            // Разделяем существующее дерево по новому ключу
            Node* left = nullptr;
            Node* right = nullptr;
            splitTree(root, key, &left, &right);

            // Присоединяем полученные поддеревья как детей нового узла
            newNode->left = left;
            newNode->right = right;
        }

        return newNode;
    }

    // Рекурсивно вставляем в соответствующее поддерево
    if (key < root->key) {
        root->left = insertRandomized(root->left, key);
    }
    else {
        root->right = insertRandomized(root->right, key);
    }

    return root;
}

/**
 * Удаление из рандомизированного дерева
 */
Node* deleteRandomized(Node* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->key == key) {
        // Нашли узел для удаления
        Node* result = mergeTrees(root->left, root->right);
        delete root;
        return result;
    }

    if (key < root->key) {
        root->left = deleteRandomized(root->left, key);
    }
    else {
        root->right = deleteRandomized(root->right, key);
    }

    return root;
}


void printTree(Node* root, int space) {
    const int COUNT = 4;

    if (root == nullptr) {
        return;
    }

    space += COUNT;
    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) {
        std::cout << " ";
    }
    std::cout << root->key;

    printTree(root->left, space);
}

void printTreeWrapper(Node* root) {
    std::cout << "\nСтруктура дерева:\n";
    std::cout << "================\n";
    if (root == nullptr) {
        std::cout << "Дерево пустое\n";
    }
    else {
        printTree(root, 0);
    }
    std::cout << "\n================\n";
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void deleteRandomizedTree(Node* root) {
    deleteTree(root); 
}

// Подсчет нечетных чисел в узлах с двумя поддеревьями
int countOddNodesWithTwoSubtrees(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    
    int count = 0;
    
    // Проверяем, имеет ли текущий узел оба поддерева
    if (root->left != nullptr && root->right != nullptr) {
        // Проверяем, является ли ключ нечетным числом
        if (root->key % 2 != 0) {
            count = 1;
            cout << "  Найден узел с двумя поддеревьями и нечетным ключом: " << root->key << endl;
        }
    }
    
    // Рекурсивно обходим левое и правое поддеревья
    count += countOddNodesWithTwoSubtrees(root->left);
    count += countOddNodesWithTwoSubtrees(root->right);
    
    return count;
}

// Обертка 
void countOddNodesWithTwoSubtreesWrapper(Node* root) {
    cout << "\nПодсчет нечетных чисел в узлах с двумя поддеревьями:\n";
    cout << "===================================================\n";
    
    if (root == nullptr) {
        cout << "  Дерево пустое\n";
        cout << "  Найдено узлов: 0\n";
        return;
    }
    
    int count = countOddNodesWithTwoSubtrees(root);
    
    cout << "\nИтоговый результат:\n";
    cout << "  Всего узлов в дереве: " << countNodes(root) << endl;
    cout << "  Найдено узлов с двумя поддеревьями и нечетным ключом: " << count << endl;
    cout << "===================================================\n";
}