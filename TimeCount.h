#pragma once

#include <ctime>    // библиотека для работы с (time)
#include <chrono>   // библиотека для отсчёта времени (считать время)
#include <iostream>
using namespace std;

namespace TimeCount {
    //измерение времени работы учатска кода - func
    template<typename Func> //Func - функциональный тип, указатель на функцию
    int measure_time(Func func) {
        auto t1 = chrono::steady_clock::now(); //текущее время до выполнения кода
        func(); //выполнения некоторого кода
        auto t2 = chrono::steady_clock::now(); //текущее время после выполнения кода.

        auto delta = chrono::duration_cast<chrono::nanoseconds>(t2 - t1); // разница времени 
        //cout << "Time milliseconds: " << delta.count() << endl;
        return delta.count();
    }
}
