//
// Created by Ahmad Aziz on 20/02/2022.
//

#include <iostream>
#include "cat.h"
int main(int argc, char* argv[]) {

    const int numberOfCats = (argc)/2;
    bool odd = false;
    if((argc+1)%2==1) {
        odd = true;
    }
    std::cout << "allocating clowder size of: "<<numberOfCats<<"\n";
    cat* cats = new cat[numberOfCats];

    for(int i = 0; i<numberOfCats;i++){
        int name = (2 * i) + 1;
        int lives = (2 * i) + 2;
        if (odd == true && i == (numberOfCats-1)){
            cat m(argv[name] , 9);
            cats[i] = std::move(m);
        }
        else
        {
            cat m(argv[name] , atoi(argv[lives]));
            cats[i] = std::move(m);
        }
    }
    for(int i = 0;i<numberOfCats;i++){
        std::cout << cats[i].getName() << " has "
                  << cats[i].getLives() << " lives." << std::endl;
    }
    delete [] cats;
    return 0;
}