/*Автор: Саргсян Татев ИВТ-23*/

/*lab_1.cpp*/

#include <iostream> //библиотека для стандартных ввода-вывода 
#include <vector> // Заголовочный файл для работы с вектором
#include <fstream> //библиотека для работы с файлами
#include <random> //библиотека для работы со случайными значениями
#include <stdexcept> //Заголовочный файл, используемый для сообщений об исключениях
#include <cassert> //для тестов assert
#include <ctime>   //для time()
#include <cstdlib> //для rand() и srand()
#include <chrono>
#include <string>
#include "Array.h"
#include "DinamicArray.h"
#include "List.h"
#include "TimeMeasure.h"
#include "Queue.h"


//#include "test_dlist.h"
//#include "test_darray.h"
//#include "test_stack.h"
//#include "test_array.h"
#include "test_queue.h"




//строка включает все имена, объявленные в пространстве имен "std"
using namespace std;
//строка включает все имена, объявленные в пространстве имен "chrono"
using namespace chrono;
using namespace TimeCount;
using namespace TimeMeasure;



int main() {
    setlocale(LC_ALL, "Russian");
    TimeMeasure::run();  // вызываем функцию, которая запускает все измерения
    /*test_push_and_size();
    test_pop();
    test_peek();
    test_is_empty();
    test_clear();
    test_underflow();
    test_queue_order();
    cout << endl << "Успешно";*/
    return 0;
    
}

