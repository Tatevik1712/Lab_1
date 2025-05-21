#pragma once
/*�����: ������� ����� ���-23*/

#include <functional> // ��� std::function

/* SEARCHING */

// ��������� ������� ��� ����������������� ������ � �������
// BigO (�����)
// ������ ������:  O(1)
// ������� ������: O(n)
// ������ ������:  O(n)
// BigO (������) : O(1)
template <typename T>
long long sequential_search1(const T* arr, size_t size, const T& num) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return i;  //���������� ������ ���������� ��������
        }
    }
    return -1;
}

// ������� ��� ����������������� ������ � ���������� ������������ ������� ���������
// arr - ������, size - ������, target - ������� ��������, comp - ������� ���������  
// (function, �������������� ����� ������������ �������, ����������� ��� ����������� 
// ������ �� ������� ���� T � ������������ bool (������ ��� ����). ��� ������� ����������, 
// ��� ���������� �������� ������� � ������� ���������)
// ��������� ������������ �� ������ ������� ��������� (==), ��������:
//��������� ����� ��� ����� ��������.
//��������� �������� �� ������ - �� ����������� ��������.
//��������� ����� � ������ �����������.
template <typename T>
long long sequential_search(const T* arr, size_t size, const T& target, function<bool(const T&, const T&)> comp) {
    for (size_t i = 0; i < size; ++i) {
        if (comp(arr[i], target)) {
            return i;  // ���������� ������ ���������� ��������
        }
    }
    return -1;
}

// ������� ��� ��������� ������ (������ ������ ���� ������������)
// BigO (�����)
// ������ ������:  O(1)
// ������� ������: O(log n)
// ������ ������:  O(log n)
// BigO (������) : O(1)
template<typename T>
long long binary_search(const T* arr, size_t size, const T& target) {
    if (size == 0) return -1; // �����: �������� �� ������ ������!
    size_t left = 0, right = size - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ������� ��� ����������������� ������ (��� ���������� �������������� ������)
// BigO 
// ������ ������:   O(1)
// ������� ������:  O(log log n)
// ������ ������:   O(n)
// BigO (������) :  O(1)
template <typename T>
long long interpolation_search(const T* arr, size_t size, const T& target) {
    size_t left = 0, right = size - 1;
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            if (arr[left] == target) return left;
            return -1;
        }
        if (arr[right] == arr[left]) return -1;

        size_t pos = left + ((target - arr[left]) * (right - left) / (arr[right] - arr[left])); //������� ���������� ������� ������� �����
        if (pos >= size) return -1;

        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return -1;
}
