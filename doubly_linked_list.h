#pragma once

#include <cstddef> // для size_t
#include <stdexcept> // для std::out_of_range

// Шаблон двусвязного списка
template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t listSize;

    // Вспомогательная функция очистки памяти (используется в деструкторе и clear)
    void clearList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    // Вспомогательная функция глубокого копирования
    void copyFrom(const DoublyLinkedList& other) {
        Node* curr = other.head;
        while (curr != nullptr) {
            pushBack(curr->data);
            curr = curr->next;
        }
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    // Копирующий конструктор (глубокое копирование)
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        copyFrom(other);
    }

    // Оператор присваивания (глубокое копирование, защита от самоприсваивания)
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clearList();
            copyFrom(other);
        }
        return *this;
    }

    // Деструктор
    ~DoublyLinkedList() {
        clearList();
    }

    // Добавить элемент в конец
    void pushBack(const T& value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++listSize;
    }

    // Удалить элемент с начала
    void popFront() {
        if (head == nullptr) {
            throw std::out_of_range("Список пуст");
        }
        Node* toDelete = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr; // если список стал пустым
        delete toDelete;
        --listSize;
    }

    // Получить значение первого элемента
    T& front() {
        if (head == nullptr) {
            throw std::out_of_range("Список пуст");
        }
        return head->data;
    }

    const T& front() const {
        if (head == nullptr) {
            throw std::out_of_range("Список пуст");
        }
        return head->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return listSize == 0;
    }

    // Очистить список
    void clear() {
        clearList();
    }

    // Получить размер списка
    size_t size() const {
        return listSize;
    }

    // Итератор только для чтения
    class ConstIterator {
    private:
        Node* node;
    public:
        ConstIterator(Node* ptr) : node(ptr) {}
        bool operator!=(const ConstIterator& other) const { return node != other.node; }
        const T& operator*() const { return node->data; }
        ConstIterator& operator++() { node = node->next; return *this; }
    };

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
};