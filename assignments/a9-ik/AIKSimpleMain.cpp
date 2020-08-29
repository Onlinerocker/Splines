#include "AIKSimple.h"

int main(int argc, char** argv)
{
	AIKSimple viewer;
	viewer.init(argc, argv);
    viewer.setupCharacter();
	viewer.run();
	return 0;
}

