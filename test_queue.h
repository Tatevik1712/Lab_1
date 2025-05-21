#include <cassert>
#include "Queue.h"  // ������������ ����, ���������� ���������� �������

// ����: ���������� ��������� � �������� �������
void test_push_and_size() {
    Queue q;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    // ��������� 3 �������� � �������
    assert(q.Size() == 3);
}

// ����: �������� ��������� � �������� �������
void test_pop() {
    Queue q;
    q.Push(1);
    q.Push(2);
    q.Push(3);

    // ������� �� ������� � ��������� ��������
    assert(q.Pop() == 1);
    assert(q.Pop() == 2);
    assert(q.Pop() == 3);
    // ����� ���� �������� ������� ������ ���� �����
    assert(q.isEmpty());
}

// ����: �������� ������� �������� ��� �������� (Peek)
void test_peek() {
    Queue q;
    q.Push(5);
    q.Push(7);

    // Peek ���������� ������ ������� (5), �� �� ������� ���
    assert(q.Peek() == 5);
    // ������ ������ �������� �������
    assert(q.Size() == 2);
}

// ����: ���������� ������ isEmpty()
void test_is_empty() {
    Queue q;
    assert(q.isEmpty()); // ������ �������

    q.Push(100);
    assert(!q.isEmpty()); // ������ �� �����

    q.Pop();
    assert(q.isEmpty()); // ����� �������� ����� �����
}

// ����: ������� �������
void test_clear() {
    Queue q;
    q.Clear(); // ������� �������� ������ ������� 
    q.Push(1);
    q.Push(2);
    q.Push(3);

    q.Clear(); // ������� �������

    // ����� ������� ������� �����
    assert(q.isEmpty());
    assert(q.Size() == 0);
}

// ����: ������� �������� �� ������ ������� (�� ������ ������)
void test_underflow() {
    Queue q;

    // ������� ������� �� ������ ������� � ������� -1 � ��������� �� ������
    int result = q.Pop();
    assert(result == -1);

    // ������� ��������� � ������ ������� � ����� ������� -1
    assert(q.Peek() == -1);
}

// ����: �������� ����������� ������� ��������� (FIFO)
void test_queue_order() {
    Queue q;

    // ��������� �������� �� 1 �� 5
    for (int i = 1; i <= 5; ++i) {
        q.Push(i);
    }

    // ������� � ��������� �������: ������ �������� � ��� �� �������
    for (int i = 1; i <= 5; ++i) {
        assert(q.Pop() == i);
    }
}

