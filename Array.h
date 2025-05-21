/*�����: ������� ����� ���-23*/

#pragma once // ������ �� ������������� ���������
#include <iostream>
#include <vector>
#include <chrono>
#include <functional> // ��� function
#include <cassert> // ��� ������ assert

//������ �������� ��� �����, ����������� � ������������ ���� "std"
using namespace std;
using namespace chrono;


///������� ����������� ������ ���������� ������� size - ������ �������, 
//minVal - ����������� ��������, maxVal - ������������ ��������
// ���������� ������� ���������� �������
template <typename T>
void random_array(T* arr, size_t size, int minVal, int maxVal) {
    if (arr == nullptr || size <= 0) { // ���� ������ ����/������ 0
        throw invalid_argument("������ ���� ��� ����� ������������ ������.");
    }
    if (minVal > maxVal) { //���� ����.�������� ������ ���.��������
        throw invalid_argument("����������� �������� ������ �������������."); //����� ������
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> distrib(minVal, maxVal);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
}

// ������� �������� ������� ��������� ������� size, ������������ ���������� ���������� � ������� 
// ������������ � �������� ��������� �� min_val (�� ��������� 0) �� max_val (�� ��������� 10)
template<typename T>
T* random_array_sorted(size_t size, T min, T max) {
    if (static_cast<size_t>(max - min + 1) < size) {
        throw invalid_argument("������������� ��������");
    }

    T* arr = new T[size];
    mt19937 gen(random_device{}());

    // ����������� min ������ ���, ����� ��������� ������� ��� ������ �����������
    T current_min = min;
    for (size_t i = 0; i < size; ++i) {
        uniform_int_distribution<T> dist(current_min, max - (size - i - 1));
        arr[i] = dist(gen);
        current_min = arr[i] + 1;
    }
    return arr;
}

/// ������� ���������� ������� ���������� �������, �� ��������� ��������������
// size - ������ �������, 
// minVal - ����������� ��������, maxVal - ������������ ��������
template <typename T>
T* increasing_array(size_t size, T minVal, T maxVal) {
    if (size <= 0) {
        throw invalid_argument("������ ������� ������ ���� �������������.");
    }
    if (minVal > maxVal) {
        throw invalid_argument("����������� �������� ������ �������������.");
    }

    T* arr = new T[size]; //��������� ������ ��� �������
    if (arr == nullptr) {
        throw runtime_error("�� ������� �������� ������.");
    }

    random_device rd;
    mt19937 gen(rd()); //����������� ��������� ��������� �����
    uniform_int_distribution<T> distrib(minVal, maxVal); //������������� ��� ��������� ����� ����� � �������� ���������

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

// ������� ������ ������� � ����, array - ������, filename - �������� �����, size - ������ �������
//true � ������ �������� ������, false � ������ ������.
template <typename T>
bool write_array_tofile(const T* array, size_t size, const string& filename) {
    if (array == nullptr || size <= 0) {
        return false; //��������� ������ ������� ��� ������������� �������
    }
    ofstream file(filename);

    //������ ��������� ������� � ����
    for (size_t i = 0; i < size; ++i) {
        file << array[i]; //���� ��������
        if (i < size - 1) {
            file << " "; //���������� ������� ����� ���������� (����� ����������)
        }
    }

    //�������� �� ������ ������
    if (file.fail()) {
        cerr << "������: ��������� ������ �� ����� ������ � ����.\n";
        return false;
    }

    file.close(); //�������� �����
    return true;
}


//������� �������� ���������� ������� array �� �����������, size - ������
template <typename T>
bool isSorted(const T* arr, size_t size) {
    if (arr == nullptr || size <= 1) { //���� ������ ������ ��� ���-�� ���������=1
        return true; // ������ ��� �������������� ������ ��������� ���������������
    }
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) { //���� ������ �������� ������ �������
            return false; // ������� ��������� ������� - ������ �� ������������
        }
    }
    return true; // ������ ������������
}


/* �������� */

// ����������� ������� �������� ���� �����
// ����������: ����� ����� a � b.
template<typename T>
T RecursionSum(T a, T b) {
    // ���� ������ ����� ����� 0, ���������� ������ (�������� ���������).
    if (b == 0) {
        return a;
    }

    // ���� ������ ����� ����� 0, ���������� ������ (�������� ���������).
    if (a == 0) {
        return b;
    }

    // ���� b �������������, ��������� ��� �� 1 � ����������� a �� 1.
    // ��� ��������� �������� ����� ����������� �����������.
    if (b > 0) {
        return RecursionSum(a + 1, b - 1);
    }
    else {
        // ���� b �������������, ����������� ��� �� 1 � ��������� a �� 1.
        // ��� ����� ������������ �������� ��� ������������� ���������.
        return RecursionSum(a - 1, b + 1);
    }
}



/* ������ ��������� */

// ������� ����������� ������: ������� ������� ��������,
// � ����� ���������� ���������� ���������, ������� � ������� ����� ��������.
//n � ���-�� ��������� � �������
//avg � ���������� ��� �������� �������� �������� �������
//greater_count � ���-�� ���������, ����������� ������� ��������
//lesser_count � ���-�� ���������, ������� ��������

// ��������� ���������:
// ������ ������: O(n) � ��� ������� �� ������� ����� n (������������ � ���������).
// ������ ������: O(n) � ��� �������� �������� �� �� ��������.
// ������� ������: O(n) � ������ �������� ��������� �� ���������� ���������.

// ���������������� ���������:
// O(1) � ������������ ������������� ���������� �������������� ������, �� ��������� �� ������� �������.

template<typename T>
void analyze_numbers(T* arr, size_t n, double& avg, size_t& greater_count, size_t& lesser_count) {
    avg = 0;
    for (size_t i = 0; i < n; i++) {
        avg += arr[i];
    }
    avg /= n;

    greater_count = 0;
    lesser_count = 0;

    for (size_t i = 0; i < n; i++) {
        if (arr[i] > avg) greater_count++;
        else if (arr[i] < avg) lesser_count++;
    }
}

// ������� ��� ������ ����������� � ����
void write_results(const string& filename, double avg, size_t greater_count, size_t lesser_count) {
    ofstream output(filename);
    if (!output) {
        cerr << "������ �������� �����" << endl;
        return;
    }

    output << "������� ��������: " << avg << endl;
    if (greater_count > lesser_count) {
        output << "������ ��������� > ��������" << endl;
    }
    else if (greater_count < lesser_count) {
        output << "������ ��������� < ��������" << endl;
    }
    else {
        output << "����� ������� � ������� ��������� �����" << endl;
    }

    output.close();
}
    
/// ������������ ���������
/// ������� ��� ���������� ������������ �������
vector<vector<long long>> buildPascalTriangle(size_t n) {
    vector<vector<long long>> pascal(n); // �������������� ������ �� n �����

    // ������� ����: �������� �� ���� ������� ������������
    for (size_t i = 0; i < n; ++i) {
        pascal[i].resize(i + 1);          // ������ ������ i-� ������ (i + 1 ���������)
        pascal[i][0] = pascal[i][i] = 1;   // ������ � ��������� �������� ������ ������ ����� 1

        // ���������� ����: ��������� ���������� �������� ������ (����� �������� ���������)
        for (size_t j = 1; j < i; ++j) {
            // ������ ������� ����� ����� ���� ��������� �� ���������� ������
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }
    return pascal;
}





    
