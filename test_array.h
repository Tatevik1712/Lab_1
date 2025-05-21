/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <iostream>
#include <cassert> // для тестов assert
#include "List.h"
#include <vector>


//строка включает все имена, объявленные в пространстве имен "std"
using namespace std;

/* TESTS */

// Тестирование последовательного поиска 
void test_sequential_search() {
    vector<int> arr = { 1, 3, 5, 7, 9, 34, 6, 2 };
    vector<int> arr1 = { 7 };
    function<bool(const int&, const int&)> comp = [](const int& a, const int& b) { return a == b; };
    assert(sequential_search(arr.data(), arr.size(), 1, comp) == 0); //первый
    assert(sequential_search(arr.data(), arr.size(), 2, comp) == 7); //последний
    assert(sequential_search(arr.data(), arr.size(), 5, comp) == 2); //средний
    assert(sequential_search(arr.data(), arr.size(), 7, comp) == 3); //случаный
    assert(sequential_search(arr.data(), arr.size(), 55, comp) == -1); //отсутствует
    assert(sequential_search(arr1.data(), arr1.size(), 7, comp) == 0); //из 1 эл-та в массиве
    cout << "Тест последовательного поиска пройден" << endl;
}

// Тестирование бинарного поиска
void test_binary_search() {
    vector<int> arr = { 1, 3, 5, 7, 9, 5, 22, 89 };
    vector<int> arr1 = { 9 };

    assert(binary_search(arr.data(), arr.size(), 1) == 0); //первый
    assert(binary_search(arr.data(), arr.size(), 89) == 7); //последний
    assert(binary_search(arr.data(), arr.size(), 7) == 3); //средний
    assert(binary_search(arr.data(), arr.size(), 5) == 2); //случаный
    assert(binary_search(arr.data(), arr.size(), 78) == -1); //отсутствует
    assert(binary_search(arr1.data(), arr1.size(), 9) == 0); //из 1 эл-та в массиве
    cout << "Тест бинарного поиска пройден" << endl;
}

// Тестирование интерполяционного поиска
void test_interpolation_search() {
    vector<int> arr = { 1, 3, 5, 7, 9, 5, 22, 89 };
    vector<int> arr1 = { 4 };
    assert(interpolation_search(arr.data(), arr.size(), 1) == 0); //первый
    assert(interpolation_search(arr.data(), arr.size(), 89) == 7); //последний
    assert(interpolation_search(arr.data(), arr.size(), 7) == 3); //средний
    assert(interpolation_search(arr.data(), arr.size(), 5) == 2); //случаный
    assert(interpolation_search(arr.data(), arr.size(), 78) == -1); //отсутствует
    assert(interpolation_search(arr1.data(), arr1.size(), 4) == 0); //из 1 эл-та в массиве
    cout << "Тест интерполяционного поиска пройден" << endl;
}

// Функция для тестирования поиска с компаратором
void test_sequential_search1() {

    int testArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int testArray1[1] = { 6 };

    function<bool(const int&, const int&)> comp = [](const int& a, const int& b) { return a == b; };

    assert(sequential_search(testArray, 10, 5, comp) == 4);  //средний
    assert(sequential_search(testArray, 10, 10, comp) == 9);  //последний
    assert(sequential_search(testArray, 10, 1, comp) == 0);  //первый
    assert(sequential_search(testArray, 10, 42, comp) == -1); //отсутствует
    assert(sequential_search(testArray1, 10, 6, comp) == 0); //из 1 эл-та

    cout << "Тест интерполяционного поиска1 пройден" << endl;;
}


