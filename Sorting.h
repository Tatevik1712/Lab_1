#pragma once
/*Автор: Саргсян Татев ИВТ-23*/

#include <vector>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()

//строка включает все имена, объявленные в пространстве имен "std"
using namespace std;
using namespace chrono;
/* SORTING */

//Функция сортировки пузырьком arr - массив, size - размер
// BigO (время)
// Лучший случай:   O(n)
// Средний случай:  O(n^2)
// Худший случай:   O(n^2)
// BigO (память):   О(1)
template <typename T>
void BubbleSort(T* arr, size_t size) {
    size_t pass, i;
    size_t temp;
    bool swapped;
    if (size < 2) return; //если массив пуст или из одного элемента
    for (pass = size - 1; pass > 0; pass--) { // для сравнения соседних элементов
        swapped = false;
        // Внутренний цикл проходит по массиву до текущей границы pass,
        // сравнивает соседние элементы и меняет их местами при необходимости.
        for (i = 0; i < pass; i++) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                // swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; //массив уже отсортирован
    }
}

// Сортировка по выбору arr - массив, size - размер
// BigO (время)
// Лучший случай:   O(n^2)
// Средний случай:  O(n^2)
// Худший случай:   O(n^2)
// BigO (память) :  O(1)
template <typename T>
void SelectionSort(T* arr, size_t size) {
    size_t j, i;
    size_t min;
    if (arr == nullptr || size == 0) return;
    // Внутренний цикл ищет минимальный элемент в оставшейся части массива
    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) { //запоминание индекса минимального эл-та
                min = j; // Обновляем индекс минимального элемента
            }
        }
        // Если найден минимальный элемент не на текущей позиции — меняем местами
        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}

