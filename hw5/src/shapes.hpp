#pragma once
#include <iostream>

/**
 * @brief Интерфейс фигуры
 */
class IShape{
public:
    virtual void Draw() = 0;
    virtual bool pointInside(int x_, int y_) = 0;
    IShape(int x, int y) : x(x), y(y){};
    virtual ~IShape() = default;
protected:
    int x,y;
};

/**
 * @brief Квадрат
 */
class Square : public IShape {
public:
    Square(int x, int y, int side) : IShape(x,y), side(side){};
    ~Square(){};
    void Draw(){std::cout << "Draw Square at ("<< x <<","<< y << ") size ("<< side << "," << side << ")\n"; };
    bool pointInside(int x_, int y_){
        return ((x_ == std::clamp(x_, x, x+side)) && (y_ == std::clamp(y_, y, y+side)))?true:false; 
    };
protected:
    int side;
};

/**
 * @brief Круг
 */
class Circle : public IShape {
public:
    Circle(int x, int y, int radius): IShape(x,y), radius(radius){};
    ~Circle(){};
    bool pointInside(int x_, int y_){
        return (std::abs(x-x_) < radius && std::abs(y-y_) < radius);
    }
    void Draw(){std::cout << "Draw Circle at ("<< x <<","<< y << ") radius "<< radius << "\n"; };
protected:
    int radius;
};
