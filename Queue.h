#pragma once
#include <iostream>
#include "DinamicArray.h"  

/*
������� (Queue) � ��� ��������� ������,
� ������� �������� ����������� � �����, � ��������� �� ������.
�������� �� �������� FIFO (First In � First Out).
*/
class Queue {
private:
    DynamicArray<int> data;  // ���������� ������������ ������ � �������� ����������� ����������

public:
    // ����������� �� ���������
    Queue() = default;

    // ��������, ����� �� �������
    bool isEmpty() const {
        return data.size() == 0;
    }

    // ���������� �������� � ����� �������
    void Push(int value) {
        data.push_back(value);
    }

    // �������� �������� �� ������ ������� � ������� ��� ��
    int Pop() {
        if (isEmpty()) {
            cerr << "������: ������� ������� ������� �� ������ �������\n";
            return -1;
        }
        int frontValue = data[0];
        data.clear_element(0);  // ������� ������ �������
        return frontValue;
    }

    // �������� ������� �������� ��� ��������
    int Peek() const {
        if (isEmpty()) {
            cerr << "������� �����\n";
            return -1;
        }
        return data[0];
    }

    // ������� �������
    void Clear() {
        while (!isEmpty()) {
            data.clear_element(0);  // ������� �������� �� ������
        }
    }

    // ���������� ��������� � �������
    int Size() const {
        return data.size();
    }

    // ���������� �����: ����� ���� ���������
    void Print() const {
        cout << "�������: ";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
