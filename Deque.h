#pragma once
#include "Stack.h"   // Подключаем уже реализованный шаблонный стек
#include <iostream>
using namespace std;

// Класс Deque<T>: двусторонняя очередь, реализованная на двух стеках
template<typename T>
class Deque {
private:
    Stack<T> frontStack;  // Стек для элементов, добавленных в начало дека
    Stack<T> backStack;   // Стек для элементов, добавленных в конец дека

    // Вспомогательная функция:
    // переносит все элементы из одного стека в другой, инвертируя порядок
    // Это используется, когда нужно извлечь элемент, а нужный стек пуст
    void transfer(Stack<T>& from, Stack<T>& to) {
        Stack<T> temp;

        // Сначала переносим элементы в промежуточный стек для реверса
        while (!from.empty()) {
            temp.push(from.top());
            from.pop();
        }

        // Затем перекладываем в целевой стек, уже в нужном порядке
        while (!temp.empty()) {
            to.push(temp.top());
            temp.pop();
        }
    }

public:
    // Проверка, пуст ли дек
    bool empty() const {
        return frontStack.empty() && backStack.empty();
    }

    // Получение количества элементов в деке
    size_t size() const {
        return frontStack.size() + backStack.size();
    }

    // Вставка элемента в начало
    void push_front(const T& value) {
        frontStack.push(value);  // просто добавляем во frontStack
    }

    // Вставка элемента в конец
    void push_back(const T& value) {
        backStack.push(value);   // просто добавляем в backStack
    }

    // Удаление элемента из начала
    T pop_front() {
        if (frontStack.empty()) {
            // Если frontStack пуст, но есть элементы в backStack,
            // переносим их во frontStack в обратном порядке
            if (backStack.empty()) {
                throw out_of_range("Deque is empty (front)");
            }
            transfer(backStack, frontStack);
        }

        // Теперь можем безопасно удалить элемент из frontStack
        T value = frontStack.top();
        frontStack.pop();
        return value;
    }

    // Удаление элемента с конца
    T pop_back() {
        if (backStack.empty()) {
            // Если backStack пуст, но frontStack не пуст —
            // переносим туда элементы из frontStack
            if (frontStack.empty()) {
                throw out_of_range("Deque is empty (back)");
            }
            transfer(frontStack, backStack);
        }

        // Теперь можем безопасно удалить элемент из backStack
        T value = backStack.top();
        backStack.pop();
        return value;
    }

    // Просмотр элемента в начале (без удаления)
    T peek_front() {
        if (frontStack.empty()) {
            if (backStack.empty()) {
                throw out_of_range("Deque is empty (front)");
            }
            transfer(backStack, frontStack);
        }
        return frontStack.top();
    }

    // Просмотр элемента в конце (без удаления)
    T peek_back() {
        if (backStack.empty()) {
            if (frontStack.empty()) {
                throw out_of_range("Deque is empty (back)");
            }
            transfer(frontStack, backStack);
        }
        return backStack.top();
    }

    // Полная очистка дека
    void clear() {
        frontStack.clear();
        backStack.clear();
    }

    //вывод элементов дека
    void print() const {
        cout << "Deque: ";

        // Копируем frontStack и backStack, чтобы не повредить оригиналы
        Stack<T> frontCopy = frontStack;
        Stack<T> backCopy = backStack;

        // Печатаем frontStack в правильном порядке (сначала дно)
        Stack<T> reversedFront;
        while (!frontCopy.empty()) {
            reversedFront.push(frontCopy.top());
            frontCopy.pop();
        }

        while (!reversedFront.empty()) {
            cout << reversedFront.top() << " ";
            reversedFront.pop();
        }

        // Печатаем backStack как есть (от вершины к дну)
        Stack<T> tempBack;
        while (!backCopy.empty()) {
            tempBack.push(backCopy.top());
            backCopy.pop();
        }
        while (!tempBack.empty()) {
            cout << tempBack.top() << " ";
            tempBack.pop();
        }

        cout << endl;
    }
};
