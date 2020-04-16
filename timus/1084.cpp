#include <iostream>
#include <iomanip>
#include <cmath>


int main(){
    double side, rope;
    std::cin >> side >> rope;
    std::cout << std::fixed << std::setprecision(3);
    if(rope <= side/2.0){
        std::cout << rope*rope*3.1415926535;
    } else if(rope >= 1.41421356237*side/2.0) {
        std::cout << side*side;
    } else {
        side /= 2.0;
        double y = sqrt(rope*rope-pow(side, 2));
        //std::cout << "y= " << y << "\n";
        double angle = atan(y/side);
        //std::cout << "angle= " << angle << "\n";
        angle = 3.1415926535 / 4 - angle;
        //std::cout << "angle= " << angle << "\n";
        double s = angle/2 * pow(rope, 2);
        double ans = (y*side + 2*s) * 4;
        std::cout << ans;
    }   
}