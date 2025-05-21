#pragma once
/*�����: ������� ����� ���-23*/

#include <vector>
#include <cstdlib> // ��� rand() � srand()
#include <ctime>   // ��� time()

//������ �������� ��� �����, ����������� � ������������ ���� "std"
using namespace std;
using namespace chrono;
/* SORTING */

//������� ���������� ��������� arr - ������, size - ������
// BigO (�����)
// ������ ������:   O(n)
// ������� ������:  O(n^2)
// ������ ������:   O(n^2)
// BigO (������):   �(1)
template <typename T>
void BubbleSort(T* arr, size_t size) {
    size_t pass, i;
    size_t temp;
    bool swapped;
    if (size < 2) return; //���� ������ ���� ��� �� ������ ��������
    for (pass = size - 1; pass > 0; pass--) { // ��� ��������� �������� ���������
        swapped = false;
        // ���������� ���� �������� �� ������� �� ������� ������� pass,
        // ���������� �������� �������� � ������ �� ������� ��� �������������.
        for (i = 0; i < pass; i++) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                // swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; //������ ��� ������������
    }
}

// ���������� �� ������ arr - ������, size - ������
// BigO (�����)
// ������ ������:   O(n^2)
// ������� ������:  O(n^2)
// ������ ������:   O(n^2)
// BigO (������) :  O(1)
template <typename T>
void SelectionSort(T* arr, size_t size) {
    size_t j, i;
    size_t min;
    if (arr == nullptr || size == 0) return;
    // ���������� ���� ���� ����������� ������� � ���������� ����� �������
    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) { //����������� ������� ������������ ��-��
                min = j; // ��������� ������ ������������ ��������
            }
        }
        // ���� ������ ����������� ������� �� �� ������� ������� � ������ �������
        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}

