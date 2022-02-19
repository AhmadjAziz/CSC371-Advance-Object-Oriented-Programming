//
// Created by Ahmad Aziz on 19/02/2022.
//

#ifndef LAB4_CAT_H
#define LAB4_CAT_H

#include <string>

//declaration of class.
class cat {
    // declaring private members.
private:
    std::string name;
    unsigned int lives;

public:
    //declaring public functions.
    cat(std::string name);
    cat(std::string name, unsigned int lives);
    ~cat();

    // getters to return constant references.
    std::string getName() const;
    int getLives() const;
};
#endif
