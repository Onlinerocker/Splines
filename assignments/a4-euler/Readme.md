
# Readme

## Question 0: Euler angles

Q1: What is an orthogonal matrix? Show that this matrix is orthogonal.

    An orthogonal matrix is a square matrix where all the columns have unit length and are
    perpendicular to each other.
    
    To show the first column is 1 we need to find its magnitude. Then show it's equal to 1
    To show the first column is perpendiculator to each of the others, we take
    the dot product and show it's equal to zero.

Q2: What matrix element would be the easiest to get an angle back?

    The middle element is the easiest to be back.
    In the ZYX orientation, Y would be the easiest.

Q3: Recall that tan = sin/cos. How could we use this to get the other angles back?

    In the ZYX orientation...

    We can use tan to obtain Theta_x by computing 
    Theta_x = atan2(cos(theta_y) * sin(theta_x), cos(theta_x) * cos(theta_y))

    We can use tan to obtain Theta_z by computing 
    Theta_z = atan2(cos(theta_y) * sin(theta_z), cos(theta_x) * cos(theta_z) + sin(theta_x) * sin(theta_y) * sin(theta_z))   

Q4: What happens when the rotation around the Y axis is 90 degrees?

    In the ZYX orientation we encounter gimbol lock.
    X and Z rotate along the same axis.

Q5: If the Y rotation is 90 degrees, how can we get the X and Z values back?

Q6: Show that when the rotation around Y is 90 degrees, the values for X and Z are not unique.

    See Q6 image.

Q7: Consider the following matrix. What does each column represent?

|0   -cx⋅sz + cz⋅sx  cx⋅cz + sx⋅sz|
|0   cx⋅cz + sx⋅sz   cx⋅sz - cz⋅sx|
|-1        0               0      |

Q8: Consider the following matrix. Suppose we want to use this matrix to convert a character's local axes to world coordinates. How do we do this?

|0   -cx⋅sz + cz⋅sx  cx⋅cz + sx⋅sz|
|0   cx⋅cz + sx⋅sz   cx⋅sz - cz⋅sx|
|-1        0               0      |

Q9: Suppose we tried to extract euler angles from a matrix that was not orthogonal. What are some problems we would encounter?

Q10: What is the inverse of the rotation matrix corresponding to XYZ euler angles, in terms of Rx, Ry, and Rz matrices? 


## What was the hardest part of this assignment?
    The readme questions

## What was the easiest part of this assignment?
    Non-middle element = +-90 cases

## Did you complete any extra credits?  If so, how do I run them and where is the video?
    No
