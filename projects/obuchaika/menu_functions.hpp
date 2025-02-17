#ifndef MENU_FUNCTIONS_HPP
#define MENU_FUNCTIONS_HPP

#include "main.hpp"

namespace MenuFunctions {

    const vitashaa::MenuItem* show_global_menu(const vitashaa::MenuItem* current);
    const vitashaa::MenuItem* show_element_menu(const vitashaa::MenuItem* current);
    const vitashaa::MenuItem* show_element_with_link_menu(const vitashaa::MenuItem* current);

}

#endif