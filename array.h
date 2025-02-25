// Защита от многократного включения
#include <iostream>
#include <vector>
using namespace std; // Использование пространства имен std для упрощения записи

//сделала шаблонные функции
//исправлены комментарии
//исправила функцию сохранение массива в файл


///Функция заполняющая массив рандомными числами size - размер массива, 
//minVal - минимальное значение, maxVal - максимальное значение
// Заполнение массива случайными числами
template <typename T>
void random_array(T* arr, size_t size, int minVal, int maxVal) {
    if (arr == nullptr || size <= 0) { // если массив пуст/размер 0
        throw invalid_argument("Массив пуст или имеет недопустимый размер.");
    }
    if (minVal > maxVal) { //если макс.значение больше мин.значения
        throw invalid_argument("Минимальное значение больше максимального."); //вывод ошибки
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> distrib(minVal, maxVal);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
}

/// функция увеличения массива случайными числами, но монотонно увеличивающими
// size - размер массива, 
// minVal - минимальное значение, maxVal - максимальное значение
template <typename T>
T* increasing_array(size_t size, T minVal, T maxVal) {
    if (size <= 0) {
        throw invalid_argument("Размер массива должен быть положительным.");
    }
    if (minVal > maxVal) {
        throw invalid_argument("Минимальное значение больше максимального.");
    }

    T* arr = new T[size]; //выделение памяти для массива
    if (arr == nullptr) {
        throw runtime_error("Не удалось выделить память.");
    }

    random_device rd;
    mt19937 gen(rd()); //стандартный генератор случайных чисел
    uniform_int_distribution<T> distrib(minVal, maxVal); //распределение для генерации целых чисел в заданном диапазоне

    arr[0] = minVal;//
    T prev = minVal;
    for (size_t i = 1; i < size; ++i) {
        T next = distrib(gen);
        while (next <= prev) {
            next = distrib(gen);
        }
        arr[i] = next;
        prev = next;
    }
    return arr;
}



// Функция записи массива в файл, array - массив, filename - название файла, size - размер массива
//true в случае успешной записи, false в случае ошибки.
template <typename T>
bool write_array_tofile(const T* array, size_t size, const string& filename) {
    if (array == nullptr || size <= 0) {
        return false; //обработка случая пустого или некорректного массива
    }
    ofstream file(filename);

    //запись элементов массива в файл
    for (size_t i = 0; i < size; ++i) {
        file << array[i]; //ввод элемента
        if (i < size - 1) {
            file << " "; //добавление пробела между элементами (кроме последнего)
        }
    }

    //проверка на ошибки записи
    if (file.fail()) {
        cerr << "Ошибка: Произошла ошибка во время записи в файл.\n";
        return false;
    }

    file.close(); //закрытие файла
    return true;
}


//Функция проверки сортировки массива array по возрастанию, size - размер
template <typename T>
bool isSorted(const T* arr, size_t size) {
    if (arr == nullptr || size <= 1) { //если массив пустой или кол-во элементов=1
        return true; // Пустой или одноэлементный массив считается отсортированным
    }
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) { //если второй эелемент больше первого
            return false; // Найдено нарушение порядка - массив не отсортирован
        }
    }
    return true; // Все элементы в порядке - массив отсортирован
}

// Шаблонная функция для последовательного поиска в массиве
template <typename T>
int sequential_search(const T* arr, size_t size, const T& target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;  //возвращаем индекс найденного элемента
        }
    }
}