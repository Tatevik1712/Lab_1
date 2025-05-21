#include <cassert>
#include "Queue.h"  // Заголовочный файл, содержащий реализацию очереди

// Тест: добавление элементов и проверка размера
void test_push_and_size() {
    Queue q;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    // Ожидается 3 элемента в очереди
    assert(q.Size() == 3);
}

// Тест: удаление элементов и проверка порядка
void test_pop() {
    Queue q;
    q.Push(1);
    q.Push(2);
    q.Push(3);

    // Удаляем по порядку и проверяем значения
    assert(q.Pop() == 1);
    assert(q.Pop() == 2);
    assert(q.Pop() == 3);
    // После всех удалений очередь должна быть пуста
    assert(q.isEmpty());
}

// Тест: проверка первого элемента без удаления (Peek)
void test_peek() {
    Queue q;
    q.Push(5);
    q.Push(7);

    // Peek возвращает первый элемент (5), но не удаляет его
    assert(q.Peek() == 5);
    // Размер должен остаться прежним
    assert(q.Size() == 2);
}

// Тест: корректная работа isEmpty()
void test_is_empty() {
    Queue q;
    assert(q.isEmpty()); // Пустая очередь

    q.Push(100);
    assert(!q.isEmpty()); // Теперь не пуста

    q.Pop();
    assert(q.isEmpty()); // После удаления снова пуста
}

// Тест: очистка очереди
void test_clear() {
    Queue q;
    q.Clear(); // попытка очистить пустую очередь 
    q.Push(1);
    q.Push(2);
    q.Push(3);

    q.Clear(); // Очистка очереди

    // После очистки очередь пуста
    assert(q.isEmpty());
    assert(q.Size() == 0);
}

// Тест: попытка удаления из пустой очереди (не должно падать)
void test_underflow() {
    Queue q;

    // Попытка извлечь из пустой очереди — ожидаем -1 и сообщение об ошибке
    int result = q.Pop();
    assert(result == -1);

    // Попытка заглянуть в пустую очередь — также ожидаем -1
    assert(q.Peek() == -1);
}

// Тест: проверка правильного порядка элементов (FIFO)
void test_queue_order() {
    Queue q;

    // Добавляем элементы от 1 до 5
    for (int i = 1; i <= 5; ++i) {
        q.Push(i);
    }

    // Удаляем и проверяем порядок: должны выходить в том же порядке
    for (int i = 1; i <= 5; ++i) {
        assert(q.Pop() == i);
    }
}

