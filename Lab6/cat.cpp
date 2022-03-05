//
// Created by Ahmad Aziz on 19/02/2022.
//
#include <iostream>
#include "cat.h"


Cat::Cat() {
    this->name = "Tom";
    this->lives = 9;
    std::cout<<"Default Constructor called...\n";
}
//overloaded constructor
Cat::Cat(std::string name) {
    this->name = name;
    this->lives = 9; // hard coding the lives.
    std::cout<<"Constructor called with name...\n";

}

//second overloaded constructor.
Cat::Cat(std::string name, unsigned int lives) {
    this->name = name;
    this->lives = lives;
    std::cout<<"Constructor called with name and lives...\n";
}

//destructor, prints so we can verify its call.
Cat::~Cat() {
    std::cout<<"destructor called...\n";
}

//implementing the getter.
const int Cat::getLives() {
    return  lives;
}

//implementing the getter.
const std::string Cat::getName() {
    return  name;
}

//implementing the setter setName.
void Cat::setName(const std::string name){
    std::cout<< "setName has been called!\n";
    this->name = name;
}

/**
 * The functions makes sure cat lives can be reduced but not increased,
 * and if lives are set to 0 the cat dies changing its name by making a setName call.
 * @param lives number of cat lives as an unsigned int
 */
void Cat::setLives(const unsigned int lives){
    std::cout<< "setValue has been called!\n";
    if(this->lives > 0 &&  lives == 0){
        this->lives = lives;
        setName("The Cat formerly known as " + Cat::getName());
    }else if (lives >= this->lives) {
        return;
    }  else {
        this->lives = lives;
    }
}



