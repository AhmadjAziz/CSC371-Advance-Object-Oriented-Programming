#include "constituency.h"

void constructConstituency(struct Constituency * const obj, char const *name,
                            unsigned int* const neighbours, unsigned int const numNeighbours){
    //always clear data.
    obj->name = NULL;
    obj->neighbours = NULL;
    obj->numNeighbours = 0;
    
    obj->name = (char*) realloc(obj->name, strlen(name) * sizeof(char)); 

    //copy the value of what name is pointing to. (dereference pointer)
    memcpy(obj->name, name, strlen(name)*sizeof(char));


}

void printConstituency(struct Constituency * const obj){
    int i;
    for (i = 0; i < obj->numNeighbours;i++){
        printf("name: %s", obj->name);
    }

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