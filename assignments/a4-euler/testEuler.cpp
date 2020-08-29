#include <iostream>
#include "AMatrix3.h"

int main()
{
    AMatrix3 rotZ;
    rotZ.fromEulerAnglesZYX(AVector3(0,-90.0,0)*ADeg2Rad);

    // should print out a matrix corresponding to a 45 degree 
    // rotation around Z
    std::cout << rotZ << std::endl;
    std::cout << rotZ[2][0] << std::endl;

    rotZ.toEulerAnglesZYX();

    AMatrix3 rotY;
    rotY.fromEulerAnglesXYZ(AVector3(0,45,0)*ADeg2Rad);
    std::cout << rotY << std::endl;

    AMatrix3 rotX;
    rotX.fromEulerAnglesXYZ(AVector3(45,0,0)*ADeg2Rad);
    std::cout << rotX << std::endl;

/* Uncomment to test every euler angle order
    const char* rooNames[6] = { "XYZ", "XZY", "YXZ", "YZX", "ZXY", "ZYX" };
    for (int i = 0; i < 6; i++)
    {
        AMatrix3 rot;
        rot.fromEulerAngles((AMatrix3::RotOrder)i, AVector3(30,0,0)*ADeg2Rad);
        std::cout << "Test " << rooNames[i] << std::endl;
        std::cout << rot << std::endl;
    }
*/
    // Put more test cases here to check your work!
}