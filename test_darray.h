/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include <cassert>
#include <iostream>
#include "DinamicArray.h"

using namespace std;

void test_push_back_and_index() {
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    assert(arr.size() == 3);
    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    // Проверка выхода за границу — ожидаем исключение
    bool exceptionThrown = false;
    try {
        int value = arr[3];  // должно выбросить исключение
    }
    catch (const out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown && "Expected out_of_range exception for arr[3]");
}

void test_push_front() {
    DynamicArray<int> arr;
    arr.push_front(30);
    arr.push_front(20);
    arr.push_front(10);
    assert(arr.size() == 3);
    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    // Проверка выхода за границу — ожидаем исключение
    bool exceptionThrown = false;
    try {
        int value = arr[3];  // должно выбросить исключение
    }
    catch (const out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown && "Expected out_of_range exception for arr[3]");
}

void test_insert_middle() {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.insert(1, 2); // Вставка в середину
    assert(arr.size() == 3);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
}

void test_insert_at_start_and_end() {
    DynamicArray<int> arr;
    arr.insert(0, 10); // Вставка в начало
    arr.insert(1, 30); // Вставка в конец
    arr.insert(1, 20); // Вставка в середину
    arr.insert(1, 25); // Вставка в cлучайное

    assert(arr.size() == 4);
    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    assert(arr[3] == 25);
}

void test_clear_element_middle() {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.clear_element(1);
    assert(arr.size() == 2);
    assert(arr[0] == 1);
    assert(arr[1] == 3);
}

void test_clear_element_bounds() {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.clear_element(0); // Удаляем начало
    arr.clear_element(1); // Удаляем конец
    assert(arr.size() == 1);
    assert(arr[0] == 2);
}

void test_clear_element_out_of_range() {
    DynamicArray<int> arr;
    arr.push_back(10);
    try {
        arr.clear_element(5);
        assert(false); // Исключение обязательно
    }
    catch (const out_of_range&) {
    }
}

void test_pop_back() {
    DynamicArray<int> arr;
    arr.push_back(5);
    arr.push_back(6);
    arr.pop_back();
    assert(arr.size() == 1);
    assert(arr[0] == 5);
}

void test_pop_back_empty() {
    DynamicArray<int> arr;
    try {
        arr.pop_back();
        assert(false);
    }
    catch (const out_of_range&) {
    }
}

void test_find_existing_and_missing() {
    DynamicArray<int> arr;
    arr.push_back(100);
    arr.push_back(200);
    assert(arr.find(100) == 0);
    assert(arr.find(200) == 1);
    assert(arr.find(999) == -1);
}

void test_find_ref() {
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    // Проверка успешного поиска
    int& ref = arr.find_ref(20);
    assert(ref == 20);
    ref = 99;
    assert(arr[1] == 99);  // проверяем, что значение реально изменилось

    // Проверка исключения
    try {
        arr.find_ref(999); // не существует
        assert(false);     // если сюда дошло — тест не прошёл
    }
    catch (const std::out_of_range&) {
        assert(true);      // исключение ожидаемо
    }
}


void test_sort_sorted_and_single() {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.sort(); // Уже отсортировано
    assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3);

    DynamicArray<int> single;
    single.push_back(42);
    single.sort(); // 1 элемент
    assert(single[0] == 42);
}

void test_copy_constructor_and_assignment() {
    DynamicArray<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);

    // Копирующий конструктор
    DynamicArray<int> arr2 = arr1;
    assert(arr2.size() == 2);
    assert(arr2[0] == 1 && arr2[1] == 2);

    // Оператор присваивания
    DynamicArray<int> arr3;
    arr3 = arr1;
    assert(arr3.size() == 2);
    assert(arr3[0] == 1 && arr3[1] == 2);

    // Убедимся в глубоком копировании (разные массивы)
    arr1[0] = 99;
    assert(arr2[0] == 1);
    assert(arr3[0] == 1);
}

void test_move_constructor_and_assignment() {
    DynamicArray<int> original;
    original.push_back(10);
    original.push_back(20);

    DynamicArray<int> moved = move(original);
    assert(moved.size() == 2);
    assert(moved[0] == 10);
    assert(original.size() == 0);

    DynamicArray<int> another;
    another = move(moved);
    assert(another.size() == 2);
    assert(another[1] == 20);
    assert(moved.size() == 0);

}

int run_all_tests_darray() {
    test_push_back_and_index();
    test_push_front();
    test_insert_middle();
    test_insert_at_start_and_end();
    test_clear_element_middle();
    test_clear_element_bounds();
    test_clear_element_out_of_range();
    test_pop_back();
    test_pop_back_empty();
    test_find_existing_and_missing();
    test_sort_sorted_and_single();
    test_copy_constructor_and_assignment();
    test_move_constructor_and_assignment();
    test_find_ref();

    cout << "\nВсе тесты прошли" << endl;
    return 0;
}
