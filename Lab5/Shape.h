#ifndef SHAPE_H
#define SHAPE_H
#include <string>
class Shape{
    public:
        virtual std::string to_string() const = 0;
        virtual void centre_at(double x, double y) = 0;
};

class Circle : public Shape{
    double x,y,r;
    public:
    virtual std::string to_string() const;
    virtual void centre_at(double x, double y);    
    Circle(double x, double y, double r);

};

class Rectangle : public Shape {
    private: 
       double x0,x1,y0,y1;
    
    public:
       virtual std::string to_string() const;
       virtual void centre_at(double x, double y);
       Rectangle(double x0, double y0, double x1, double y1);
};

class Triangle : public Shape {
    private:
    double x0, y0, x1, y1, x2, y2;

    public:
    virtual std::string to_string() const;
    virtual void centre_at(double x, double y);
    Triangle(double x0, double y0, double x1, double y1, double x2, double y2);
};


#endif