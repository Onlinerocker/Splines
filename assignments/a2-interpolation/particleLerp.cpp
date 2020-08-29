#include "AFramework.h"
#include "AGLObjects.h"

class ParticleLerp : public AFramework
{
public:
    ParticleLerp() : AFramework(AFramework::Perspective)
    {
    }

    void draw()
    {
        ASetMaterial(AVector3(1,0,0));

        AVector3 start = AVector3(100,0,0);
        AVector3 end = AVector3(0,0,100);
        ADrawSphere(start, 10);
        ADrawSphere(end, 10);

        double duration = 8;
        double t = elapsedTime()/duration;
        AVector3 pos = (1-t) * start + t * end;

        ASetMaterial(AVector3(1,1,0));
        ADrawSphere(pos, 10);
    }
};

int main(int argc, char** argv)
{
    ParticleLerp viewer;
    viewer.init(argc, argv);
    viewer.run();
    return 0;
}

