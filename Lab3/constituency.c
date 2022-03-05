#include "constituency.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void constructConstituency(struct Constituency * const obj, char const *name,
                           unsigned int* const neighbours, unsigned int const numNeighbours){
    //always clear data.
    obj->name = NULL;
    obj->neighbours = NULL;
    obj->numNeighbours = 0;

    obj->name = (char*) malloc(strlen(name) * sizeof(char));
    obj->neighbours = (unsigned int*) malloc(sizeof(unsigned int) * numNeighbours);
    obj->numNeighbours = numNeighbours;
    //copy the value of what name is pointing to. (dereference pointer)
    memcpy(obj->name, name, strlen(name) * sizeof(char));
    //copy the value of what neighbours is pointing to. (dereference pointer)
    if (numNeighbours > 0) {
        memcpy(obj->neighbours, neighbours, numNeighbours * sizeof(unsigned int));
    }
}

void printConstituency(struct Constituency * const obj){

    printf("%s | %u neighbours | [", obj->name, obj->numNeighbours);
    int i;
    for (i = 0; i < obj->numNeighbours;i++){
        printf(" %u ", obj->neighbours[i]);
    }
    printf("]\n");

}

void destructConstituency(struct Constituency * const obj){
    if(obj->name != NULL){
        free(obj->name);
    }
    if(obj->neighbours != NULL){
        free(obj->neighbours);
    }
    obj->numNeighbours = 0;
}
struct Constituency *copyConstituencies(struct Constituency constituencies[], const unsigned int constiNum)
{
    struct Constituency *copiedConstituencies= (struct Constituency *)malloc(sizeof(constituencies[0])*constiNum);
    int d;

    for (d = 0; d < constiNum; d++) {
        constructConstituency(&copiedConstituencies[d], (constituencies[d].name), (constituencies[d].neighbours), (constituencies[d].numNeighbours));
    }
    return copiedConstituencies;
}