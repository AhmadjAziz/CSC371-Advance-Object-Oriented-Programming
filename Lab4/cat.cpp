//
// Created by Ahmad Aziz on 19/02/2022.
//
#include <iostream>
#include "cat.h"

cat::cat(std::string name) {
    this->name = name;
    this->lives = 9;
    //std::cout<< "Constructor called with name... \n" << this->name << " has "<< this->lives << "lives.\n";
}

cat::cat(std::string name, unsigned int lives) {
    this->name = name;
    this-> lives = lives;
    //std::cout<< "Constructor called with name and lives... \n" << this->name << " has "<< this->lives << "lives.\n";
}

cat::~cat() {
    std::cout<<"destructor called...\n";
}

int cat::getLives() const{
    return  lives;
}
std::string cat::getName() const{
    return  name;
}

