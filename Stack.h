/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <stdexcept>
#include "DinamicArray.h" 

/*Стек - это абстрактная структура данных, представляющая собой 
коллекцию элементов, с двумя основными операциями: 
push (добавляет элемент), 
pop (удаляет последний добавленный элемент).  
Добаление и удалени подчиняется принципу 
FILO (First In, Last Out) – “первым пришел - последним ушел”. 
Иногда принцип называют LIFO.
*/

// Шаблонный класс Stack на основе DynamicArray
template<typename T>
class Stack {
private:
    DynamicArray<T> data;

public:
    // Добавление элемента в стек
    void push(const T& value) {
        data.push_back(value);
    }

    // Удаление верхнего элемента
    void pop() {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    // Получение верхнего элемента (без удаления)
    T top() const {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }
        return data[data.size() - 1];
    }

    // Проверка, пуст ли стек
    bool empty() const {
        return data.size() == 0;
    }

    // Получение количества элементов в стеке
    size_t size() const {
        return data.size();
    }

    //полное очищение стека
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    //Вывод элементов стека
    void print() const {
        cout << "Stack: ";
        for (size_t i = data.size(); i > 0; --i) {
            cout << data[i - 1] << " ";
        }
        cout << "\n";
    }

    //Просмотр n-го элемента от вершины (без удаления)
    T peek(size_t n) const {
        if (n >= size()) throw out_of_range("Peek out of range");
        return data[size() - 1 - n];
    }

};
