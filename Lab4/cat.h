//
// Created by Ahmad Aziz on 19/02/2022.
//

#ifndef LAB4_CAT_H
#define LAB4_CAT_H

#include <string>

class cat {
private:
    std::string name;
    unsigned int lives;

public:
    cat(std::string name);
    cat(std::string name, unsigned int lives);
    ~cat();


    std::string getName() const;
    int getLives() const;
};
#endif
