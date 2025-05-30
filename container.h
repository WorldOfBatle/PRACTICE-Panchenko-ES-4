#pragma once

// Интерфейс контейнера: чисто виртуальные методы
template<typename T>
class Container {
public:
    virtual void add(const T& value) = 0;      // Добавить элемент
    virtual void remove() = 0;                 // Удалить элемент (с головы или с конца)
    virtual bool isEmpty() const = 0;          // Проверка на пустоту
    virtual ~Container() = default;            // Виртуальный деструктор
};