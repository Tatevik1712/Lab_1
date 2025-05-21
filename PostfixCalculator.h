#pragma once
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include "Stack.h" // Используется шаблонный класс Stack, основанный на DynamicArray

using namespace std;

/*
    Постфиксный калькулятор
    Поддерживаемые операторы: +, -, *, /
*/
class PostfixCalculator {
private:
    Stack<double> stack; // Используем стек для хранения операндов

public:

    // Метод вычисления значения выражения в постфиксной нотации
    double evaluate(const string& expression) {
        istringstream iss(expression); // Поток для разбора строки
        string token;

        // Считываем токены (числа и операторы) из строки по одному
        while (iss >> token) {
            // Если токен — число (возможно отрицательное)
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                double num = stod(token);  // Преобразуем строку в число
                stack.push(num);           // Кладём число в стек
            }
            // Если токен — оператор (+, -, *, /)
            else {
                // Проверка: для любой бинарной операции нужно хотя бы два числа в стеке
                if (stack.size() < 2) {
                    throw runtime_error("Недостаточно операндов для операции: " + token);
                }

                // Сначала извлекаем второй операнд (он был положен последним)
                double b = stack.top(); stack.pop();
                // Затем извлекаем первый операнд
                double a = stack.top(); stack.pop();

                // Выполняем соответствующую операцию
                if (token == "+") {
                    stack.push(a + b);
                }
                else if (token == "-") {
                    stack.push(a - b);
                }
                else if (token == "*") {
                    stack.push(a * b);
                }
                else if (token == "/") {
                    if (b == 0) {
                        throw runtime_error("Деление на ноль недопустимо");
                    }
                    stack.push(a / b);
                }
                else {
                    // Неизвестный символ (например, ^)
                    throw runtime_error("Неизвестный оператор: " + token);
                }
            }
        }

        // После обработки всего выражения в стеке должен остаться только один результат
        if (stack.size() != 1) {
            throw runtime_error("Ошибка: выражение некорректно или неполно");
        }

        // Возвращаем результат и очищаем стек
        double result = stack.top();
        stack.pop();
        return result;
    }
};
