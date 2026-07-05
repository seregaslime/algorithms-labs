/*--------------------------------------------------------------*
* Project Type : MacOS                                          *
* Project Name : Alg_Lab1                                       *
* File Name    : lab1.cpp                                       *
* Language     : C/C++                                          *
* Programmer(s): Ильин С. А., Петровский Д. Е.                  *
* Modified By  :                                                *
* Lit source   :                                                *
* Created      : 13/11/25                                       *
* Last Revision: 14/11/25                                       *
* Comment(s)   :                                                *
****************************************************************/
#include <iostream>
#include <chrono>       // Библиотека для вычисления времени выполнения алгоритма
#include <algorithm>

using namespace std;

// Алгоритм Better_Linear_Search
int Better_Linear_Search(int A[], int n, int x, int& counter1, int& counter2)
{
    counter1 = 0;       // Счетчик кол-ва сравниваний элемента массива с ключем
    counter2 = 0;       // Счетчик кол-ва сравниваний индекса с длинной массива

    for (int i = 0; i < n; i++)
    {
        counter1++;             // Прибавляем счетчик
        counter2++;             // Прибавляем счетчик

        if (A[i] == x)          // Сравниваем элемент массива с ключом
        {
            return i;           // Возвращаем индекс элемента
        }
    }
    return -1;                  // Возвращаем -1 если ничего не нашли
}

// Алгоритм Sentinel_Linear_Search
int Sentinel_Linear_Search(int A[], int n, int x, int& counter1, int& counter2)
{
    counter1 = 0;       // Счетчик кол-ва сравниваний элемента массива с ключем
    counter2 = 0;       // Счетчик кол-ва сравниваний индекса с длинной массива
    int last = A[n - 1]; // Запоминаем последний элемент массива
    A[n - 1] = x;       // Устанавливаем флаг на последний элемент массива
    int i = 0;          // Индекс элемента массива

    while (A[i] != x)
    {
        counter1++;             // Прибавляем счетчик
        i++;
    }

    A[n - 1] = last;    // Возвращаем элемент на место
    counter1++;         // Прибавляем счетчик
    counter2++;         // Прибавляем счетчик

    // Сравниваем элемент массива с ключем
    if (i < (n - 1) or A[n - 1] == x) 
    {
        return i;               // Возвращаем индекс элемента
    }
    return -1;                  // Возвращаем -1 если ничего не нашли
}

// Алгоритм Ordered_Array_Search
int Ordered_Array_Search(int A[], int n, int x, int& counter1, int& counter2)
{
    counter1 = 0;       // Счетчик кол-ва сравниваний элемента массива с ключем
    counter2 = 0;       // Счетчик кол-ва сравниваний индекса с длинной массива
    int i = 0;          // Индекс элемента массива


    while (A[i] < x and i<n)
    {
        counter1++;     // Прибавляем счктчик
        counter2++;
        i++;
    }

    counter1++;         // Прибавляем счктчик
    counter2++;
    if (A[i] == x)
    {
        return i;       // Возвращаем индекс элемента
    }
    return -1;          // Возвращаем -1 если ничего не нашли
}

// Алгоритм Binary_Search
int Binary_Search(int A[], int n, int x, int& counter1, int& counter2)
{
    counter1 = 0;       // Счетчик кол-ва сравниваний элемента массива с ключем
    counter2 = 0;       // Счетчик кол-ва сравниваний индекса с длинной массива

    int left = 0;       // Левая граница
    int right = n - 1;  // Правая граница

    while (left <= right)
    {
        int mid = left + (right - left) / 2;    // Находим середину
        counter1++;                             // Прибавляем счетчик

        if (A[mid] == x)            // Проверяем ключ с серединой
        {
            return mid;             // Возвращаем индекс элемента
        }
        else if (A[mid] < x)
        {
            counter1++;             // Прибавляем счетчик
            left = mid + 1;         // Ищем в правой половине
        }
        else
        {
            counter1++;             // Прибавляем счетчик
            right = mid - 1;        // Ищем в левой половине
        }
    }
    return -1;          // Возвращаем -1 если ничего не нашли
}

void Print_Info(int result, int counter1, int counter2, chrono::microseconds elapsed_ms)
{
    if (result != -1)   // Если ключ есть
    {
        cout << "Индекс ключа - " << result << endl;
        cout << "Кол-во сравнений ключа с элементом массива - " << counter1 << endl;
        cout << "Кол-во сравнений индекса с длинной массива - " << counter2 << endl;
    }
    else                // Если ключа нет
    {
        cout << "Индекс ключа - " << "NotFound" << endl;
        cout << "Кол-во сравнений ключа с элементом массива - " << counter1 << endl;
        cout << "Кол-во сравнений индекса с длинной массива - " << counter2 << endl;
    }
    cout << "Время работы алгоритма: " << elapsed_ms.count() << " (мкС)\n" << endl;
}

