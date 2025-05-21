/*�����: ������� ����� ���-23*/

#pragma once
#include <stdexcept>
#include "DinamicArray.h" 

/*���� - ��� ����������� ��������� ������, �������������� ����� 
��������� ���������, � ����� ��������� ����������: 
push (��������� �������), 
pop (������� ��������� ����������� �������).  
��������� � ������� ����������� �������� 
FILO (First In, Last Out) � ������� ������ - ��������� ����. 
������ ������� �������� LIFO.
*/

// ��������� ����� Stack �� ������ DynamicArray
template<typename T>
class Stack {
private:
    DynamicArray<T> data;

public:
    // ���������� �������� � ����
    void push(const T& value) {
        data.push_back(value);
    }

    // �������� �������� ��������
    void pop() {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    // ��������� �������� �������� (��� ��������)
    T top() const {
        if (empty()) {
            throw out_of_range("Stack is empty");
        }
        return data[data.size() - 1];
    }

    // ��������, ���� �� ����
    bool empty() const {
        return data.size() == 0;
    }

    // ��������� ���������� ��������� � �����
    size_t size() const {
        return data.size();
    }

    //������ �������� �����
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    //����� ��������� �����
    void print() const {
        cout << "Stack: ";
        for (size_t i = data.size(); i > 0; --i) {
            cout << data[i - 1] << " ";
        }
        cout << "\n";
    }

    //�������� n-�� �������� �� ������� (��� ��������)
    T peek(size_t n) const {
        if (n >= size()) throw out_of_range("Peek out of range");
        return data[size() - 1 - n];
    }

};
