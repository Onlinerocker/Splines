#include "AnimationToolkit.h"
#include "AFramework.h"

class AFireworksViewer : public AFramework
{
public:
   AFireworksViewer() : AFramework(AFramework::Orthographic) 
   {
   }

   virtual ~AFireworksViewer()
   {
   }
    
   void keyPress(unsigned char key, int specialKey, int x, int y)
   {
      if (key == ' ')
      {
         // todo: launch firework
      }
   }

   void setup()
   {
   }

   void update()
   {
   }

   void draw()
   {
   }
};


int main(int argc, char** argv)
{
   AFireworksViewer viewer;
	viewer.init(argc, argv);
	viewer.run();
	return 0;
}

