#include <iostream>
#include "Shape.h"

int main(int argc , char *argv[]) {
//    Shape *x = new Circle(0,0,1); // x, y, r
    
//     std::cout << x->to_string() << std::endl;
//     x->centre_at(2, 3);
    
//     std::cout << x->to_string() << std::endl;

//     Shape *y = new Rectangle(0,1,1,0);

//     std::cout << y->to_string() << std::endl;
//     y->centre_at(-2.5, 2.5);
    
//     std::cout << y->to_string() << std::endl;
    
    Shape **xs = new Shape*[10];

    xs[0] = new Circle(0,0,1);
    xs[1] = new Rectangle(0,1,1,0);
    xs[2] = new Triangle(0,0,1,1,0,1);
    
    //just looped over 3 elements to make things quicker as it is repeated code.
    for(int i = 0; i < 3; i++){
        std::cout << xs[i]->to_string() << std::endl;
    }
    for(int i = 0; i < 3; i++){
        delete xs[i];
    }
    delete xs;
    return 0;
}