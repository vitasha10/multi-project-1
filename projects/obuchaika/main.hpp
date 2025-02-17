#ifndef MENU_HPP
#define MENU_HPP

#include <string>

namespace vitashaa {

    struct MenuItem {
        std::string title;
        std::string information_link;
        const MenuItem* (*itemfunction)(const MenuItem*);
        const MenuItem* parent;
        const MenuItem* const* children;
        int children_count;
    };

}

#endif