//���������� ��������� arr - ������, size - ������
// BigO (�����)
// ������ ������:   O(n)
// ������� ������:  O(n^2)
// ������ ������:   O(n^2)
// BigO (������):   �(1)
template <typename T>
void InsertionSort(T* arr, size_t size) {
    if (arr == nullptr || size == 0) return;
    for (size_t i = 1; i < size; i++) {
        T key = arr[i];
        size_t j = i;
        // �������� ��������, ������� key, ������, ���� �� ����� ����� ��� ������� key
        while (j > 0 && arr[j - 1] > key) { // ���� ������� ����� ������ �����
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

//���������� ���� arr - ������, size - ������
// BigO (�����)
// ������ ������:   O(n)
// ������� ������:  -
// ������ ������:   O(n log^2 n)
// BigO (������):   �(1)
template <typename T>
void ShellSort(T* arr, size_t size) {
    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        // �������� ������ � ������� ����� (gap), �������� �������� ������ ��������
        for (size_t i = gap; i < size; i++) {
            T temp = arr[i];
            size_t j;
            // ������� �������� �� ��� ����� � "���������� � ����� gap"
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// ������� ��� ���������� ������� �� ��� ����� ������������ �������� ��������.
//arr - ������, low - ������� ��-�, high - ������� ��-�
/*template<typename T>
int  partition(T* arr, int low, int high) { //����� ���������� ��-�� ��� ��� ������.-�� �������, ������������ � �����
    T pivot = arr[high]; // ������� ������� (��������� �������)
    int i = low;       // ������ �������� ��������

    // ���� ������� ������� ������ ��������, ���������� ��� ����� �������
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++; // �������� ������� ����� (�������) �����
        }
    }
    swap(arr[i], arr[high]);
    return i; // ���������� ������ �������� ��������
}*/



template<typename T>
int partition(T* arr, int low, int high) {
    // �������� ��������� ������ � �������� low..high � ������ ��� �������
    int pivotIndex = low + rand() % (high - low + 1);
    std::swap(arr[pivotIndex], arr[high]); // �������� ��������� pivot � �����

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


/// ���������� QuickSort 
//arr - ������, low - ������� ��-�, high - ������� ��-�
// BigO (�����)                     
// ������ ������:   O(n log n)       
// ������� ������:  O(n log n)
// ������ ������:   O(n ^ 2)
// BigO (������)
// ������� ������:  O(log n)
// ������ ������:   O(n)
template<typename T>
void QuickSort(T* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high); // ������ �������� ��������

        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
    }
}


// ������� ��� ������� ���� ��������������� �����������.
// ���������� ��� ���������� arr[left..mid] � arr[mid+1..right] � ���� ��������������� ���������.
template<typename T>
void Merge(T* arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1; // ������ ������ ����������
    size_t n2 = right - mid;    // ������ ������� ����������

    // ������� ��������� ������� ��� �������� ��������� ������ � ������� �����������
    vector<T> L(n1), R(n2);

    // �������� ������ � ��������� �������
    for (size_t i = 0; i < n1; i++) { //������� ����
        L[i] = arr[left + i];
    }
    for (size_t j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // ������� ��������� �������� ������� � �������� ������
    size_t i = 0; // ������ ��� ������ ����������
    size_t j = 0; // ������ ��� ������� ����������
    size_t k = left; // ������ ��� ��������������� �������

    // ������� ���� ����������� � ���� ��������������� ������
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // ���� ������� �� ������ ���������� ������ ��� ����� �������� �� �������
            arr[k] = L[i]; // �������� ��� � ���������
            i++; // �������� ������ ������ ����������
        }
        else {
            arr[k] = R[j]; // ���� ������� �� ������� ���������� ������, �������� ��� � ���������
            j++; // �������� ������ ������� ����������
        }
        k++; // �������� ������ ��������������� �������
    }

    // �������� ���������� �������� �� ������ ����������, ���� ������� �������
    while (i < n1) {
        arr[k] = L[i]; // �������� ������� �� ������ ����������
        i++;
        k++; // �������� ������ ��������������� �������
    }

    // �������� ���������� �������� �� ������� ����������, ���� ������� �������
    while (j < n2) {
        arr[k] = R[j]; // �������� ������� �� ������� ����������
        j++;
        k++; // �������� ������ ��������������� �������
    }
}

// C��������� �������� arr - ������, L - ����� ��-�, R - ������ ��-�
// ��������� ��������� arr[L..R]
// BigO (�����)
// ������ ������:   O(nlog n)       
// ������� ������:  O(nlog n)
// ������ ������:   O(nlog n)
// BigO (������) :  �(n)
//����� ������ ���������
template<typename T>
void MergeSort(T* arr, size_t L, size_t R) {
    if (L < R) {
        size_t mid = L + (R - L) / 2; // ���������� ��������

        // ����������� ���������� ����� � ������ �������
        MergeSort(arr, L, mid);
        MergeSort(arr, mid + 1, R);
        // ������� ��������������� �������
        Merge(arr, L, mid, R);
    }
}



//Heap Sort (������������� ����������)
// Heap Sort (������������� ����������)
// �����: O(n log n) � � ������, ������� � ������ �������
// ������: O(1) � ���������� "�� �����", �� ������� �������������� ������
// ��������������� ������� heapify � ������������ �������� max-����
template <typename T>
void heapify(T* arr, size_t size, size_t root) {
    size_t largest = root;         // ���������� �������, ��� ������ � ����������
    size_t left = 2 * root + 1;    // ������ ������ �������
    size_t right = 2 * root + 2;   // ������ ������� �������

    // ���� ����� ������� ������ �����
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // ���� ������ ������� ������ �������� �����������
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // ���� ���������� � �� ������, ������ ������� � ���������� heapify ��� ���������
    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, size, largest);  // ���������� heapify ���������� ���������
    }
}

// �������� ������� ���������� Heap Sort
template <typename T>
void HeapSort(T* arr, size_t size) {
    // ������ max-���� (������������� ������)
    for (int i = size / 2 - 1; i >= 0; i--)  // �������� � ���������� ����������� ����
        heapify(arr, size, i);

    // ���� �� ������ ��������� �������� �� ���� (� ����� �������)
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);      // ���������� ������� ������ (��������) � �����
        heapify(arr, i, 0);        // ��������������� ���� ��� ����������� �������
    }
}
