//
// Created by Ahmad Aziz on 19/02/2022.
//
#include <iostream>
#include "cat.h"

//overloaded constructor
cat::cat(std::string name) {
    this->name = name;
    this->lives = 9; // hard coding the lives.

}

//second overloaded constructor.
cat::cat(std::string name, unsigned int lives) {
    this->name = name;
    this-> lives = lives;
    //std::cout<< "Constructor called with name and lives... \n" << this->name << " has "<< this->lives << "lives.\n";
}

//destructor, prints so we can verify its call.
cat::~cat() {
    std::cout<<"destructor called...\n";
}

//implementing the getter.
const int cat::getLives() {
    return  lives;
}

//implementing the getter.
const std::string cat::getName() {
    return  name;
}

//implementing the setter setName.
void cat::setName(const std::string name){
    std::cout<< "setName has been called!\n";
    this->name = name;
}

/**
 * The functions makes sure cat lives can be reduced but not increased,
 * and if lives are set to 0 the cat dies changing its name by making a setName call.
 * @param lives number of cat lives as an unsigned int
 */
void cat::setLives(const unsigned int lives){
    std::cout<< "setValue has been called!\n";
    if(this->lives > 0 &&  lives == 0){
        this->lives = lives;
        setName("The Cat formerly known as " + cat::getName());
    }else if (lives >= this->lives) {
        return;
    }  else {
        this->lives = lives;
    }
}