//Сортировка вставками arr - массив, size - размер
// BigO (время)
// Лучший случай:   O(n)
// Средний случай:  O(n^2)
// Худший случай:   O(n^2)
// BigO (память):   О(1)
template <typename T>
void InsertionSort(T* arr, size_t size) {
    if (arr == nullptr || size == 0) return;
    for (size_t i = 1; i < size; i++) {
        T key = arr[i];
        size_t j = i;
        // Сдвигаем элементы, большие key, вправо, пока не найдём место для вставки key
        while (j > 0 && arr[j - 1] > key) { // Если элемент слева больше ключа
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

//Сортировка Шела arr - массив, size - размер
// BigO (время)
// Лучший случай:   O(n)
// Средний случай:  -
// Худший случай:   O(n log^2 n)
// BigO (память):   О(1)
template <typename T>
void ShellSort(T* arr, size_t size) {
    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        // Проходим массив с текущим шагом (gap), сортируя элементы внутри подгрупп
        for (size_t i = gap; i < size; i++) {
            T temp = arr[i];
            size_t j;
            // Вставка элемента на своё место в "подмассиве с шагом gap"
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функция для разделения массива на две части относительно опорного элемента.
//arr - массив, low - меньший эл-т, high - больший эл-т
/*template<typename T>
int  partition(T* arr, int low, int high) { //выбор случайного эл-та для уже отсорт.-го массива, перекидываем в конец
    T pivot = arr[high]; // Опорный элемент (последний элемент)
    int i = low;       // Индекс меньшего элемента

    // Если текущий элемент меньше опорного, перемещаем его левее границы
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++; // Сдвигаем границу левой (меньшей) части
        }
    }
    swap(arr[i], arr[high]);
    return i; // Возвращаем индекс опорного элемента
}*/



template<typename T>
int partition(T* arr, int low, int high) {
    // Выбираем случайный индекс в пределах low..high и делаем его опорным
    int pivotIndex = low + rand() % (high - low + 1);
    std::swap(arr[pivotIndex], arr[high]); // Помещаем случайный pivot в конец

    T pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}


/// Сортировка QuickSort 
//arr - массив, low - меньший эл-т, high - больший эл-т
// BigO (время)                     
// Лучший случай:   O(n log n)       
// Средний случай:  O(n log n)
// Худший случай:   O(n ^ 2)
// BigO (память)
// Средний случай:  O(log n)
// Худший случай:   O(n)
template<typename T>
void QuickSort(T* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high); // Индекс опорного элемента

        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
    }
}


// Функция для слияния двух отсортированных подмассивов.
// Объединяет два подмассива arr[left..mid] и arr[mid+1..right] в один отсортированный подмассив.
template<typename T>
void Merge(T* arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1; // Размер левого подмассива
    size_t n2 = right - mid;    // Размер правого подмассива

    // Создаем временные векторы для хранения элементов левого и правого подмассивов
    vector<T> L(n1), R(n2);

    // Копируем данные в временные векторы
    for (size_t i = 0; i < n1; i++) { //функция копи
        L[i] = arr[left + i];
    }
    for (size_t j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Слияние временных векторов обратно в исходный массив
    size_t i = 0; // Индекс для левого подмассива
    size_t j = 0; // Индекс для правого подмассива
    size_t k = left; // Индекс для результирующего массива

    // Слияние двух подмассивов в один отсортированный массив
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // Если элемент из левого подмассива меньше или равен элементу из правого
            arr[k] = L[i]; // Помещаем его в результат
            i++; // Сдвигаем индекс левого подмассива
        }
        else {
            arr[k] = R[j]; // Если элемент из правого подмассива меньше, помещаем его в результат
            j++; // Сдвигаем индекс правого подмассива
        }
        k++; // Сдвигаем индекс результирующего массива
    }

    // Копируем оставшиеся элементы из левого подмассива, если таковые имеются
    while (i < n1) {
        arr[k] = L[i]; // Копируем элемент из левого подмассива
        i++;
        k++; // Сдвигаем индекс результирующего массива
    }

    // Копируем оставшиеся элементы из правого подмассива, если таковые имеются
    while (j < n2) {
        arr[k] = R[j]; // Копируем элемент из правого подмассива
        j++;
        k++; // Сдвигаем индекс результирующего массива
    }
}

// Cортировка слиянием arr - массив, L - перый эл-т, R - правый эл-т
// Сортирует подмассив arr[L..R]
// BigO (время)
// Лучший случай:   O(nlog n)       
// Средний случай:  O(nlog n)
// Худший случай:   O(nlog n)
// BigO (память) :  О(n)
//какой массив необходим
template<typename T>
void MergeSort(T* arr, size_t L, size_t R) {
    if (L < R) {
        size_t mid = L + (R - L) / 2; // Вычисление середины

        // Рекурсивная сортировка левой и правой половин
        MergeSort(arr, L, mid);
        MergeSort(arr, mid + 1, R);
        // Слияние отсортированных половин
        Merge(arr, L, mid, R);
    }
}



//Heap Sort (пирамидальная сортировка)
// Heap Sort (Пирамидальная сортировка)
// Время: O(n log n) — в худшем, среднем и лучшем случаях
// Память: O(1) — сортировка "на месте", не требует дополнительной памяти
// Вспомогательная функция heapify — поддерживает свойство max-кучи
template <typename T>
void heapify(T* arr, size_t size, size_t root) {
    size_t largest = root;         // Изначально считаем, что корень — наибольший
    size_t left = 2 * root + 1;    // Индекс левого потомка
    size_t right = 2 * root + 2;   // Индекс правого потомка

    // Если левый потомок больше корня
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок больше текущего наибольшего
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // Если наибольший — не корень, меняем местами и продолжаем heapify для поддерева
    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, size, largest);  // Рекурсивно heapify затронутое поддерево
    }
}

// Основная функция сортировки Heap Sort
template <typename T>
void HeapSort(T* arr, size_t size) {
    // Строим max-кучу (перестраиваем массив)
    for (int i = size / 2 - 1; i >= 0; i--)  // начинаем с последнего внутреннего узла
        heapify(arr, size, i);

    // Один за другим извлекаем элементы из кучи (в конец массива)
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);      // Перемещаем текущий корень (максимум) в конец
        heapify(arr, i, 0);        // Восстанавливаем кучу для оставшегося массива
    }
}
