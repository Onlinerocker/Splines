
# Readme

## Question 0: Reading code

* The spline passes a normalized time u in the range [0,1] to the interpolator. What formula is used to convert the general time (for example, the application time since startup) to a normalized time?

    Normalized time = (app_time % anim_total_time) / anim_total_time

* Suppose a spline holds 3 keys. One at time 0, one at time 3, and one at time 5. If we call getValue(7, true), what segment will be used to interpolate? What formula is used to compute the normalized time u. What will the normalized time be?

    The first segment will be used.
    Normalized Time = (7 % 5) / 5 = 2 / 5 = 0.4

* Suppose a spline holds 3 keys. One at time 0, one at time 3, and one at time 5. If we call getValue(7, false), what segment will be used to interpolate? What formula is used to compute the normalized time u? What will the normalized time be?

    Since we aren't looping, the final segment will be used and normalized time = 1.

* Suppose a spline holds 3 keys. One at time 0, one at time 3, and one at time 5. If we call getValue(-2, false), what segment will be used to interpolate? What formula is used to compute the normalized time u? What will the normalized time be?

    Since we aren't looping, the first segment will be used and normalized time = 0.

* Suppose a spline holds 3 keys. One at time 0, one at time 3, and one at time 5. What formula is used to compute the normalized duration? If we call getNormalizedDuration(7) what value is returned? 

    0.4

## What was the hardest part of this assignment?

Calculating the control points for hermite

## What was the easiest part of this assignment?

Animating the point

## Did you complete any extra credits?  If so, how do I run them and where is the video?

