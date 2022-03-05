//
// Created by Ahmad Aziz on 19/02/2022.
//

#ifndef LAB4_CAT_H
#define LAB4_CAT_H
#include <string>

#include <sstream>

namespace std {
template <>
struct hash<Cat> {
size_t operator()(const Cat &obj) const {
unsigned long hash = 0;
std::stringstream sstr;
sstr << obj;
std::string str = sstr.str();

std::size_t hash1 =  std::hash<Cat>()(str);

return hash1;
}
};
}

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

friend std::ostream &operator<<(std::ostream &os, const Cat& cat);

    Cat();
};
#endif
