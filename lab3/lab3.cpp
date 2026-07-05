#include <iostream>
using namespace std;

struct List
{
    List* next;
    int data;
};

void ShowMenu()
{
    cout << "Выберите действия:" << endl;
    cout << "1. Создать список(с конца)" << endl;
    cout << "2. Вывести элементы списка" << endl;
    cout << "3. Удалить список" << endl;
    cout << "4. Вывод макс.элемента списка с его номером" << endl;
    cout << "5. Добавить элемент в конец списка" << endl;
    cout << "6. Удаление заданного элемента по индексу" << endl;
    cout << "0. Выход из программы" << endl;
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "");

    List* p = NULL;
    List* firstP = NULL;
    List* lastP = NULL;
    List* list = NULL;
    int data;
    int choice;
    bool flag = false;
    int maxData;
    int index = 0, indexMax = 0;
    
    // Переменные для удаления по индексу
    List* current = NULL;
    List* previous = NULL;
    int currentIndex = 0;
    int deleteIndex = 0;

    do
    {
        ShowMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (firstP == NULL)
            {
                cout << "Введите номера списка (для завершения введите 0):" << endl;
                while (true)
                {
                    cin >> data;

                    if (data == 0)
                    {
                        firstP = p;
                        break;
                    }

                    list = new List;

                    list->data = data;
                    list->next = p;
                    p = list;

                    if (lastP == NULL)
                    {
                        lastP = p;
                    }
                }
                while (p != NULL)
                {
                    list = p->next;
                    while (list != NULL)
                    {
                        if (p->data == list->data)
                        {
                            cout << "Найдено повторение! Число " << p->data << endl;
                            flag = true;
                            break;
                        }
                        list = list->next;
                    }
                    p = p->next;
                }
                if (flag == true)
                {
                    p = firstP;
                    while (p != NULL)
                    {
                        list = p;
                        p = list->next;
                        delete list;
                        list = nullptr;
                    }
                    firstP = NULL;
                }
            }
            else
            {
                cout << "Список уже создан!" << endl;
                system("cls");
                break;
            }
            break;
        }

        case 2:
        {
            if (firstP == NULL)
            {
                cout << "Список еще не создан!" << endl;
                system("cls");
                break;
            }

            cout << "Текущий список: ";

            list = firstP;
            while (list != NULL)
            {
                cout << list->data << " ";
                list = list->next;
            }
            cout << endl;
            break;
        }

        case 3:
        {
            if (firstP == NULL)
            {
                cout << "Список еще не создан!" << endl;
                system("cls");
                break;
            }

            cout << "Удаление списка!" << endl;

            p = firstP;
            while (p != NULL)
            {
                list = p;
                p = list->next;
                delete list;
                list = nullptr;
            }
            firstP = NULL;
            lastP = NULL;
            cout << "Список удален!" << endl;
            system("cls");
            break;
        }

        case 4:
        {
            if (firstP == NULL)
            {
                cout << "Список еще не создан!" << endl;
                system("cls");
                break;
            }

            list = firstP;
            maxData = list->data;
            index = 0;
            indexMax = 0;

            while (list != NULL)
            {
                if (maxData < list->data)
                {
                    indexMax = index;
                    maxData = list->data;
                }
                index++;
                list = list->next;
            }
            cout << "Макс.элемент в списке: " << maxData << " с индексом " << indexMax << endl;
            break;
        }

        case 5:
        {
            if (firstP == NULL)
            {
                cout << "Список еще не создан!" << endl;
                system("cls");
                break;
            }

            cout << "Введите новый элемент: ";
            cin >> data;

            // Проверка на повторение
            list = firstP;
            bool duplicate = false;
            while (list != NULL)
            {
                if (list->data == data)
                {
                    cout << "Ошибка: число " << data << " уже есть в списке!" << endl;
                    duplicate = true;
                    break;
                }
                list = list->next;
            }

            if (duplicate)
            {
                break; // Не добавляем дубликат
            }

            list = new List;

            lastP->next = list;
            list->data = data;
            list->next = NULL;

            lastP = list;
            cout << "Элемент " << data << " добавлен в конец списка!" << endl;
            break;
        }

        case 6:
        {
            if (firstP == NULL)
            {
                cout << "Список еще не создан!" << endl;
                system("cls");
                break;
            }

            cout << "Введите индекс элемента для удаления (начиная с 0): ";
            cin >> deleteIndex;

            // Проверка на пустой список
            if (firstP == NULL)
            {
                cout << "Список пуст!" << endl;
                break;
            }

            // Удаление первого элемента
            if (deleteIndex == 0)
            {
                List* temp = firstP;
                firstP = firstP->next;
                // Если список стал пустым, обнуляем lastP
                if (firstP == NULL)
                {
                    lastP = NULL;
                }
                delete temp;
                cout << "Элемент с индексом 0 удален!" << endl;
                break;
            }

            // Сбрасываем переменные перед использованием
            current = firstP;
            previous = NULL;
            currentIndex = 0;

            while (current != NULL && currentIndex < deleteIndex)
            {
                previous = current;
                current = current->next;
                currentIndex++;
            }

            // Проверка, найден ли элемент
            if (current == NULL)
            {
                cout << "Элемент с индексом " << deleteIndex << " не найден!" << endl;
                break;
            }

            // Удаление элемента
            previous->next = current->next;
            
            // Если удаляем последний элемент, обновляем lastP
            if (current == lastP)
            {
                lastP = previous;
            }
            
            delete current;
            cout << "Элемент с индексом " << deleteIndex << " удален!" << endl;
            break;
        }

        case 0:
            // Очистка памяти перед выходом
            if (firstP != NULL)
            {
                List* current = firstP;
                while (current != NULL)
                {
                    List* next = current->next;
                    delete current;
                    current = next;
                }
            }
            return 0;

        default:
            cout << "Неверный выбор!" << endl;
            system("cls");
        }

    } while (choice != 0);
    return 0;
}