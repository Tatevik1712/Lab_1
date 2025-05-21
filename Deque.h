#pragma once
#include "Stack.h"   // ���������� ��� ������������� ��������� ����
#include <iostream>
using namespace std;

// ����� Deque<T>: ������������ �������, ������������� �� ���� ������
template<typename T>
class Deque {
private:
    Stack<T> frontStack;  // ���� ��� ���������, ����������� � ������ ����
    Stack<T> backStack;   // ���� ��� ���������, ����������� � ����� ����

    // ��������������� �������:
    // ��������� ��� �������� �� ������ ����� � ������, ���������� �������
    // ��� ������������, ����� ����� ������� �������, � ������ ���� ����
    void transfer(Stack<T>& from, Stack<T>& to) {
        Stack<T> temp;

        // ������� ��������� �������� � ������������� ���� ��� �������
        while (!from.empty()) {
            temp.push(from.top());
            from.pop();
        }

        // ����� ������������� � ������� ����, ��� � ������ �������
        while (!temp.empty()) {
            to.push(temp.top());
            temp.pop();
        }
    }

public:
    // ��������, ���� �� ���
    bool empty() const {
        return frontStack.empty() && backStack.empty();
    }

    // ��������� ���������� ��������� � ����
    size_t size() const {
        return frontStack.size() + backStack.size();
    }

    // ������� �������� � ������
    void push_front(const T& value) {
        frontStack.push(value);  // ������ ��������� �� frontStack
    }

    // ������� �������� � �����
    void push_back(const T& value) {
        backStack.push(value);   // ������ ��������� � backStack
    }

    // �������� �������� �� ������
    T pop_front() {
        if (frontStack.empty()) {
            // ���� frontStack ����, �� ���� �������� � backStack,
            // ��������� �� �� frontStack � �������� �������
            if (backStack.empty()) {
                throw out_of_range("Deque is empty (front)");
            }
            transfer(backStack, frontStack);
        }

        // ������ ����� ��������� ������� ������� �� frontStack
        T value = frontStack.top();
        frontStack.pop();
        return value;
    }

    // �������� �������� � �����
    T pop_back() {
        if (backStack.empty()) {
            // ���� backStack ����, �� frontStack �� ���� �
            // ��������� ���� �������� �� frontStack
            if (frontStack.empty()) {
                throw out_of_range("Deque is empty (back)");
            }
            transfer(frontStack, backStack);
        }

        // ������ ����� ��������� ������� ������� �� backStack
        T value = backStack.top();
        backStack.pop();
        return value;
    }

    // �������� �������� � ������ (��� ��������)
    T peek_front() {
        if (frontStack.empty()) {
            if (backStack.empty()) {
                throw out_of_range("Deque is empty (front)");
            }
            transfer(backStack, frontStack);
        }
        return frontStack.top();
    }

    // �������� �������� � ����� (��� ��������)
    T peek_back() {
        if (backStack.empty()) {
            if (frontStack.empty()) {
                throw out_of_range("Deque is empty (back)");
            }
            transfer(frontStack, backStack);
        }
        return backStack.top();
    }

    // ������ ������� ����
    void clear() {
        frontStack.clear();
        backStack.clear();
    }

    //����� ��������� ����
    void print() const {
        cout << "Deque: ";

        // �������� frontStack � backStack, ����� �� ��������� ���������
        Stack<T> frontCopy = frontStack;
        Stack<T> backCopy = backStack;

        // �������� frontStack � ���������� ������� (������� ���)
        Stack<T> reversedFront;
        while (!frontCopy.empty()) {
            reversedFront.push(frontCopy.top());
            frontCopy.pop();
        }

        while (!reversedFront.empty()) {
            cout << reversedFront.top() << " ";
            reversedFront.pop();
        }

        // �������� backStack ��� ���� (�� ������� � ���)
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
