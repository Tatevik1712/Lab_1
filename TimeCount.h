#pragma once

#include <ctime>    // ���������� ��� ������ � (time)
#include <chrono>   // ���������� ��� ������� ������� (������� �����)
#include <iostream>
using namespace std;

namespace TimeCount {
    //��������� ������� ������ ������� ���� - func
    template<typename Func> //Func - �������������� ���, ��������� �� �������
    int measure_time(Func func) {
        auto t1 = chrono::steady_clock::now(); //������� ����� �� ���������� ����
        func(); //���������� ���������� ����
        auto t2 = chrono::steady_clock::now(); //������� ����� ����� ���������� ����.

        auto delta = chrono::duration_cast<chrono::nanoseconds>(t2 - t1); // ������� ������� 
        //cout << "Time milliseconds: " << delta.count() << endl;
        return delta.count();
    }
}
