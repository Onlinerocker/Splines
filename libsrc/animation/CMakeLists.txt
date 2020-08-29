set(SRC
    AVector3.cpp
    AMatrix3.cpp
    AMatrix3-basecode.cpp
    AQuaternion.cpp
    AQuaternion-basecode.cpp
    )

set(SRC_SPLINE
    ASpline.cpp
    AQuatSpline.cpp
    AInterpolator.cpp
    AInterpolator-basecode.cpp
    )

set(SRC_FK
    ABVHReader.cpp
    ATransform.cpp
    ATransform-basecode.cpp
    ASkeleton.cpp
    AJoint.cpp
    AJoint-basecode.cpp
    APose.cpp
    AMotion.cpp
    )

set(SRC_IK
    AIKController.cpp
    AIKController-basecode.cpp
    )

set(SRC_BLEND
    AMotionBlender-basecode.cpp
    )

add_library(animationbasic STATIC ${SRC})
add_library(animationspline STATIC ${SRC_SPLINE})
add_library(animationfk STATIC ${SRC_FK})
add_library(animationik STATIC ${SRC_IK})
add_library(animationblend STATIC ${SRC_BLEND})
