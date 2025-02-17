#include "menu_items.hpp"
#include "menu_functions.hpp"

// Если есть дочерние элементы меню, их нужно определить
namespace programming_children {
    const vitashaa::MenuItem* const children[] = {
        &vitashaa::ALGORITHMS_LEVEL3,
        &vitashaa::OOP_LEVEL3,
        &vitashaa::DATA_STRUCTURES_LEVEL3
    };
}

namespace algorithms_children {
    const vitashaa::MenuItem* const children[] = {
        &vitashaa::LEARN_SORTING_LEVEL4,
        &vitashaa::LEARN_RECURSION_LEVEL4
    };
}

// Главное меню
const vitashaa::MenuItem vitashaa::MAIN_LEVEL0 = {
    "Главное меню", "", MenuFunctions::show_element_menu, nullptr, programming_children::children, 3
};

// Меню программирования
const vitashaa::MenuItem vitashaa::SUBJECT_CHOICE_LEVEL1 = {
    "Меню программирования", "", MenuFunctions::show_element_menu, &MAIN_LEVEL0, programming_children::children, 3
};

// Уровень 3 - разделы программирования
const vitashaa::MenuItem vitashaa::ALGORITHMS_LEVEL3 = {
    "Алгоритмы", "", MenuFunctions::show_element_menu, &SUBJECT_CHOICE_LEVEL1, algorithms_children::children, 2
};

const vitashaa::MenuItem vitashaa::OOP_LEVEL3 = {
    "Объектно-ориентированное программирование", "https://ru.wikipedia.org/wiki/Объектно-ориентированное_программирование",
    MenuFunctions::show_element_with_link_menu, &SUBJECT_CHOICE_LEVEL1, nullptr, 0
};

const vitashaa::MenuItem vitashaa::DATA_STRUCTURES_LEVEL3 = {
    "Структуры данных", "https://en.wikipedia.org/wiki/Data_structure",
    MenuFunctions::show_element_with_link_menu, &SUBJECT_CHOICE_LEVEL1, nullptr, 0
};

// Уровень 4 - подробности
const vitashaa::MenuItem vitashaa::LEARN_SORTING_LEVEL4 = {
    "Изучение сортировок", "https://en.wikipedia.org/wiki/Sorting_algorithm",
    MenuFunctions::show_element_with_link_menu, &ALGORITHMS_LEVEL3, nullptr, 0
};

const vitashaa::MenuItem vitashaa::LEARN_RECURSION_LEVEL4 = {
    "Изучение рекурсии", "https://en.wikipedia.org/wiki/Recursion",
    MenuFunctions::show_element_with_link_menu, &ALGORITHMS_LEVEL3, nullptr, 0
};