/*Автор: Саргсян Татев ИВТ-23*/

/*Ссылка на задание*/  

#include <iostream> //библиотека для стандартных ввода-вывода 
#include <vector> // Заголовочный файл для работы с вектором
#include <fstream> //библиотека для работы с файлами
#include <random> //библиотека для работы со случайными значениями
#include <stdexcept> // Заголовочный файл, используемый для сообщений об исключениях
#include <algorithm>
#include <cassert> // для тестов assert
#include <ctime>   // для time()
#include <cstdlib> // для rand() и srand()
#include "array.h"
#include <chrono>
//строка включает все имена, объявленные в пространстве имен "std"
using namespace std; 
using namespace chrono;


// Функция для тестирования поиска
void test_sequential_search() {
   int testArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(sequential_search(testArray, 10, 5) == 4);
    assert(sequential_search(testArray, 10, 10) == 9);
    assert(sequential_search(testArray, 10, 1) == 0);
    //assert(sequential_search(testArray, 10, 11) == -1);
    cout << "Все тесты прошли успешно!" << endl;
}

void test_random_array() {
    int arr[5];
    random_array(arr, 5, 1, 10);
    for (int i = 0; i < 5; ++i) {
        assert(arr[i] >= 1 && arr[i] <= 10);
    }

    //проверка исключения для minVal > maxVal
    bool exceptionCaught = false;
    try {
        random_array(arr, 5, 10, 1);
    } catch (const invalid_argument& e) {
        //если возникнет исключение типа invalid_argument, перехватываем его
        exceptionCaught = true;
    }
    

    // //Проверка исключения для nullptr
    // exceptionCaught = false;
    // try {
    //     random_array(nullptr, 5, 1, 10);
    // } catch (const invalid_argument& e) {
    //     exceptionCaught = true;
    // }
    // assert(exceptionCaught);

    // Проверка на выброс исключения, когда размер массива (size) меньше или равен нулю
    exceptionCaught = false;  // Инициализация переменной, которая будет отслеживать, поймано ли исключение
    try {
        random_array(arr, 0, 1, 10);  // Вызов функции random_array с size = 0, что должно вызвать исключение
    } catch (const invalid_argument& e) {  // Поймать исключение типа invalid_argument
        exceptionCaught = true;  // Если исключение поймано, устанавливаем флаг в true
    }
    // Проверка, что исключение было действительно поймано
    assert(exceptionCaught);  // Если исключение не было поймано, программа завершится с ошибкой
    cout << "test_random_array прошел" << endl;  // Если исключение поймано, выводим сообщение о прохождении теста

}

void test_increasing_array() {
    int* arr = increasing_array(5, 1, 100);
    assert(isSorted(arr, 5));
    for (int i = 0; i < 5; ++i) {
        assert(arr[i] >= 1 && arr[i] <= 100);
    }
    delete[] arr;

    //Проверка исключения для minVal > maxVal
    bool exceptionCaught = false;
    try {
        increasing_array(5, 100, 1);
    } catch (const invalid_argument& e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    //Проверка исключения для size <= 0
    exceptionCaught = false;
    try {
        increasing_array(0, 1, 100);
    } catch (const invalid_argument& e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    //Проверка на нехватку памяти (не гарантировано, но проверяет)
    exceptionCaught = false;
    try {
        increasing_array(1000000000, 1,100); // Попытка выделить очень много памяти
    } catch (const exception& e) {
      exceptionCaught = true;
    }
    // assert(exceptionCaught); // Комментируем, т.к. может зависеть от системы

    cout << "test_increasing_array прошел" << endl;
}


void test_write_array_tofile() {
    int arr[] = {1, 2, 3, 4, 5};
    bool success = write_array_tofile(arr, 5, "test.txt");
    assert(success);
    //Проверка на существование файла (не очень надежный тест, но базовый)
    ifstream f("test.txt");
    assert(f.good());
    f.close();
    //удаление файла после проверки
    remove("test.txt");

    cout << "test_write_array_tofile прошел" << endl;
}

void test_isSorted() {
  int arr1[] = {1, 2, 3, 4, 5};
  assert(isSorted(arr1, 5));

  int arr2[] = {1, 3, 2, 4, 5};
  assert(!isSorted(arr2, 5));

  int arr3[] = {5};
  assert(isSorted(arr3, 1));

  int* arr4 = nullptr;
  assert(isSorted(arr4, 0));

  cout << "test_isSorted прошел гуд" << endl;
}

int main() {

    test_random_array();
    test_increasing_array();
    test_write_array_tofile();
    test_isSorted();
    test_sequential_search();
    cout << "Все  тесты пройдены"<< endl;

    char choice;
    cout << "Хотите протестировать на больших массивах? (y/n): ";
    cin >> choice;
    
    int n; // размер массива
    int min, max; // диапазон значений
    int s; //искомое значение
    const int iterations = 10; // Количество итераций для надежности замера

    if (choice == 'y' || choice == 'Y') {
        const int num_tests = 10;  // Количество повторений теста для получения стабильных результатов
        const long long n = 1'000'000'000;
        const int min_v = 0;
        const int max_v = 1'000'000;  // Диапазон значений для генерации
        
    } else {
        cout << "Введите размер массива: ";
        cin >> n;
        cout << "Введите диапазон значений (min max): ";
        cin >> min >> max;
    }

    cout << "Введите искомое значение в массиве: ";
    cin >> s;

    int* myArray = new int[n]; // создание массива по размеру

    random_array(myArray, n, min, max);
    cout << "Случайный массив: ";
    // for (int i = 0; i < n; ++i) {
    //     cout << myArray[i] << " ";
    // }

    duration<double> total_time(0);
        
    for (int i = 0; i < iterations; ++i) {
        auto start = high_resolution_clock::now();
        sequential_search(myArray, n, s);
        auto end = high_resolution_clock::now();
        total_time += duration<double>(end - start);
    }
    
    cout << "Размер массива: " << n << " Время выполнения: " 
              << total_time.count() / iterations << " секунд" << endl;



    write_array_tofile(myArray, n, "array.txt");
    cout << endl;

    cout << "Монотонновозрастающий массив: ";
    int* monotonicArray = increasing_array(n, min, max);
    // for (int i = 0; i < n; ++i) {
    //     cout << monotonicArray[i] << " ";
    // }
    cout << endl;
    //write_array_tofile(monotonicArray, n1, "array.txt");
    delete[] monotonicArray; //Освобождаем память


    if (isSorted(myArray,n)) {
        cout << "Массив отсортированный";
    }
    else {cout << "Массив не отсортирован";}
    


    delete[] myArray; //Освобождаем память


}
