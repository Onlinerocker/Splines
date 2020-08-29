#include <iostream>
#include <cmath>
#include "AMatrix3.h"
#include "AQuaternion.h"

int main()
{
    AQuaternion q;
    AMatrix3 m;

    m.fromEulerAnglesXYZ(AVector3(0,0,M_PI/4));
    q.fromMatrix(m);
    std::cout << "45 Z " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 Z" << std::endl << m << std::endl;

    m.fromEulerAnglesXYZ(AVector3(0,M_PI/4,0));
    q.fromMatrix(m);
    std::cout << "45 Y " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 Y " << std::endl << m << std::endl;

    m.fromEulerAnglesXYZ(AVector3(M_PI/4,0,0));
    q.fromMatrix(m);
    std::cout << "45 X " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 X" << std::endl << m << std::endl;

    return 0;
}