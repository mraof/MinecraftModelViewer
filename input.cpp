#include "input.h"
#include "globals.h"
#include <iostream>

extern float rotY;
extern float rotZ;
extern float translateX;
extern float translateY;
extern float translateZ;

void keyPress(int key)
{
    if (key == OS_KEY_UP)
        rotZ += 0.1f;
    if(key == OS_KEY_DOWN)
        rotZ -= 0.1f;
    if(key == OS_KEY_LEFT)
        rotY += 0.1f;
    if(key == OS_KEY_RIGHT)
        rotY -= 0.1f;
    if(key == OS_KEY_D)
        translateX += 0.1f;
    if(key == OS_KEY_A)
        translateX -= 0.1f;
    if(key == OS_KEY_W)
        translateY += 0.1f;
    if(key == OS_KEY_S)
        translateY -= 0.1f;
    if(key == OS_KEY_Q)
        translateZ += 0.5f;
    if(key == OS_KEY_E)
        translateZ -= 0.5f;
    std::cout << rotY << ", " << rotZ << "\n";
}
