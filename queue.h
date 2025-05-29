#pragma once

#include "container.h"
#include "doubly_linked_list.h"
#include <stdexcept>

// Очередь на основе двусвязного списка
template<typename T>
class Queue : public Container<T> {
private:
    DoublyLinkedList<T> list;

public:
    Queue() = default;

    // Добавить элемент в очередь (в конец)
    void add(const T& value) override {
        list.pushBack(value);
    }

    // Удалить элемент из очереди (с головы)
    void remove() override {
        if (list.isEmpty()) {
            throw std::out_of_range("Очередь пуста");
        }
        list.popFront();
    }

    // Проверка на пустоту
    bool isEmpty() const override {
        return list.isEmpty();
    }

    // Получить значение первого элемента
    T& front() {
        if (list.isEmpty()) {
            throw std::out_of_range("Очередь пуста");
        }
        return list.front();
    }

    const T& front() const {
        if (list.isEmpty()) {
            throw std::out_of_range("Очередь пуста");
        }
        return list.front();
    }

    // Очистить очередь
    void clear() {
        list.clear();
    }

    // Получить размер очереди
    size_t size() const {
        return list.size();
    }

    // Итератор только для чтения
    using ConstIterator = typename DoublyLinkedList<T>::ConstIterator;
    ConstIterator begin() const { return list.begin(); }
    ConstIterator end() const { return list.end(); }
};