#include "AFramework.h"

int main(int argc, char** argv)
{
    AFramework viewer(AFramework::Perspective);
    viewer.init(argc, argv);
    viewer.run();
    return 0;
}

