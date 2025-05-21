#pragma once
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>
#include "Stack.h" // ������������ ��������� ����� Stack, ���������� �� DynamicArray

using namespace std;

/*
    ����������� �����������
    �������������� ���������: +, -, *, /
*/
class PostfixCalculator {
private:
    Stack<double> stack; // ���������� ���� ��� �������� ���������

public:

    // ����� ���������� �������� ��������� � ����������� �������
    double evaluate(const string& expression) {
        istringstream iss(expression); // ����� ��� ������� ������
        string token;

        // ��������� ������ (����� � ���������) �� ������ �� ������
        while (iss >> token) {
            // ���� ����� � ����� (�������� �������������)
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                double num = stod(token);  // ����������� ������ � �����
                stack.push(num);           // ����� ����� � ����
            }
            // ���� ����� � �������� (+, -, *, /)
            else {
                // ��������: ��� ����� �������� �������� ����� ���� �� ��� ����� � �����
                if (stack.size() < 2) {
                    throw runtime_error("������������ ��������� ��� ��������: " + token);
                }

                // ������� ��������� ������ ������� (�� ��� ������� ���������)
                double b = stack.top(); stack.pop();
                // ����� ��������� ������ �������
                double a = stack.top(); stack.pop();

                // ��������� ��������������� ��������
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
                        throw runtime_error("������� �� ���� �����������");
                    }
                    stack.push(a / b);
                }
                else {
                    // ����������� ������ (��������, ^)
                    throw runtime_error("����������� ��������: " + token);
                }
            }
        }

        // ����� ��������� ����� ��������� � ����� ������ �������� ������ ���� ���������
        if (stack.size() != 1) {
            throw runtime_error("������: ��������� ����������� ��� �������");
        }

        // ���������� ��������� � ������� ����
        double result = stack.top();
        stack.pop();
        return result;
    }
};
