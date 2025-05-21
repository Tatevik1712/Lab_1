/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Array.h"

/*
 * Глубокое копирование создаёт полную копию объекта, включая данные,
 * размещённые в динамической памяти. Это важно при работе с указателями.
 * Поверхностное копирование копирует только адреса, из-за чего два объекта
 * могут обращаться к одной и той же памяти, что опасно.
 * Для корректной работы с динамической памятью нужно реализовать:
 * - конструктор копирования
 * - оператор присваивания копированием
 * - деструктор
 * - перемещающий конструктор и оператор присваивания
 */

using namespace std;

/// Шаблонный класс динамического массива
template<typename T>
class DynamicArray {
private:
    T* data;           // Указатель на данные массива
    size_t size_;      // Текущее количество элементов
    size_t capacity;   // Вместимость массива (размер выделенной памяти)

    ///функция для изменения размера массива
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity]; // Выделяем новую память
        copy(data, data + size_, new_data);
        delete[] data;                     // Освобождаем старую память
        data = new_data;
        capacity = new_capacity;
    }

public:
    // --- Правило пяти ---

    /// Конструктор по умолчанию
    DynamicArray() : data(nullptr), size_(0), capacity(0) {}

    /// Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    /// Копирующий конструктор (глубокое копирование)
    DynamicArray(const DynamicArray& other) : size_(other.size_), capacity(other.capacity) {
        data = new T[capacity];
        copy(other.data, other.data + size_, data);
    }

    /// Оператор присваивания копированием
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            capacity = other.capacity;
            data = new T[capacity];
            copy(other.data, other.data + size_, data);
        }
        return *this;
    }

    /// Конструктор перемещения
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size_(other.size_), capacity(other.capacity) {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity = 0;
    }

    /// Оператор присваивания перемещением
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size_ = other.size_;
            capacity = other.capacity;

            other.data = nullptr;
            other.size_ = 0;
            other.capacity = 0;
        }
        return *this;
    }

    /// Оператор доступа по индексу (для чтения и записи)
    T& operator[](size_t index) {
        if (index >= size_) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw out_of_range("Index out of range");
        return data[index];
    }

    // ----- Методы -----
    
    /// Добавление элемента в конец массива
    void push_back(const T& value) {
        if (size_ == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Удваиваем размер при необходимости // Тернарный оператор
                                                        //условие ? значение_если_true : значение_если_false;
        }
        data[size_++] = value;
    }
    
    /// Добавление элемента в начало массива(сдвигаем все вправо)
    void push_front(const T & value) {
    if (size_ == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);  //условие ? значение_если_true : значение_если_false;
    }
    for (size_t i = size_; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = value;
    ++size_;
    }

    /// Удаление последнего элемента
    void pop_back() {
        if (size_ == 0) throw out_of_range("Array is empty");
        --size_;
        if (size_ < capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
    }

    /// Получение количества элементов
    size_t size() const {
        return size_;
    }

    /// Вставка элемента в указанную позицию
    void insert(size_t index, const T& value) {
        if (index > size_) throw out_of_range("Index out of range");

        if (size_ == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }

        // Сдвигаем элементы вправо
        for (size_t i = size_; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size_;
    }

    /// Удаление элемента по индексу
    void clear_element(size_t index) {
        if (index >= size_) throw out_of_range("Index out of range");

        // Сдвигаем элементы влево
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size_;

        //сокращение массив при необходимости
        //оптимизация: если массив стал слишком пустым, то мы освобождаем лишнюю память
        //capacity — сколько элементов влезает в текущем выделенном буфере
        //size_ < capacity / 4 — если заполнено меньше четверти
        //resize(capacity / 2) — уменьшаем выделенную память вдвое
        //capacity > 1 — чтобы не сжать до нуля или недопустимого значения
        if (size_ < capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
    }

    /// Поиск элемента по значению
    long long find(const T& value) const {
        return sequential_search1(data, size_, const_cast<T&>(value));
    }

    long long find_sequential(const T& value, function<bool(const T&, const T&)> comp) const {
        return sequential_search(data, size_, value, comp);
    }

    /// Возвращение ссылки на элемент по значению (если найден), иначе исключение
    T& find_ref(const T& value) {
        long long index = sequential_search1(data, size_, value);
        if (index != -1) {
            return data[index];
        }
        throw out_of_range("Element not found");
    }

    /// Реализация сортировки пузырьком
    void sort() {
        BubbleSort(data, size_);
        
        /*if (size_ < 2) return;

        for (size_t i = 0; i < size_ - 1; ++i) { // Проход по элементам
            for (size_t j = 0; j < size_ - i - 1; ++j) { // Попарное сравнение
                if (data[j] > data[j + 1]) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }*/
    }

};

