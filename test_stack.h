/*Автор: Саргсян Татев ИВТ-23*/

#pragma once
#include "Stack.h"

// Тесты для стека
void test_stack() {
    Stack<int> s;
    assert(s.empty());
    s.push(1);
    assert(!s.empty());
    assert(s.top() == 1);
    s.push(2);
    assert(s.top() == 2);
    s.pop();
    assert(s.top() == 1);
    s.pop();
    assert(s.empty());

    try {
        s.pop();
        assert(false); // не должно сюда дойти
    }
    catch (const out_of_range&) {
        // ожидаемое поведение
    }

    // Дополнительные тесты
    Stack<string> s_str;
    s_str.push("hello");
    s_str.push("world");
    assert(s_str.top() == "world");
    s_str.pop();
    assert(s_str.top() == "hello");
    s_str.pop();
    assert(s_str.empty());
}

// Тесты для калькулятора
void test_calculator() {
    PostfixCalculator calc;
    assert(calc.evaluate("3 4 +") == 7);
    assert(calc.evaluate("10 2 -") == 8);
    assert(calc.evaluate("2 3 *") == 6);
    assert(calc.evaluate("8 4 /") == 2);
    assert(calc.evaluate("5 1 2 + 4 * + 3 -") == 14); // 5 + ((1 + 2) * 4) - 3

    // Дополнительные тесты
    assert(calc.evaluate("7 3 - 2 *") == 8);
    //assert(calc.evaluate("9 3 1 - /") == 3);
    assert(calc.evaluate("2 3 + 5 * 6 -") == 19);
    assert(calc.evaluate("3 4 + 2 * 7 /") == 2);
    assert(calc.evaluate("12 3 / 2 * 1 +") == 9);

    try {
        calc.evaluate("4 0 /");
        assert(false);
    }
    catch (const runtime_error& e) {
        // Division by zero expected
    }

    try {
        calc.evaluate("+");
        assert(false);
    }
    catch (const runtime_error&) {
        // expected error
    }

    try {
        calc.evaluate("1 2"); // too few operators
        assert(false);
    }
    catch (const runtime_error&) {
        // expected error
    }

    try {
        calc.evaluate("2 2 ^"); // unsupported operator
        assert(false);
    }
    catch (const runtime_error&) {
        // expected error
    }
}

int run_all_tests_stack() {
    test_stack();
    test_calculator();
    cout << "Все тесты прошли stack";
    return 0;
}