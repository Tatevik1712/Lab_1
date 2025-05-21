/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <cassert>
#include <iostream>
#include "List.h"

using namespace std;
//очищенный список с добавлением элемента
void test_push_front_and_back() {
    DoublyLinkedList<int> list;
    list.push_front(2);
    list.push_back(3);
    list.push_front(1);
    assert(list.find(1) == 0);
    assert(list.find(2) == 1);
    assert(list.find(3) == 2);
    assert(list.size() == 3);
}

void test_insert() {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);
    list.insert(0, 0);
    list.insert(4, 4); // вставка в конец
    assert(list.find(0) == 0);
    assert(list.find(1) == 1);
    assert(list.find(2) == 2);
    assert(list.find(3) == 3);
    assert(list.find(4) == 4);
}

void test_clear_element() {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) list.push_back(i);
    list.clear_element(0); // удалим первый
    list.clear_element(2); // удалим "3"
    assert(list.find(0) == -1);
    assert(list.find(1) == 0);
    assert(list.find(2) == 1);
    assert(list.find(3) == -1);
    assert(list.find(4) == 2);
    assert(list.size() == 3);
}

void test_clear_element_out_of_range() {
    DoublyLinkedList<int> list;
    try {
        list.clear_element(0);
        assert(false); // должно выбросить исключение
    }
    catch (const out_of_range&) {
        assert(true);
    }
}

void test_clear_and_size() {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 10; ++i) list.push_back(i);
    assert(list.size() == 10);
    list.clear();
    assert(list.size() == 0);
    assert(list.find(5) == -1);
}

void test_concat_move() {
    DoublyLinkedList<int> a, b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(3);
    b.push_back(4);
    a.concat_move(b);
    assert(a.size() == 4);
    assert(b.size() == 0); // список b опустел
    assert(a.find(1) == 0);
    assert(a.find(4) == 3);
}

void test_concat_copy() {
    DoublyLinkedList<int> a, b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(3);
    b.push_back(4);
    a.concat_copy(b);
    assert(a.size() == 4);
    assert(b.size() == 2); // b остался прежним
    assert(a.find(3) == 2);
}

void test_find_with_predicate() {
    DoublyLinkedList<string> list;
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");
    // Поиск индекса первого элемента, удовлетворяющего предикату.
    // функция возвращает true, если строка начинается с буквы 'b'.
    // В данном случае, элемент "banana" — второй в списке (индекс 1).
    int idx = list.find([](const string& s) {
        return s.front() == 'b';
        });

    // Проверка, что найденный индекс соответствует ожидаемому значению
    assert(idx == 1);
}

void test_find_from_index() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(10);
    assert(list.find(10, 1) == 2); // 10 после первого
    assert(list.find(10, 3) == -1); // за пределами
}

void test_copy_constructor_and_assignment() {
    DoublyLinkedList<int> original;
    original.push_back(1);
    original.push_back(2);

    DoublyLinkedList<int> copy1(original); // копия
    assert(copy1.size() == 2);
    assert(copy1.find(2) == 1);

    DoublyLinkedList<int> copy2;
    copy2 = original; // копирующее присваивание
    assert(copy2.size() == 2);
    assert(copy2.find(1) == 0);
}

void test_move_constructor_and_assignment() {
    DoublyLinkedList<int> source;
    source.push_back(100);
    source.push_back(200);

    DoublyLinkedList<int> moved1(move(source));
    assert(moved1.size() == 2);
    assert(source.size() == 0);

    DoublyLinkedList<int> another;
    another.push_back(300);
    another = move(moved1);
    assert(another.size() == 2);
    assert(moved1.size() == 0);
}

void run_all_tests_dlist() {
    test_push_front_and_back();
    test_insert();
    test_clear_element();
    test_clear_element_out_of_range();
    test_clear_and_size();
    test_concat_move();
    test_concat_copy();
    test_find_with_predicate();
    test_find_from_index();
    test_copy_constructor_and_assignment();
    test_move_constructor_and_assignment();
    cout << "Все тесты пройдены" << endl;
}
