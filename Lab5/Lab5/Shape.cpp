#include "Shape.h"
#include <sstream>
#include <iostream>
    Circle::Circle(double _x, double _y, double _r):x(_x), y(_y), r(_r){
        std::cout << "Cirlcle made.";        
    }

     std::string Circle::to_string() const {
        std::stringstream sstr;
        sstr << "Circle centred at (" << x << "," << y << ") with radius " << r;
        std::string str = sstr.str(); // "Hello world. 42";
        return str;
     }

    void Circle::centre_at(double _x, double _y){
     x = _x;
     y = _y;
    }

    Rectangle::Rectangle(double _x0, double _y0, double _x1, double _y1):x0(_x0), y0(_y0), x1(_x1), y1(_y1){

    }

    void Rectangle::centre_at(double x, double y){
        // double old_centre_x = 
        // double old_centre_y = 

        double difference_x = x1 - (x0 + x1) / 2; 
        double difference_y = y1 - (y0 + y1) / 2;

        x0 = x - difference_x;
        y0 = y - difference_y;
        x1 = x + difference_x;
        y1 = y + difference_y;       
    }

    std::string Rectangle::to_string() const{
        std::stringstream sstr;
        sstr << "Rectangle at [(" << x0 << ", " << y0 << "), ("<< x1<<", " << y1 <<
         ")] with width "<< x1-x0 << ", height " << y0 - y1;
        std::string str = sstr.str(); // "Hello world. 42";
        return str;
    }

    Triangle::Triangle(double x0, double y0, double x1, double y1, double x2, double y2):x0(x0), y0(y0), x1(x1), y1(y1), x2(x2),y2(y2){

    }