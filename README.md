# FlightSimulator
I am using the camera as the plane.

Every plane has pitch, yaw and roll and i tried to achieve this by using euler angle rotation matrices and failed miserably and after long hours of googling i found that they use Quaternions because u can rotate along a vector in any direction unlike euler rotation where u are only constrained to rotate along the 3 axis.

Heres where i learnt about Quaternions -> http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

so i had to create plane axis forward, up and left, forward pointing the front of the plane, left pointing left of plane so that the forward vector can rotate along left axis as pitch of the plane using quaternions. 

![Plane Axis](https://uploads.gamedev.net/monthly_2019_11/1375953994_aircraftaxis.PNG.fb0b034c91bd5817fd94220dfea17561.PNG)


Here's how i pitch the plane :

![Pitch](https://uploads.gamedev.net/monthly_2019_11/pitchRotation.PNG.55a198a559b33b38df1e95e6bdfeea86.PNG)

and same applies for rolling and yaw, this is how every flight simulator handles orientation.

And for torque i had to multiply with a variable that increases then becomes constant, that "pitchUp" variable will increase at the beginning then clamps to constant value.

in order for the plane to move forward i just incremented the forward vector and scaled it with a "forwardSpeed" variable.

Heres the pseudo  code for move function->
```
if(W key){
    thrust += deltaTime;
    gravity -= deltaTime;
    clamp thrust and gravity
    forward += deltaTime;
    clamp forward variable;
} else {
    gravity += deltaTime;
    thrust -= deltaTime;
    clamp thrust and gravity
    forward += 0.2 * acceleration * GLIDESPEED * deltaTime;
    forward -= deltaTime;
    clamp forward variable;
}
Acceleration += gravity;
Acceleration -= thrust;
Ypos -= Acceleration;
Also clamp acceleration to zero
```
If the roll or pitch angle is too big or if the plane is upside down and collides with the ground then the plane crashes so i just reset the plane.

I also added a spot light in front of the plane so u can see how close u are with the ground.

use W for thrust and arrow keys for rolling and pitching.

ScreenShots ->

![](https://github.com/TheGameDevDude/FlightSimulator/blob/master/ScreenShots/takeoff.png)

youtube link -> https://www.youtube.com/watch?v=C9zNYBBjB90&feature=youtu.be


