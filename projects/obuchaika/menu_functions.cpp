#include "menu_functions.hpp"
#include <iostream>
#include <cstdlib>
#include <limits> // добавлено для std::numeric_limits

const vitashaa::MenuItem* MenuFunctions::show_global_menu(const vitashaa::MenuItem* current) {
    std::cout << "0 - Вернуться на уровень выше / Выйти из программы" << std::endl;
    for (int i = 0; i < current->children_count; i++) {
        std::cout << i + 1 << " - " << current->children[i]->title << std::endl;
    }

    std::cout << "Выберите пункт меню: ";
    int n;
    do {
        if (!(std::cin >> n) || n < 0 || n > current->children_count) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод, попробуйте снова!" << std::endl;
            n = -1;
        }
    } while (n < 0 || n > current->children_count);

    if (n == 0) {
        if (current->parent == nullptr) {
            std::cout << "Завершение программы!" << std::endl;
            std::exit(0);
        } else {
            std::cout << "Возврат на уровень выше\n" << std::endl;
            return current->parent;
        }
    }
    std::cout << std::endl;

    return current->children[n - 1];
}

const vitashaa::MenuItem* MenuFunctions::show_element_menu(const vitashaa::MenuItem* current) {
    std::cout << current->title << ":\n";
    return show_global_menu(current);
}

const vitashaa::MenuItem* MenuFunctions::show_element_with_link_menu(const vitashaa::MenuItem* current) {
    std::cout << current->title << ":\n";
    std::cout << "Подробнее по ссылке: " << current->information_link << "\n";
    return show_global_menu(current);
}