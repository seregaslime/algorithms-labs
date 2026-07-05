#ifndef TREE_H
#define TREE_H

// Структура узла дерева 
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Основные операции BST
Node* createNode(int key);
Node* insertBST(Node* root, int key);
Node* searchBST(Node* root, int key);
Node* deleteBST(Node* root, int key);
void printTree(Node* root, int space);
int getHeight(Node* root);
int countNodes(Node* root);
void inorderTraversal(Node* root);
void deleteTree(Node* root);

// Рандомизированное дерево 
Node* insertRandomized(Node* root, int key);
Node* mergeTrees(Node* left, Node* right);  
void splitTree(Node* root, int key, Node** left, Node** right); 
void deleteRandomizedTree(Node* root);

// Функции вывода дерева
void printTreeWrapper(Node* root);

// Измененная функция: подсчет нечетных чисел в узлах с двумя поддеревьями
int countOddNodesWithTwoSubtrees(Node* root);
void countOddNodesWithTwoSubtreesWrapper(Node* root);

#endif