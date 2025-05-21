/*Автор: Саргсян Татев ИВТ-23*/

#pragma once // Защита от многократного включения
#include <iostream>
#include <vector>
#include <chrono>
#include <functional> // Для function
#include <cassert> // для тестов assert

//строка включает все имена, объявленные в пространстве имен "std"
using namespace std;
using namespace chrono;


///Функция заполняющая массив рандомными числами size - размер массива, 
//minVal - минимальное значение, maxVal - максимальное значение
// Заполнение массива случайными числами
template <typename T>
void random_array(T* arr, size_t size, int minVal, int maxVal) {
    if (arr == nullptr || size <= 0) { // если массив пуст/размер 0
        throw invalid_argument("Массив пуст или имеет недопустимый размер.");
    }
    if (minVal > maxVal) { //если макс.значение больше мин.значения
        throw invalid_argument("Минимальное значение больше максимального."); //вывод ошибки
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> distrib(minVal, maxVal);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
}

// Функция создания массива заданного размера size, заполненного случайными значениями в порядке 
// возврастания в заданном интервале от min_val (по умолчанию 0) до max_val (по умолчанию 10)
template<typename T>
T* random_array_sorted(size_t size, T min, T max) {
    if (static_cast<size_t>(max - min + 1) < size) {
        throw invalid_argument("Недостаточный диапазон");
    }

    T* arr = new T[size];
    mt19937 gen(random_device{}());

    // Увеличиваем min каждый раз, чтобы следующий элемент был больше предыдущего
    T current_min = min;
    for (size_t i = 0; i < size; ++i) {
        uniform_int_distribution<T> dist(current_min, max - (size - i - 1));
        arr[i] = dist(gen);
        current_min = arr[i] + 1;
    }
    return arr;
}

/// функция увеличения массива случайными числами, но монотонно увеличивающими
// size - размер массива, 
// minVal - минимальное значение, maxVal - максимальное значение
template <typename T>
T* increasing_array(size_t size, T minVal, T maxVal) {
    if (size <= 0) {
        throw invalid_argument("Размер массива должен быть положительным.");
    }
    if (minVal > maxVal) {
        throw invalid_argument("Минимальное значение больше максимального.");
    }

    T* arr = new T[size]; //выделение памяти для массива
    if (arr == nullptr) {
        throw runtime_error("Не удалось выделить память.");
    }

    random_device rd;
    mt19937 gen(rd()); //стандартный генератор случайных чисел
    uniform_int_distribution<T> distrib(minVal, maxVal); //распределение для генерации целых чисел в заданном диапазоне

    arr[0] = minVal;//
    T prev = minVal;
    for (size_t i = 1; i < size; ++i) {
        T next = distrib(gen);
        while (next <= prev) {
            next = distrib(gen);
        }
        arr[i] = next;
        prev = next;
    }
    return arr;
}

// Функция записи массива в файл, array - массив, filename - название файла, size - размер массива
//true в случае успешной записи, false в случае ошибки.
template <typename T>
bool write_array_tofile(const T* array, size_t size, const string& filename) {
    if (array == nullptr || size <= 0) {
        return false; //обработка случая пустого или некорректного массива
    }
    ofstream file(filename);

    //запись элементов массива в файл
    for (size_t i = 0; i < size; ++i) {
        file << array[i]; //ввод элемента
        if (i < size - 1) {
            file << " "; //добавление пробела между элементами (кроме последнего)
        }
    }

    //проверка на ошибки записи
    if (file.fail()) {
        cerr << "Ошибка: Произошла ошибка во время записи в файл.\n";
        return false;
    }

    file.close(); //закрытие файла
    return true;
}


//Функция проверки сортировки массива array по возрастанию, size - размер
template <typename T>
bool isSorted(const T* arr, size_t size) {
    if (arr == nullptr || size <= 1) { //если массив пустой или кол-во элементов=1
        return true; // Пустой или одноэлементный массив считается отсортированным
    }
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) { //если второй эелемент больше первого
            return false; // Найдено нарушение порядка - массив не отсортирован
        }
    }
    return true; // массив отсортирован
}


/* РЕКУРСИЯ */

// Рекурсивная функция сложения двух чисел
// Возвращает: сумму чисел a и b.
template<typename T>
T RecursionSum(T a, T b) {
    // Если второе число равно 0, возвращаем первое (рекурсия завершена).
    if (b == 0) {
        return a;
    }

    // Если первое число равно 0, возвращаем второе (рекурсия завершена).
    if (a == 0) {
        return b;
    }

    // Если b положительное, уменьшаем его на 1 и увеличиваем a на 1.
    // Это имитирует сложение через рекурсивное прибавление.
    if (b > 0) {
        return RecursionSum(a + 1, b - 1);
    }
    else {
        // Если b отрицательное, увеличиваем его на 1 и уменьшаем a на 1.
        // Это также эквивалентно сложению при отрицательных значениях.
        return RecursionSum(a - 1, b + 1);
    }
}



/* АНАЛИЗ СЛОЖНОСТИ */

// Функция анализирует массив: считает среднее значение,
// а затем определяет количество элементов, больших и меньших этого среднего.
//n – кол-во элементов в массиве
//avg – переменная для хранения среднего значения массива
//greater_count – кол-во элементов, превышающих среднее значение
//lesser_count – кол-во элементов, меньших среднего

// Временная сложность:
// Лучший случай: O(n) – два прохода по массиву длины n (суммирование и сравнение).
// Худший случай: O(n) – все элементы проходят те же операции.
// Средний случай: O(n) – всегда линейная сложность по количеству элементов.

// Пространственная сложность:
// O(1) – используется фиксированное количество дополнительной памяти, не зависящей от размера массива.

template<typename T>
void analyze_numbers(T* arr, size_t n, double& avg, size_t& greater_count, size_t& lesser_count) {
    avg = 0;
    for (size_t i = 0; i < n; i++) {
        avg += arr[i];
    }
    avg /= n;

    greater_count = 0;
    lesser_count = 0;

    for (size_t i = 0; i < n; i++) {
        if (arr[i] > avg) greater_count++;
        else if (arr[i] < avg) lesser_count++;
    }
}

// Функция для записи результатов в файл
void write_results(const string& filename, double avg, size_t greater_count, size_t lesser_count) {
    ofstream output(filename);
    if (!output) {
        cerr << "Ошибка открытия файла" << endl;
        return;
    }

    output << "Среднее значение: " << avg << endl;
    if (greater_count > lesser_count) {
        output << "Больше элементов > среднего" << endl;
    }
    else if (greater_count < lesser_count) {
        output << "Больше элементов < среднего" << endl;
    }
    else {
        output << "Число больших и меньших элементов равно" << endl;
    }

    output.close();
}
    
/// Динамические алгоритмы
/// Функция для построения треугольника Паскаля
vector<vector<long long>> buildPascalTriangle(size_t n) {
    vector<vector<long long>> pascal(n); // Инициализируем вектор из n строк

    // Внешний цикл: проходим по всем строкам треугольника
    for (size_t i = 0; i < n; ++i) {
        pascal[i].resize(i + 1);          // Задаем размер i-й строки (i + 1 элементов)
        pascal[i][0] = pascal[i][i] = 1;   // Первые и последние элементы строки всегда равны 1

        // Внутренний цикл: заполняем внутренние элементы строки (между крайними единицами)
        for (size_t j = 1; j < i; ++j) {
            // Каждый элемент равен сумме двух элементов из предыдущей строки
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }
    return pascal;
}





    
