#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <stdexcept>
#include <cassert> // для тестов assert
#include <ctime>   // для time()
#include <cstdlib> // для rand() и srand()
#include "array.h"

using namespace std; // Использование пространства имен std для упрощения записи


///Функция заполняющая массив рандомными числами size - размер массива, 
//minVal - минимальное значение, maxVal - максимальное значение
void random_array(vector<int>& v, int minVal, int maxVal) {
    if (v.empty()) {
        throw invalid_argument("Вектор пуст. Невозможно заполнить случайными числами.");
    }
    if (minVal > maxVal) {
        throw invalid_argument("Минимальное значение больше максимального.");
    }

    random_device rd; // Получаем начальное значение от операционной системы
    mt19937 gen(rd()); // Стандартный генератор Mersenne Twister, инициализированный rd()
    uniform_int_distribution<> distrib(minVal, maxVal); // Определяем диапазон

    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = distrib(gen); // Заполняем вектор случайными числами
    }
}

/// функция увеличения массива случайными числами, но монотонно увеличивающими
///size - размер массива, 
///minVal - минимальное значение, maxVal - максимальное значение
vector<int> increasing_array(size_t size, int minVal, int maxVal) {
    vector<int> array;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    if (size <= 0) {
        throw invalid_argument("Array size must be positive.");
    }

    int prev = minVal;
    for (size_t i = 0; i < size; ++i) {
        int next = distrib(gen);
        while (next <= prev) {
            next = distrib(gen); // generate until a larger number is obtained
        }
        array.push_back(next);
        prev = next;
    }
    return array;
}

// Функция записи массива в файл, array - массив, filename - название файла
bool write_array_tofile(const vector<int>& array, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    for (int x : array) {
        file << x << " ";
    }
    file.close();
    return true;
}


// Функция, которая в последнее время, отсортирована по массиву, array - массив
void sortArray(vector<int>& array) {
    sort(array.begin(), array.end());
}


// // Тесты
// void testSorting() {
//     vector<int> array1 = {5, 2, 8, 1, 9, 4};
//     vector<int> array1_sorted = {1, 2, 4, 5, 8, 9};
//     sortArray(array1);
//     assert(array1 == array1_sorted); // Check for equality


//     vector<int> array2 = {10, 20, 30, 40, 50};
//     vector<int> array2_sorted = {10, 20, 30, 40, 50};
//     sortArray(array2);
//     assert(array2 == array2_sorted);


//     vector<int> array3 = {}; //пустой массив
//     sortArray(array3);
//     assert(array3.empty());

//     vector<int> array4 = {1}; //массив с одним элементом
//     sortArray(array4);
//     assert(array4.size() ==1);
//     assert(array4[0] == 1);

//     cout << "Тесты пройдены" << endl;
// }
