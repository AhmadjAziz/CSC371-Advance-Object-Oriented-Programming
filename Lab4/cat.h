//
// Created by Ahmad Aziz on 19/02/2022.
//

#ifndef LAB4_CAT_H
#define LAB4_CAT_H

#include <string>

//declaration of class.
class Cat {
    // declaring private members.
private:
    std::string name;
    unsigned int lives;

public:
    //declaring public functions.
    Cat(std::string name);
    Cat(std::string name, unsigned int lives);
    ~Cat();

    // getters to return constant references.
    const std::string getName();
    const int getLives();

    //declaring public setters.
    void setName(const std:: string name);
    void setLives(const unsigned int lives);

    Cat();
};
#endif
