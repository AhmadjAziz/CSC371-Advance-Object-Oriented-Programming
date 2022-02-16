#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <stdlib.h>
#include <stdio.h>
struct Constituency {
    char *name;
    unsigned int *neighbours;
    unsigned int *numNeighbours;
};


void constructConstituency(struct Constituency * const obj, char const *name,
                            unsigned int* const neighbours, unsigned int const numNeighbours);
void destructConstituency(struct Constituency * const obj);
void printConstituency(struct Constituency * const obj);

#endif