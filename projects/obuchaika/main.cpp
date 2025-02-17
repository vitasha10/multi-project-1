#include <clocale>
#include <iostream>
#include "menu_items.hpp"
#include "menu_functions.hpp"

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::cout << "Добро пожаловать в интерактивную программу обучения Виталия Сухоплечева!\n";

    const vitashaa::MenuItem *current = &vitashaa::MAIN_LEVEL0;

    do {
        current = current->itemfunction(current);
    } while (true);

    return 0;
}