void test_random_array() {
    int arr[5];
    random_array(arr, 5, 1, 10);
    for (int i = 0; i < 5; ++i) {
        assert(arr[i] >= 1 && arr[i] <= 10);
    }

    // Проверка исключения для minVal > maxVal
    bool exceptionCaught = false;
    try {
        random_array(arr, 5, 10, 1);
    }
    catch (const invalid_argument& e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    // Проверка, когда размер массива меньше или равен нулю
    exceptionCaught = false;
    try {
        random_array(arr, 0, 1, 10);
    }
    catch (const invalid_argument& e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    cout << "test_random_array прошел" << endl;
}

//Тетсирование проверки на сортировку 
void test_isSorted() {
    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    assert(isSorted(arr1, 5));
    int arr2[] = { 1, 3 };          //пары элементов
    assert(isSorted(arr2, 2));
    int arr3[] = { 5 };             //1 эл-т
    assert(isSorted(arr3, 1));
    int* arr4 = nullptr;            // пустой
    assert(isSorted(arr4, 0));
    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    assert(isSorted(arr5, 5));
    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    assert(isSorted(arr6, 5));
    cout << "test_isSorted прошел" << endl;
}

// Тестирование сортировки пузырьком
void test_bubble_sort() {
    int arr[] = { 5, 3, 8, 4, 2 };    //простой
    BubbleSort(arr, 5);
    assert(isSorted(arr, 5));

    int single[] = { 1 };             // 1 эл-т
    BubbleSort(single, 1);
    assert(isSorted(single, 1));

    int* arr4 = nullptr;            // пустой
    BubbleSort(arr4, 0);
    assert(isSorted(arr4, 0));

    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    BubbleSort(arr1, 5);
    assert(isSorted(arr1, 5));

    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    BubbleSort(arr5, 5);
    assert(isSorted(arr5, 5));

    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    BubbleSort(arr6, 5);
    assert(isSorted(arr6, 5));
    cout << "test_bubble_sort пройден " << endl;
}

// Тестирование сортировки выбором
void test_selection_sort() {
    int arr[] = { 5, 3, 8, 4, 2 };    //простой
    SelectionSort(arr, 5);
    assert(isSorted(arr, 5));

    int single[] = { 1 };             // 1 эл-т
    SelectionSort(single, 1);
    assert(isSorted(single, 1));

    int* arr4 = nullptr;            // пустой
    SelectionSort(arr4, 0);
    assert(isSorted(arr4, 0));

    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    SelectionSort(arr1, 5);
    assert(isSorted(arr1, 5));

    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    SelectionSort(arr5, 5);
    assert(isSorted(arr5, 5));

    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    SelectionSort(arr6, 5);
    assert(isSorted(arr6, 5));
    cout << "test_selection_sort пройден " << endl;
}

// Тестирование сортировки вставками
void test_insertion_sort() {
    int arr[] = { 5, 3, 8, 4, 2 };    //простой
    InsertionSort(arr, 5);
    assert(isSorted(arr, 5));

    int single[] = { 1 };             // 1 эл-т
    InsertionSort(single, 1);
    assert(isSorted(single, 1));

    int* arr4 = nullptr;            // пустой
    InsertionSort(arr4, 0);
    assert(isSorted(arr4, 0));

    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    InsertionSort(arr1, 5);
    assert(isSorted(arr1, 5));

    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    InsertionSort(arr5, 5);
    assert(isSorted(arr5, 5));

    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    InsertionSort(arr6, 5);
    assert(isSorted(arr6, 5));
    cout << "test_insertion_sort пройден " << endl;
}

// Тестирование сортировки Шелла
void test_shell_sort() {
    int arr[] = { 5, 3, 8, 4, 2 };    //простой
    ShellSort(arr, 5);
    assert(isSorted(arr, 5));

    int single[] = { 1 };             // 1 эл-т
    ShellSort(single, 1);
    assert(isSorted(single, 1));

    int* arr4 = nullptr;            // пустой
    ShellSort(arr4, 0);
    assert(isSorted(arr4, 0));

    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    ShellSort(arr1, 5);
    assert(isSorted(arr1, 5));

    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    ShellSort(arr5, 5);
    assert(isSorted(arr5, 5));

    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    ShellSort(arr6, 5);
    assert(isSorted(arr6, 5));
    cout << "test_shell_sort пройден" << endl;
}

// Тестирование Быстрой сортировки
void test_quick_sort() {
    /*size_t size = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, size - 1);
    assert(is_sorted(arr, size));*/
    int arr[] = { 5, 3, 8, 4, 2 };    //простой (случайный)
    QuickSort(arr, 0, 4);
    assert(isSorted(arr, 5));

    int single[] = { 1 };             // 1 эл-т
    QuickSort(single, 0, 0);
    assert(isSorted(single, 1));

    int arr1[] = { 5, 3, 2, 5, 1, 2 }; //одинаковые эл-ты
    QuickSort(arr1,0, 4);
    assert(isSorted(arr1, 5));

    int arr5[] = { 5, 4, 3, 2, 1 }; //по убыванию
    QuickSort(arr5,0, 4);
    assert(isSorted(arr5, 5));

    int arr6[] = { 1, 2, 3, 4, 5 }; //по возрастанию (отсортированный)
    QuickSort(arr6, 0, 4);
    assert(isSorted(arr6, 5));
    cout << "test_quick_sort пройден" << endl;
}


void test_recursion() {
   
    assert(RecursionSum(0, 0) == 0);
    assert(RecursionSum(0, 2) == 2);
    assert(RecursionSum(5, 0) == 5);
    assert(RecursionSum(-3, 0) == -3);
    assert(RecursionSum(0, -6) == -6);
    assert(RecursionSum(10, 23) == 33);
    assert(RecursionSum(-8, -10) == -18);

    cout << "test_recursion пройден" << endl;
}


void test_analyze_numbers() {
    double arr1[] = { 1, 2, 3, 4, 5 };
    double avg1;
    size_t greater1, lesser1;
    analyze_numbers(arr1, 5, avg1, greater1, lesser1);
    assert(avg1 == 3);
    assert(greater1 == 2);
    assert(lesser1 == 2);

    double arr2[] = { 10, 10, 10, 10, 10 };
    double avg2;
    size_t greater2, lesser2;
    analyze_numbers(arr2, 5, avg2, greater2, lesser2);
    assert(avg2 == 10);
    assert(greater2 == 0);
    assert(lesser2 == 0);

    double arr3[] = { 1, 100 };
    double avg3;
    size_t greater3, lesser3;
    analyze_numbers(arr3, 2, avg3, greater3, lesser3);
    assert(avg3 == 50.5);
    assert(greater3 == 1);
    assert(lesser3 == 1);

    cout << "test_analyze_numbers пройден" << endl;
}

/* TEST PASCAL */

// Тест 0 строк
void testZeroRows() {
    auto result = buildPascalTriangle(0);
    assert(result.empty());
}

// Тест 1 строка
void testOneRow() {
    auto result = buildPascalTriangle(1);
    assert(result.size() == 1);
    assert(result[0].size() == 1);
    assert(result[0][0] == 1);
}

// Тест 5 строк
void testFiveRows() {
    vector<vector<long long>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1}
    };

    auto result = buildPascalTriangle(5);
    assert(result.size() == expected.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        assert(result[i].size() == expected[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j) {
            assert(result[i][j] == expected[i][j]);
        }
    }
}

// Тест симметричности строк
void testSymmetry() {
    auto result = buildPascalTriangle(10);
    for (const auto& row : result) {
        for (size_t i = 0; i < row.size(); ++i) {
            assert(row[i] == row[row.size() - 1 - i]);
        }
    }
}

// Тест значения: C(6,3) = 20
void testSpecificValue() {
    auto result = buildPascalTriangle(7);  // 7 строк, индекс 6
    assert(result[6][3] == 20);
}