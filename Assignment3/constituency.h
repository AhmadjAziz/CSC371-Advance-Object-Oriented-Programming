//
// Created by Ahmad Aziz on 18/02/2022.
//

#ifndef ASSIGNMENT3_CONSTITUENCY_H
#define ASSIGNMENT3_CONSTITUENCY_H


struct Constituency {
    char *name;
    unsigned int *neighbours;
    unsigned int numNeighbours;
};


void constructConstituency(struct Constituency * const obj, char const *name, unsigned int* const neighbours,
                           unsigned int const numNeighbours);
void destructConstituency(struct Constituency * const obj);
void printConstituency(struct Constituency * const obj);
struct Constituency *copyConstituencies(struct Constituency constituencies[], const unsigned int constNum);
#endif