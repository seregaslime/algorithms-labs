/*--------------------------------------------------------------*
* Project Type : MacOS                                          *
* Project Name : Alg_Lab2                                       *
* File Name    : lab2.cpp                                       *
* Language     : C/C++                                          *
* Programmer(s): Ильин С. А., Петровский Д. Е.                  *
* Modified By  :                                                *
* Lit source   :                                                *
* Created      : 26/11/25                                       *
* Last Revision: 27/11/25                                       *
* Comment(s)   :                                                *
****************************************************************/
#include <iostream>
#include <chrono>  // Библиотека для вычисления времени выполнения алгоритма
#include <algorithm>
using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Selection_Sort(int arr[], int n, int& counter1, int& counter2)
{
    int temp = 0;
    int smallest = 0;

    // вывод для массива из 15 элементов
    //   for (int i = 0; i < n; i++)
    //   {
    //     cout << arr[i] << " ";
    //   }
    //   cout << endl;
    // вывод для массива из 15 элементов

    for (int i = 0; i < n - 1; i++)
    {
        smallest = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[smallest])
            {
                smallest = j;
                counter1++;
            }
        }

        swap(arr[i], arr[smallest]);

        // вывод для массива из 15 элементов
        // for (int i = 0; i < n; i++)
        // {
        //   cout << arr[i] << " ";
        // }
        // cout << endl;
        // вывод для массива из 15 элементов

        counter2++;
    }
}

int partition(int arr[], int low, int high, int& counter1, int& counter2)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        counter1++;

        if (arr[j] <= pivot)
        {
            
            
            i++;
            swap(arr[i], arr[j]);
            if (i != j)
            {
                counter2++;
            }
            // вывод для массива из 15 элементов
            // for (int i = 0; i < 15; i++)
            // {
            //     cout << arr[i] << " ";
            // }
            // cout << endl;
            // вывод для массива из 15 элементов
        }

    }
    swap(arr[i + 1], arr[high]);
    if (i+1 != high)
    {
        counter2++;
    }
    

    // вывод для массива из 15 элементов
    // for (int i = 0; i < 15; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    // вывод для массива из 15 элементов

    return i + 1;
}

void Quick_Sort(int arr[], int low, int high, int& counter1, int& counter2)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, counter1, counter2);
        Quick_Sort(arr, low, pi - 1, counter1, counter2);
        Quick_Sort(arr, pi + 1, high, counter1, counter2);
    }
}


int main()
{
    setlocale(LC_ALL, "");

    // const int size = 15;
    //   const int size = 500;
    //   const int size = 1000;
    //   const int size = 10000;
    //   const int size = 50000;
      const int size = 100000;

    int* vec = new int[size];

    for (int i = 0; i < size; i++)
    {
        vec[i] = rand() % 10000;
    }
    // для неотсортированного массива
    int counter1 = 0;
    int counter2 = 0;

    cout << " Результаты выполнения алгоритма сортировки (НЕотсортированного массива):" << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); // Время начала выполнения алгоритма

    // Selection_Sort(vec, size, counter1, counter2);
    Quick_Sort(vec, 0, size-1, counter1, counter2);

    chrono::steady_clock::time_point end = chrono::steady_clock::now(); // Время конца выполнения алгоритма

    chrono::nanoseconds elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin); // Подсчет времени выполнения алгоритма 

    cout << "Время работы алгоритма по формированию последовательности: " << elapsed_ms.count() << " (нС)" << endl;
    cout << "counter1 = " << counter1 << ", counter2 = " << counter2 << endl << endl;


    // сортируем массив по возрастанию
    sort(vec, vec + size);

    // для массива отсортированного по возрастанию
    counter1 = 0;
    counter2 = 0;

    cout << " Результаты выполнения алгоритма сортировки (отсортированного по возрастанию):" << endl;

    begin = chrono::steady_clock::now(); // Время начала выполнения алгоритма

    // Selection_Sort(vec, size, counter1, counter2);
    Quick_Sort(vec, 0, size - 1, counter1, counter2);

    end = chrono::steady_clock::now(); // Время конца выполнения алгоритма

    elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin); // Подсчет времени выполнения алгоритма
        cout << "Время работы алгоритма по формированию последовательности: " << elapsed_ms.count() << " (нС)" << endl;
    cout << "counter1 = " << counter1 << ", counter2 = " << counter2 << endl << endl;

   
    // сортируем массив по убыванию
    sort(vec, vec + size, greater<int>());

    // для массива отсортированного по убыванию
    counter1 = 0;
    counter2 = 0;

    cout << " Результаты выполнения алгоритма сортировки (отсортированного по убыванию):" << endl;

    begin = chrono::steady_clock::now(); // Время начала выполнения алгоритма

    // Selection_Sort(vec, size, counter1, counter2);
    Quick_Sort(vec, 0, size - 1, counter1, counter2);

    end = chrono::steady_clock::now(); // Время конца выполнения алгоритма

    elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin); // Подсчет времени выполнения алгоритма 

    cout << "Время работы алгоритма по формированию последовательности: " << elapsed_ms.count() << " (нС)" << endl;
    cout << "counter1 = " << counter1 << ", counter2 = " << counter2 << endl << endl;

}