void Print_Info2(int result, int counter1, int counter2, chrono::nanoseconds elapsed_ms)
{
    if (result != -1)   // Если ключ есть
    {
        cout << "Индекс ключа - " << result << endl;
        cout << "Кол-во сравнений ключа с элементом массива - " << counter1 << endl;
        cout << "Кол-во сравнений индекса с длинной массива - " << counter2 << endl;
    }
    else                // Если ключа нет
    {
        cout << "Индекс ключа - " << "NotFound" << endl;
        cout << "Кол-во сравнений ключа с элементом массива - " << counter1 << endl;
        cout << "Кол-во сравнений индекса с длинной массива - " << counter2 << endl;
    }
    cout << "Время работы алгоритма: " << elapsed_ms.count() << " (наноС)\n" << endl;
}


// Основная программа
int main()
{
    setlocale(LC_ALL, "");

    /***********************************************
    *           Д Л И Н Ы  М А С С И В А           * 
    ***********************************************/
    const int size = 300000;
    // const int size = 100000;
    // const int size = 150000;
    // const int size = 200000;
    // const int size = 250000;
    // const int size = 300000;
    int* vec = new int[size]; // Массив

    // Ключ
    int key = 10001;

    // Заполняем массив случайными числами
    for (int i = 0; i < size; i++)
    {
        vec[i] = rand() % 10000;
    }

     // Заполняем массив случайными числами
    // for (int i = 0; i < size; i++)
    // {
    //     cout<<vec[i]<<" " ;
    // }
    /****************************************************
    *           К Л Ю Ч И (НАЧАЛО, СЕРЕДИНА)            *
    ****************************************************/
    /*  50000   */
    // vec[74999] = key;
    // vec[49999] = key;

    /*  100000  */
    // vec[0] = key;
    // vec[49999] = key;

    /*  150000  */
    // vec[0] = key;
    // vec[74999] = key;
 
    /*  200000  */
    // vec[0] = key;
    // vec[99999] = key;

    /*  250000  */
    // vec[0] = key;
    // vec[124999] = key;

    /*  300000  */
    // vec[0] = key;
    // vec[149999] = key;

    /**************************************************/

    // Счетчики для кол-ва сравниваний 
    int counter1 = 0;       // Счетчик кол-ва сравниваний элемента массива с ключем
    int counter2 = 0;       // Счетчик кол-ва сравниваний индекса с длинной массива

    // Конечный результат
    int result = 0;





    // Вызов алгоритма Better_Linear_Search
    cout << " Результаты выполнения алгоритма BLS:" << endl;
    chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();      // Время начала выполнения алгоритма
    result = Better_Linear_Search(vec, size, key, counter1, counter2);          // Вызов функции
    chrono::steady_clock::time_point end1 = chrono::steady_clock::now();        // Время конца выполнения алгоритма
    chrono::microseconds elapsed_ms1 = chrono::duration_cast<chrono::microseconds>(end1 - begin1); // Подсчет времени выполнения алгоритма 
    Print_Info2(result, counter1, counter2, elapsed_ms1);

    // Вызов алгоритма Sentinel_Linear_Search
    cout << " Результаты выполнения алгоритма SLS:" << endl;
    chrono::steady_clock::time_point begin2 = chrono::steady_clock::now();      // Время начала выполнения алгоритма
    result = Sentinel_Linear_Search(vec, size, key, counter1, counter2);        // Вызов функции
    chrono::steady_clock::time_point end2 = chrono::steady_clock::now();        // Время конца выполнения алгоритма
    chrono::microseconds elapsed_ms2 = chrono::duration_cast<chrono::microseconds>(end2 - begin2); // Подсчет времени выполнения алгоритма 
    Print_Info2(result, counter1, counter2, elapsed_ms2);


    sort(vec, vec + size);          // Сортируем массив по возрастанию для вызова Ordered_Array_Search и Binary_Search

    // key = vec[size/2-1];


    // Вызов алгоритма Ordered_Array_Search
    cout << " Результаты выполнения алгоритма OAS:" << endl;
    chrono::steady_clock::time_point begin3 = chrono::steady_clock::now();      // Время начала выполнения алгоритма
    result = Ordered_Array_Search(vec, size, key, counter1, counter2);          // Вызов функции
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();        // Время конца выполнения алгоритма
    chrono::microseconds elapsed_ms3 = chrono::duration_cast<chrono::microseconds>(end3 - begin3); // Подсчет времени выполнения алгоритма 
    Print_Info2(result, counter1, counter2, elapsed_ms3);

    // Вызов алгоритма Binary_Search
    cout << " Результаты выполнения алгоритма BS:" << endl;
    chrono::steady_clock::time_point begin4 = chrono::steady_clock::now();      // Время начала выполнения алгоритма
    result = Binary_Search(vec, size, key, counter1, counter2);                 // Вызов функции
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();        // Время конца выполнения алгоритма
    chrono::nanoseconds elapsed_ms4 = chrono::duration_cast<chrono::nanoseconds>(end4 - begin4); // Подсчет времени выполнения алгоритма 
    Print_Info2(result, counter1, counter2, elapsed_ms4);

    // Очищаем память
    delete[] vec;
    vec = nullptr;

    return 0;
}
