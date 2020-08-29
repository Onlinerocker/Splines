#include "ACrossfadeViewer.h"

int main(int argc, char** argv)
{
   ACrossfadeViewer viewer;
	viewer.init(argc, argv);
   viewer.loadMotion1("../motions/Beta/walking.bvh");
   viewer.loadMotion2("../motions/Beta/jump.bvh");
   viewer.blend();

	viewer.run();
	return 0;
}

