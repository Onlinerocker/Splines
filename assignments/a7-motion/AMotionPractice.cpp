#include "AnimationToolkit.h"

int main(int argc, char** argv)
{
   ASkeleton skeleton;
   AMotion motion;

   ABVHReader reader;
   reader.load("../motions/Beta/walking.bvh", skeleton, motion);

   // How many frames (aka keys)?
   int numFrames = motion.getNumKeys();
   std::cout << "The number of frames is " << numFrames << std::endl;

   // What is the framerate?
   double fps = motion.getFramerate();
   std::cout << "The frame rate is " << fps << std::endl;

   // What is the duration?
   double duration = motion.getDuration();
   std::cout << "The duration of the animation is " << duration << std::endl;

   // What is the root position on frame 5 (aka Key #5)?
   // Hint: Get a pose from the motion
   APose frame5 = motion.getKey(5);
   AVector3 rootPos = frame5.rootPos;
   std::cout << "The root position on frame 5 is: " << rootPos << std::endl;

   // What is the local joint rotation of the left hand on frame 5? 
   // Give your answer in XYZ euler angles
   // Hint: use the skeleton to get the ID for the hand
   AJoint* hand = skeleton.getByName("Beta:LeftHand");
   AVector3 eulerXYZ = frame5.jointRots[hand->getID()].toMatrix().toEulerAnglesXYZ();
   std::cout << "The root position on frame 5 is: " << eulerXYZ << std::endl;

   // What is the speed of the character?
   // Hint: Use the first and last frames to get the distance traveled over the motion clip
   APose frame0 = motion.getKey(0);
   APose frameN = motion.getKey(numFrames - 1);

   double dist = AVector3::Distance(frameN.rootPos, frame0.rootPos);
   double speed =  dist / duration;
   std::cout << "The speed of the motion is (units/s): " << speed << std::endl;
}
