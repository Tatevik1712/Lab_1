/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <iostream>
#include <stdexcept>
#include "Array.h"
using namespace std;

/*
 * Глубокое копирование создаёт полную копию объекта, включая данные,
 * размещённые в динамической памяти. Это важно при работе с указателями.
 * Поверхностное копирование копирует только адреса, из-за чего два объекта
 * могут обращаться к одной и той же памяти, что опасно.
 * Для корректной работы с динамической памятью нужно реализовать:
 * - конструктор копирования
 * - оператор присваивания копированием
 * - деструктор
 * - (по возможности) перемещающий конструктор и оператор присваивания
 */

/// Шаблонный класс Двусвязного списка
template<typename T>
class DoublyLinkedList {
private:
    // Узел списка
    struct Node {
        T data;        // Данные
        Node* prev;    // Указатель на предыдущий узел
        Node* next;    // Указатель на следующий узел

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {} //констурктор узла
    };

    Node* head; // Указатель на начало списка
    Node* tail; // Указатель на конец списка 
    size_t list_size; // размер списка

    // Вспомогательная функция для копирования узлов
    void copy_from(const DoublyLinkedList<T>& other) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);// копируем значения
            current = current->next;
        }
    }

    // Возвращает указатель на узел по индексу, либо nullptr если индекс вне границ
    Node* get_node_at(size_t position) const {
        if (position >= list_size) return nullptr;
        Node* current = head;
        size_t index = 0;
        while (current && index < position) {
            current = current->next;
            ++index;
        }
        return current;
    }


public:

    // --- Правило пяти ---

    // Конструктор
    DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    // Деструктор
    ~DoublyLinkedList() {
        clear();
    }

    // Конструктор копирования (создает новый обьект как копию существующего) — глубокое копирование
    DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), list_size(0) {
        copy_from(other);
    }

    // Оператор присваивания копированием (позволяет присваивать один обьект другому)
    DoublyLinkedList& operator=(const DoublyLinkedList<T>& other) {
        if (this != &other) {
            clear(); // очищаем текущие данные
            copy_from(other); // копируем из другого списка
        }
        return *this;
    }

    // Конструктор перемещения (перемещает ресурсы из временного обьекта в ноый без копирования)
    DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept //обещает, что конструктор не выбросит исключения
        : head(other.head), tail(other.tail), list_size(other.list_size) { //Прямо инициализирует поля нового объекта значениями из временного
        other.head = nullptr; //обнуляем other
        other.tail = nullptr; //other не владеет данными — ресурсы полностью переданы.
        other.list_size = 0;
    }

    // Оператор присваивания перемещением (позволяет перемещать ресурсы из временного обьекта в существующий)
    DoublyLinkedList& operator=(DoublyLinkedList<T>&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            list_size = other.list_size;

            other.head = nullptr;
            other.tail = nullptr;
            other.list_size = 0;
        }
        return *this;
    }

    // --- Методы ---

    // Удаление всех элементов
    void clear() {
        Node* current = head;
        while (current) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = tail = nullptr;
        list_size = 0;
    }

    // Вставка элемента в начало списка O(1)
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        }
        head = new_node;
        if (!tail) {
            tail = head;
        }
        ++list_size; //увеличение размера
    }

    // Вставка элемента в конец списка O(n)
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!tail) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++list_size;
    }

    // Вставка элемента на позицию O(n)
    // Проверка на корректность позиции, вставка в середину
    void insert(size_t position, const T& value) {
        // Вставка в начало
        if (position == 0) {
            push_front(value);
            return;
        }

        // Вставка в конец или за пределы — интерпретируется как push_back
        if (position >= list_size) {
            push_back(value);
            return;
        }

        // Получаем узел по позиции (для вставки перед ним)
        Node* current = get_node_at(position);

        // Проверка: если узел не найден — ошибка (хотя по логике выше этого быть не должно)
        if (!current) {
            throw out_of_range("Position is out of bounds for insert()");
        }

        // Создаём новый узел
        Node* new_node = new Node(value);
        Node* prev_node = current->prev;

        // Перенастройка указателей
        if (prev_node) {
            prev_node->next = new_node;
        }
        new_node->prev = prev_node;

        new_node->next = current;
        current->prev = new_node;

        ++list_size;
    }


    // Удаление элемента по позиции (начало O(1), середина O(n))
    void clear_element(size_t position) {
        if (!head) throw out_of_range("List is empty");

        if (position >= list_size) throw out_of_range("Invalid position");

        if (position == 0) {
            Node* to_delete = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr; // Если удалили последний элемент
            delete to_delete;
            --list_size;
            return;
        }

        Node* current = get_node_at(position);


        if (!current) throw out_of_range(" ");

        Node* prev_node = current->prev;
        Node* next_node = current->next;

        if (prev_node) prev_node->next = next_node;
        if (next_node) next_node->prev = prev_node;

        if (current == tail) tail = prev_node;

        delete current;
        --list_size;
    }

    // Поиск элемента (O(n)) по значению
    int find(const T& value) const {
        Node* current = head;
        size_t index = 0;
        while (current) {
            if (current->data == value) return static_cast<int>(index);
            current = current->next;
            ++index; 
        }
        return -1; // Не найдено
    }

    
    // Перегрузка: поиск с указанием позиции начала (O(n))
    // Начинает поиск элемента value не с начала, а с позиции startIndex.
    // Удобно для повторного поиска или частичного обхода списка
    int find(const T& value, size_t startIndex) const {
        if (startIndex >= list_size) return -1;

        Node* current = get_node_at(startIndex); // заменили 'position' на 'startIndex'
        size_t index = startIndex;               // объявили переменную index

        while (current) {
            if (current->data == value) return static_cast<int>(index);
            current = current->next;
            ++index;
        }
        return -1; // элемент не найден
    }


    // Перегрузка: поиск с использованием предиката (O(n))
    // Принимает лямбду или функцию — предикат, и возвращает индекс первого элемента,
    // удовлетворяющего этому условию
    template<typename Predicate>
    int find(Predicate pred, size_t startIndex = 0) const {
        Node* current = get_node_at(startIndex);
        size_t index = startIndex;
        while (current) {
            if (pred(current->data)) return static_cast<int>(index);
            current = current->next;
            ++index;
        }
        return -1; // Элемент не найден
    }



    // Объединение (конкатенация) списков (O(n)) с переносом узлов
    // "Присоединяет" другой список к текущему, не создавая копий элементов.
    // Эффективно по памяти, но другой список становится пустым после вызова.
    void concat_move(DoublyLinkedList<T>& list) {
        if (!list.head) return; // Другой список пуст

        if (!head) {
            head = list.head;
            tail = list.tail;
        }
        else {
            tail->next = list.head;
            list.head->prev = tail;
            tail = list.tail;
        }

        // После конкатенации обнуляем другой список
        list_size += list.list_size;
        list.head = nullptr;
        list.tail = nullptr;
        list.list_size = 0;
    }


    // Объединение (конкатенация) списков (O(n)) с копированием
    // Копирует элементы другого списка в текущий.
    // Оригинальный список не изменяется, но расходуется память на новые узлы
    void concat_copy(const DoublyLinkedList<T>& list) {
        Node* current = list.head;
        while (current) {
            push_back(current->data); // создаём новые узлы на основе данных
            current = current->next;
        }
    }


    // Размер списка O(1)
    size_t size() const {
        return list_size;
    }

    // Вывод списка
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }
};
