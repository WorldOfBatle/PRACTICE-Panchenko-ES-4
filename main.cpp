#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

// Для локализации
#ifdef _WIN32
#include <windows.h>
#endif

// Функция для решения задачи по варианту 4
void taskVariant4(const std::string& filename) {
    Queue<int> specialGroup;   // Дети и пенсионеры
    Queue<int> regularGroup;   // Остальные

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    int age;
    while (fin >> age) {
        if (age < 5 || age > 70)
            specialGroup.add(age);   // Льготники
        else
            regularGroup.add(age);   // Остальные
    }
    fin.close();

    // После окончания чтения — проверка на ошибку
    if (!fin.eof() && fin.fail()) {
        throw std::runtime_error("Ошибка чтения данных из файла");
    }
    fin.close();

    std::cout << "Возраст пассажиров в порядке посадки на борт:" << std::endl;
    // Сначала дети и пенсионеры
    for (auto it = specialGroup.begin(); it != specialGroup.end(); ++it) {
        std::cout << *it << " ";
    }
    // Затем остальные
    for (auto it = regularGroup.begin(); it != regularGroup.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
#ifdef _WIN32
    // Для корректного вывода
    SetConsoleOutputCP(1251);
#endif

    std::cout << "Практика по C++ (Вариант 4) — Панченко Е.С.\n" << std::endl;

    // Пример
    try {
        taskVariant4("input.txt");
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}