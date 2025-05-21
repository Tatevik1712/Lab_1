#pragma once
#include <iostream>
#include "DinamicArray.h"  

/*
Очередь (Queue) — это структура данных,
в которой элементы добавляются в конец, а удаляются из начала.
Работает по принципу FIFO (First In — First Out).
*/
class Queue {
private:
    DynamicArray<int> data;  // Используем динамический массив в качестве внутреннего контейнера

public:
    // Конструктор по умолчанию
    Queue() = default;

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return data.size() == 0;
    }

    // Добавление элемента в конец очереди
    void Push(int value) {
        data.push_back(value);
    }

    // Удаление элемента из начала очереди и возврат его же
    int Pop() {
        if (isEmpty()) {
            cerr << "Ошибка: попытка извлечь элемент из пустой очереди\n";
            return -1;
        }
        int frontValue = data[0];
        data.clear_element(0);  // Удаляем первый элемент
        return frontValue;
    }

    // Просмотр первого элемента без удаления
    int Peek() const {
        if (isEmpty()) {
            cerr << "Очередь пуста\n";
            return -1;
        }
        return data[0];
    }

    // Очистка очереди
    void Clear() {
        while (!isEmpty()) {
            data.clear_element(0);  // Удаляем элементы по одному
        }
    }

    // Количество элементов в очереди
    int Size() const {
        return data.size();
    }

    // Отладочный метод: вывод всех элементов
    void Print() const {
        cout << "Очередь: ";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
