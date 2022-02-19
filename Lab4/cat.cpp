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
int cat::getLives() const{
    return  lives;
}
//implementing the setter.
std::string cat::getName() const{
    return  name;
}

