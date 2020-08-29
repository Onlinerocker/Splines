#include <iostream>
#include <cmath>
#include "AQuaternion.h"

int main()
{
    AQuaternion q;
    AVector3 v; double angle;

    q.fromAxisAngle(AVector3(0,0,1), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 Z " << q << " " << v << " " << angle * ARad2Deg << std::endl;

    q.fromAxisAngle(AVector3(0,1,0), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 Y " << q << " " << v << " " << angle * ARad2Deg << std::endl;

    q.fromAxisAngle(AVector3(1,0,0), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 X " << q << " " << v << " " << angle * ARad2Deg << std::endl;

    return 0;
}