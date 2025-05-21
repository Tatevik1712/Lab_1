/*�����: ������� ����� ���-23*/

#pragma once
#include <iostream>
#include <stdexcept>
#include "Array.h"
using namespace std;

/*
 * �������� ����������� ������ ������ ����� �������, ������� ������,
 * ����������� � ������������ ������. ��� ����� ��� ������ � �����������.
 * ������������� ����������� �������� ������ ������, ��-�� ���� ��� �������
 * ����� ���������� � ����� � ��� �� ������, ��� ������.
 * ��� ���������� ������ � ������������ ������� ����� �����������:
 * - ����������� �����������
 * - �������� ������������ ������������
 * - ����������
 * - (�� �����������) ������������ ����������� � �������� ������������
 */

/// ��������� ����� ����������� ������
template<typename T>
class DoublyLinkedList {
private:
    // ���� ������
    struct Node {
        T data;        // ������
        Node* prev;    // ��������� �� ���������� ����
        Node* next;    // ��������� �� ��������� ����

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {} //����������� ����
    };

    Node* head; // ��������� �� ������ ������
    Node* tail; // ��������� �� ����� ������ 
    size_t list_size; // ������ ������

    // ��������������� ������� ��� ����������� �����
    void copy_from(const DoublyLinkedList<T>& other) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);// �������� ��������
            current = current->next;
        }
    }

    // ���������� ��������� �� ���� �� �������, ���� nullptr ���� ������ ��� ������
    Node* get_node_at(size_t position) const {
        if (position >= list_size) return nullptr;
        Node* current = head;
        size_t index = 0;
        while (current && index < position) {
            current = current->next;
            ++index;
        }
        return current;
    }


