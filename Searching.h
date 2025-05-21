#pragma once
/*Автор: Саргсян Татев ИВТ-23*/

#include <functional> // Для std::function

/* SEARCHING */

// Шаблонная функция для последовательного поиска в массиве
// BigO (время)
// Лучший случай:  O(1)
// Средний случай: O(n)
// Худший случай:  O(n)
// BigO (память) : O(1)
template <typename T>
long long sequential_search1(const T* arr, size_t size, const T& num) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return i;  //возвращаем индекс найденного элемента
        }
    }
    return -1;
}

// Функция для последовательного поиска с поддержкой произвольной функции сравнения
// arr - массив, size - размер, target - искомое значение, comp - функция сравнения  
// (function, представляющий собой произвольную функцию, принимающую две константные 
// ссылки на объекты типа T и возвращающую bool (истина или ложь). Эта функция определяет, 
// как сравнивать элементы массива с искомым значением)
// позволяет использовать не только простое равенство (==), например:
//Сравнение строк без учета регистра.
//Сравнение объектов по какому - то конкретному атрибуту.
//Сравнение чисел с учетом погрешности.
template <typename T>
long long sequential_search(const T* arr, size_t size, const T& target, function<bool(const T&, const T&)> comp) {
    for (size_t i = 0; i < size; ++i) {
        if (comp(arr[i], target)) {
            return i;  // Возвращаем индекс найденного элемента
        }
    }
    return -1;
}

// Функция для бинарного поиска (массив должен быть отсортирован)
// BigO (время)
// Лучший случай:  O(1)
// Средний случай: O(log n)
// Худший случай:  O(log n)
// BigO (память) : O(1)
template<typename T>
long long binary_search(const T* arr, size_t size, const T& target) {
    if (size == 0) return -1; // Важно: проверка на пустой массив!
    size_t left = 0, right = size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Функция для интерполяционного поиска (для равномерно распределенных данных)
// BigO 
// Лучший случай:   O(1)
// Средний случай:  O(log log n)
// Худший случай:   O(n)
// BigO (память) :  O(1)
template <typename T>
long long interpolation_search(const T* arr, size_t size, const T& target) {
    size_t left = 0, right = size - 1;
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            if (arr[left] == target) return left;
            return -1;
        }
        if (arr[right] == arr[left]) return -1;

        size_t pos = left + ((target - arr[left]) * (right - left) / (arr[right] - arr[left])); //формула вычисления индекса средней точки
        if (pos >= size) return -1;

        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return -1;
}
