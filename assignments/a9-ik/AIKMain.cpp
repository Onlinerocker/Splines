#include "AIKViewer.h"

int main(int argc, char** argv)
{
	AIKViewer viewer;
	viewer.init(argc, argv);
    viewer.setupCharacter();
    //viewer.setSelectedJoint("Beta:LeftHand");
	viewer.run();
	return 0;
}

