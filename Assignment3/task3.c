//
// Created by Ahmad Aziz on 18/02/2022.
//

//
// Created by Ahmad Aziz on 18/02/2022.
//

// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
//
// (c) Martin Porcheron
//     m.a.w.porcheron@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "constituency.h"

int main() {
//    struct Constituency test;
//    constructConstituency(
//            &test,
//            "Swansea East",
//            (unsigned int[]){1, 2, 3, 4},
//            4);
    const int numConstituencies = 5;
    struct Constituency constituencies[numConstituencies];
    constructConstituency(
            &constituencies[0], "Swansea East",
            (unsigned int[]){1, 2, 3, 4}, 4);
    constructConstituency(
            &constituencies[1], "Swansea West",
            (unsigned int[]){0, 2}, 2);
    constructConstituency(
            &constituencies[2], "Gower",
            (unsigned int[]){0, 1, 3}, 3);
    constructConstituency(
            &constituencies[3], "Neath",
            (unsigned int[]){0, 2, 4}, 3);
    constructConstituency(
            &constituencies[4], "Aberavon",
            (unsigned int[]){0 , 3}, 2);

    struct Constituency *copy = copyConstituencies(constituencies,
                                                   numConstituencies);
    int i = 0;
    for (i = 0; i < numConstituencies; i++)
    {
        destructConstituency(&constituencies[i]);
    }
    
    int j;
    for (j = 0; j < 5; j++)
    {
        printConstituency(&copy[j]);
        printf("\n");
    }


    struct Constituency *temp;
    struct Constituency *minCon = NULL;
    struct Constituency *maxCon= NULL;



    for(int i = 0; i < numConstituencies;i++){
        temp = &constituencies[i];
        printConstituency(temp);
        if(minCon== NULL || temp->numNeighbours < minCon->numNeighbours) {
            minCon = &constituencies[i];
        }
        if(maxCon == NULL ||  temp->numNeighbours > maxCon->numNeighbours) {
            maxCon = &constituencies[i];
        }
    }
    printf("\n");

    printf("%s has the most bordering constituencies: \n",maxCon->name);
    for (int i = 0; i < maxCon->numNeighbours;i++){
        temp = &constituencies[maxCon->neighbours[i]];
        printf("   %s \n", temp->name);
    }

    printf("\n");


    printf("%s has the fewest bordering constituencies: \n",minCon->name);
    for (int i = 0; i < minCon->numNeighbours;i++){
        temp = &constituencies[minCon->neighbours[i]];
        printf("   %s \n", temp->name);
    }
    printf("\n");

    //printConstituency(&test);

    for(int i; i < numConstituencies;i++){
        destructConstituency(&constituencies[i]);
    }
    // destructConstituency(&test);

    return 0;
}