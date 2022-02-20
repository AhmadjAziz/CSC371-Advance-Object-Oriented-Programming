//
// Created by Ahmad Aziz on 19/02/2022.
//

#include <iostream>
#include "cat.h"

int main(int argc, char* argv[]) {
    cat a("Garfield");

    std::cout << a.getName() << " has "
              << a.getLives() << " lives." << std::endl;

    cat b("Mog" , 10);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;

    b.setLives(42);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;

    b.setName("Prince");
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;
    b.setLives(8);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;

    b.setLives(0);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;
    b.setLives(0);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;
    return 0;
}