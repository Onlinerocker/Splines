#include "AnimationToolkit.h"

int main(int argc, char** argv)
{
   ASkeleton skeleton;
   AMotion motion;

   ABVHReader reader;
   reader.load("../motions/Beta/idle.bvh", skeleton, motion);

   int numJoints = skeleton.getNumJoints(); 
   std::cout << "The number of joints is " << numJoints << std::endl;

   // todo: loop through and print all joint names
   for (int i = 0; i < numJoints; i++)
   {
      // todo
      std::string jointName = skeleton.getByID(i)->getName();
      std::cout << i << " " << jointName << std::endl;
   }

   // todo get root of the skeleton
   AJoint* root = skeleton.getRoot();
   std::string rootName = root->getName();
   int rootID = root->getID();
   int numchildren = root->getNumChildren();

   std::cout << "The root joint name is: " << rootName << std::endl;
   std::cout << "The root joint ID is: " << rootID << std::endl;
   std::cout << "The root joint's number of children is: " << numchildren << std::endl;
   //todo print the names of the children of the root
   for (int i = 0; i < numchildren; i++)
   {
      std::string childName = root->getChildAt(i)->getName();
      std::cout << childName << std::endl; 
   } 

   // Get the joint for the hand by looking up by name
   AJoint* hand = skeleton.getByName("Beta:LeftHand");
   AVector3 offset = hand->getLocalTranslation(); // todo get the local offset from the hand to its parent 
   std::cout << "The offset between the left hand and its parent is " << offset << std::endl;

   // todo: get the hand's parent joint's name
   std::string handParentName = hand->getParent()->getName();
   std::cout << "The parent of the hand is " << handParentName << std::endl;
}