public:

    // --- ������� ���� ---

    // �����������
    DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    // ����������
    ~DoublyLinkedList() {
        clear();
    }

    // ����������� ����������� (������� ����� ������ ��� ����� �������������) � �������� �����������
    DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), list_size(0) {
        copy_from(other);
    }

    // �������� ������������ ������������ (��������� ����������� ���� ������ �������)
    DoublyLinkedList& operator=(const DoublyLinkedList<T>& other) {
        if (this != &other) {
            clear(); // ������� ������� ������
            copy_from(other); // �������� �� ������� ������
        }
        return *this;
    }

    // ����������� ����������� (���������� ������� �� ���������� ������� � ���� ��� �����������)
    DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept //�������, ��� ����������� �� �������� ����������
        : head(other.head), tail(other.tail), list_size(other.list_size) { //����� �������������� ���� ������ ������� ���������� �� ����������
        other.head = nullptr; //�������� other
        other.tail = nullptr; //other �� ������� ������� � ������� ��������� ��������.
        other.list_size = 0;
    }

    // �������� ������������ ������������ (��������� ���������� ������� �� ���������� ������� � ������������)
    DoublyLinkedList& operator=(DoublyLinkedList<T>&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            list_size = other.list_size;

            other.head = nullptr;
            other.tail = nullptr;
            other.list_size = 0;
        }
        return *this;
    }

    // --- ������ ---

    // �������� ���� ���������
    void clear() {
        Node* current = head;
        while (current) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = tail = nullptr;
        list_size = 0;
    }

    // ������� �������� � ������ ������ O(1)
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        }
        head = new_node;
        if (!tail) {
            tail = head;
        }
        ++list_size; //���������� �������
    }

    // ������� �������� � ����� ������ O(n)
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!tail) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++list_size;
    }

    // ������� �������� �� ������� O(n)
    // �������� �� ������������ �������, ������� � ��������
    void insert(size_t position, const T& value) {
        // ������� � ������
        if (position == 0) {
            push_front(value);
            return;
        }

        // ������� � ����� ��� �� ������� � ���������������� ��� push_back
        if (position >= list_size) {
            push_back(value);
            return;
        }

        // �������� ���� �� ������� (��� ������� ����� ���)
        Node* current = get_node_at(position);

        // ��������: ���� ���� �� ������ � ������ (���� �� ������ ���� ����� ���� �� ������)
        if (!current) {
            throw out_of_range("Position is out of bounds for insert()");
        }

        // ������ ����� ����
        Node* new_node = new Node(value);
        Node* prev_node = current->prev;

        // ������������� ����������
        if (prev_node) {
            prev_node->next = new_node;
        }
        new_node->prev = prev_node;

        new_node->next = current;
        current->prev = new_node;

        ++list_size;
    }


    // �������� �������� �� ������� (������ O(1), �������� O(n))
    void clear_element(size_t position) {
        if (!head) throw out_of_range("List is empty");

        if (position >= list_size) throw out_of_range("Invalid position");

        if (position == 0) {
            Node* to_delete = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr; // ���� ������� ��������� �������
            delete to_delete;
            --list_size;
            return;
        }

        Node* current = get_node_at(position);


        if (!current) throw out_of_range(" ");

        Node* prev_node = current->prev;
        Node* next_node = current->next;

        if (prev_node) prev_node->next = next_node;
        if (next_node) next_node->prev = prev_node;

        if (current == tail) tail = prev_node;

        delete current;
        --list_size;
    }

    // ����� �������� (O(n)) �� ��������
    int find(const T& value) const {
        Node* current = head;
        size_t index = 0;
        while (current) {
            if (current->data == value) return static_cast<int>(index);
            current = current->next;
            ++index; 
        }
        return -1; // �� �������
    }

    
    // ����������: ����� � ��������� ������� ������ (O(n))
    // �������� ����� �������� value �� � ������, � � ������� startIndex.
    // ������ ��� ���������� ������ ��� ���������� ������ ������
    int find(const T& value, size_t startIndex) const {
        if (startIndex >= list_size) return -1;

        Node* current = get_node_at(startIndex); // �������� 'position' �� 'startIndex'
        size_t index = startIndex;               // �������� ���������� index

        while (current) {
            if (current->data == value) return static_cast<int>(index);
            current = current->next;
            ++index;
        }
        return -1; // ������� �� ������
    }


    // ����������: ����� � �������������� ��������� (O(n))
    // ��������� ������ ��� ������� � ��������, � ���������� ������ ������� ��������,
    // ���������������� ����� �������
    template<typename Predicate>
    int find(Predicate pred, size_t startIndex = 0) const {
        Node* current = get_node_at(startIndex);
        size_t index = startIndex;
        while (current) {
            if (pred(current->data)) return static_cast<int>(index);
            current = current->next;
            ++index;
        }
        return -1; // ������� �� ������
    }



    // ����������� (������������) ������� (O(n)) � ��������� �����
    // "������������" ������ ������ � ��������, �� �������� ����� ���������.
    // ���������� �� ������, �� ������ ������ ���������� ������ ����� ������.
    void concat_move(DoublyLinkedList<T>& list) {
        if (!list.head) return; // ������ ������ ����

        if (!head) {
            head = list.head;
            tail = list.tail;
        }
        else {
            tail->next = list.head;
            list.head->prev = tail;
            tail = list.tail;
        }

        // ����� ������������ �������� ������ ������
        list_size += list.list_size;
        list.head = nullptr;
        list.tail = nullptr;
        list.list_size = 0;
    }


    // ����������� (������������) ������� (O(n)) � ������������
    // �������� �������� ������� ������ � �������.
    // ������������ ������ �� ����������, �� ����������� ������ �� ����� ����
    void concat_copy(const DoublyLinkedList<T>& list) {
        Node* current = list.head;
        while (current) {
            push_back(current->data); // ������ ����� ���� �� ������ ������
            current = current->next;
        }
    }


    // ������ ������ O(1)
    size_t size() const {
        return list_size;
    }

    // ����� ������
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }
};
