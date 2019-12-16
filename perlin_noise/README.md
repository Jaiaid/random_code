## 3d Surface Generation using Perlin Noise

This code will generate a 3d surface drawn using opengl and glut library. Code to generate perlin noise is done following this [link](https://flafla2.github.io/2014/08/09/perlinnoise.html).

#### Compile

compiled using g++7.4.0 in ubuntu18.04
```
g++ camera.cpp -o camera.out -lGL -lglut -lGLU
```
#### Usage

A wire mesh of 1600x1600 is drawn on x-y plane with center at origin.
Camera will look towards +x, -y axes from (2,2,1) with z axis as up vector.

To move camera,

 - 1, 2 to yaw camera up and down
 - 3, 4 to pitch right and left
 - 5, 6 to roll counter clockwise and clockwise
 - up, down, left, right arrow to move in right axis and look axis
 - page up or down to move along up axis

