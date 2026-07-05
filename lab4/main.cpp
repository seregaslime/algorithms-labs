#include "tree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


// Генерация уникальных случайных чисел
void generateUniqueNumbers(int* arr, int count) {
    const int MIN_VAL = 1;
    const int MAX_VAL = 190;

    // Создаем массив для отметки использованных чисел
    bool used[MAX_VAL - MIN_VAL + 1] = { false };
    int generated = 0;

    while (generated < count) {
        int num = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);

        if (!used[num - MIN_VAL]) {
            arr[generated] = num;
            used[num - MIN_VAL] = true;
            generated++;
        }
    }
}

// Демонстрация работы с деревом
void demonstrateStage1() {
    // Генерация массива из 20-25 уникальных элементов
    srand(time(0));
    int n = 20 + rand() % 6; // 20-25 элементов
    int* numbers = new int[n];
    generateUniqueNumbers(numbers, n);

    // Вывод сгенерированных чисел
    cout << "Сгенерированные числа: ";
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // 2. Создание дерева и вставка элементов
    cout << "\n Бинарное дерево поиска\n";
    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        root = insertBST(root, numbers[i]);
    }

    // Вывод дерева
    printTree(root, 0);

    // 3. Основные характеристики дерева
    cout << "\nВысота дерева: " << getHeight(root) << endl;
    cout << "Количество узлов: " << countNodes(root) << endl;

    // 4. Отсортированная последовательность
    cout << "\nОтсортированные ключи:\n   ";
    inorderTraversal(root);
    cout << endl;

    // 5. Демонстрация поиска
    cout << "\nПоиск:\n";
    for (int i = 0; i < 3; i++) {
        int searchKey = numbers[rand() % n];
        Node* found = searchBST(root, searchKey);
        if (found != nullptr) {
            cout << "   Число " << searchKey << " найдено в дереве\n";
        }
    }

    // 6. Демонстрация удаления
    cout << "\nУдаление:\n";
    // int deleteKey = numbers[rand() % n];
    int deleteKey = numbers[0];
    cout << "   Удаляем число: " << deleteKey << endl;
    root = deleteBST(root, deleteKey);

    cout << "   Дерево после удаления:\n";
    printTree(root, 0);

    cout << "\nКоличество узлов после удаления: " << countNodes(root) << endl;

    // 7. Измененная функция: подсчет нечетных чисел в узлах с двумя поддеревьями
    cout << "\nПодсчет нечетных чисел в узлах с двумя поддеревьями:\n";
    countOddNodesWithTwoSubtreesWrapper(root);

    // Очистка памяти
    deleteTree(root);
    delete[] numbers;
}

// ============ ФУНКЦИИ ДЛЯ ЭТАПА 2 ============

// Генерация уникальных случайных чисел
void generateUniqueNumbersLarge(int* arr, int count, int minVal, int maxVal) {

    // Создаем массив для отметки использованных чисел
    bool* used = new bool[maxVal - minVal + 1]();
    int generated = 0;

    while (generated < count) {
        int num = minVal + rand() % (maxVal - minVal + 1);

        if (!used[num - minVal]) {
            arr[generated] = num;
            used[num - minVal] = true;
            generated++;
        }
    }

    delete[] used;
}

// Построение и измерение деревьев
void buildAndMeasure(int* keys, int totalKeys, bool isSorted, const char* sequenceName) {
    const int steps = 12; // от 25 до 300 с шагом 25
    int heightsBST[steps] = { 0 };
    int heightsRandomized[steps] = { 0 };

    cout << "\n" << sequenceName << " КЛЮЧИ (" << (isSorted ? "ОТСОРТИРОВАННЫЕ" : "СЛУЧАЙНЫЕ") << ")" << endl;
    cout << "┌────────┬────────────┬─────────────────────────┐" << endl;
    cout << "│ Ключей │ Высота BST │Высота рандомизированного│" << endl;
    cout << "├────────┼────────────┼─────────────────────────┤" << endl;

    for (int step = 0; step < steps; step++) {
        int n = 25 * (step + 1);

        if (n > totalKeys) break;

        // Построение обычного BST
        Node* bstRoot = nullptr;
        for (int i = 0; i < n; i++) {
            bstRoot = insertBST(bstRoot, keys[i]);
        }
        heightsBST[step] = getHeight(bstRoot);

        // Построение рандомизированного BST (без приоритета)
        Node* randRoot = nullptr;
        for (int i = 0; i < n; i++) {
            // ЗАМЕНА: insertRandomized теперь принимает только ключ
            randRoot = insertRandomized(randRoot, keys[i]);
        }
        heightsRandomized[step] = getHeight(randRoot);

        // Вывод результатов в виде таблицы
        printf("│ %6d │ %10d │ %23d │\n", n, heightsBST[step], heightsRandomized[step]);

        // Очистка памяти
        deleteTree(bstRoot);
        deleteRandomizedTree(randRoot);
    }

    cout << "└────────┴────────────┴─────────────────────────┘" << endl;
}

// Демонстрация работы (этап 2)
void demonstrateStage2() {

    const int TOTAL_KEYS = 300;
    int* randomKeys = new int[TOTAL_KEYS];
    int* sortedKeys = new int[TOTAL_KEYS];

    cout << "\nЭТАП 2" << endl;

    // 1. Генерация случайной последовательности из 300 уникальных ключей
    generateUniqueNumbersLarge(randomKeys, TOTAL_KEYS, 1, 1000);

    // 2. Копирование и сортировка
    for (int i = 0; i < TOTAL_KEYS; i++) {
        sortedKeys[i] = randomKeys[i];
    }

    // Сортировка по возрастанию
    sort(sortedKeys, sortedKeys + TOTAL_KEYS);

    // Вывод первых 10 элементов для проверки
    cout << "   Первые 10 случайных ключей: ";
    for (int i = 0; i < 10; i++) cout << randomKeys[i] << " ";
    cout << endl;

    cout << "   Первые 10 отсортированных ключей: ";
    for (int i = 0; i < 10; i++) cout << sortedKeys[i] << " ";
    cout << endl;

    // 3. Построение и измерение для случайных ключей
    cout << "\nАнализ для СЛУЧАЙНОЙ последовательности:\n";
    buildAndMeasure(randomKeys, TOTAL_KEYS, false, "СЛУЧАЙНЫЕ");

    // 4. Построение и измерение для отсортированных ключей
    cout << "\nАнализ для ОТСОРТИРОВАННОЙ последовательности:\n";
    buildAndMeasure(sortedKeys, TOTAL_KEYS, true, "ОТСОРТИРОВАННЫЕ");

    // Очистка памяти
    delete[] randomKeys;
    delete[] sortedKeys;
}

// ============ ОСНОВНАЯ ФУНКЦИЯ ============

int main() {

    srand(time(0));

    // Выполнение этапа 1
    demonstrateStage1();

    // Выполнение этапа 2
    demonstrateStage2();

    return 0;
}