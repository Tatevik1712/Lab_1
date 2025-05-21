/*�����: ������� ����� ���-23*/

#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Array.h"

/*
 * �������� ����������� ������ ������ ����� �������, ������� ������,
 * ����������� � ������������ ������. ��� ����� ��� ������ � �����������.
 * ������������� ����������� �������� ������ ������, ��-�� ���� ��� �������
 * ����� ���������� � ����� � ��� �� ������, ��� ������.
 * ��� ���������� ������ � ������������ ������� ����� �����������:
 * - ����������� �����������
 * - �������� ������������ ������������
 * - ����������
 * - ������������ ����������� � �������� ������������
 */

using namespace std;

/// ��������� ����� ������������� �������
template<typename T>
class DynamicArray {
private:
    T* data;           // ��������� �� ������ �������
    size_t size_;      // ������� ���������� ���������
    size_t capacity;   // ����������� ������� (������ ���������� ������)

    ///������� ��� ��������� ������� �������
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity]; // �������� ����� ������
        copy(data, data + size_, new_data);
        delete[] data;                     // ����������� ������ ������
        data = new_data;
        capacity = new_capacity;
    }

public:
    // --- ������� ���� ---

    /// ����������� �� ���������
    DynamicArray() : data(nullptr), size_(0), capacity(0) {}

    /// ����������
    ~DynamicArray() {
        delete[] data;
    }

    /// ���������� ����������� (�������� �����������)
    DynamicArray(const DynamicArray& other) : size_(other.size_), capacity(other.capacity) {
        data = new T[capacity];
        copy(other.data, other.data + size_, data);
    }

    /// �������� ������������ ������������
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            capacity = other.capacity;
            data = new T[capacity];
            copy(other.data, other.data + size_, data);
        }
        return *this;
    }

    /// ����������� �����������
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size_(other.size_), capacity(other.capacity) {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity = 0;
    }

    /// �������� ������������ ������������
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size_ = other.size_;
            capacity = other.capacity;

            other.data = nullptr;
            other.size_ = 0;
            other.capacity = 0;
        }
        return *this;
    }

    /// �������� ������� �� ������� (��� ������ � ������)
    T& operator[](size_t index) {
        if (index >= size_) throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw out_of_range("Index out of range");
        return data[index];
    }

    // ----- ������ -----
    
    /// ���������� �������� � ����� �������
    void push_back(const T& value) {
        if (size_ == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // ��������� ������ ��� ������������� // ��������� ��������
                                                        //������� ? ��������_����_true : ��������_����_false;
        }
        data[size_++] = value;
    }
    
    /// ���������� �������� � ������ �������(�������� ��� ������)
    void push_front(const T & value) {
    if (size_ == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);  //������� ? ��������_����_true : ��������_����_false;
    }
    for (size_t i = size_; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = value;
    ++size_;
    }

    /// �������� ���������� ��������
    void pop_back() {
        if (size_ == 0) throw out_of_range("Array is empty");
        --size_;
        if (size_ < capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
    }

    /// ��������� ���������� ���������
    size_t size() const {
        return size_;
    }

    /// ������� �������� � ��������� �������
    void insert(size_t index, const T& value) {
        if (index > size_) throw out_of_range("Index out of range");

        if (size_ == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }

        // �������� �������� ������
        for (size_t i = size_; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size_;
    }

    /// �������� �������� �� �������
    void clear_element(size_t index) {
        if (index >= size_) throw out_of_range("Index out of range");

        // �������� �������� �����
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size_;

        //���������� ������ ��� �������������
        //�����������: ���� ������ ���� ������� ������, �� �� ����������� ������ ������
        //capacity � ������� ��������� ������� � ������� ���������� ������
        //size_ < capacity / 4 � ���� ��������� ������ ��������
        //resize(capacity / 2) � ��������� ���������� ������ �����
        //capacity > 1 � ����� �� ����� �� ���� ��� ������������� ��������
        if (size_ < capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
    }

    /// ����� �������� �� ��������
    long long find(const T& value) const {
        return sequential_search1(data, size_, const_cast<T&>(value));
    }

    long long find_sequential(const T& value, function<bool(const T&, const T&)> comp) const {
        return sequential_search(data, size_, value, comp);
    }

    /// ����������� ������ �� ������� �� �������� (���� ������), ����� ����������
    T& find_ref(const T& value) {
        long long index = sequential_search1(data, size_, value);
        if (index != -1) {
            return data[index];
        }
        throw out_of_range("Element not found");
    }

    /// ���������� ���������� ���������
    void sort() {
        BubbleSort(data, size_);
        
        /*if (size_ < 2) return;

        for (size_t i = 0; i < size_ - 1; ++i) { // ������ �� ���������
            for (size_t j = 0; j < size_ - i - 1; ++j) { // �������� ���������
                if (data[j] > data[j + 1]) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }*/
    }

};

