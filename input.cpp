#include "input.h"
#include "globals.h"

extern float rotQuad;
extern float translateX;
extern float translateY;
extern float translateZ;

void keyPress(int key)
{
    if (key == OS_KEY_UP)
        rotQuad += 0.4f;
    if(key == OS_KEY_DOWN)
        rotQuad -= 0.4f;
    if(key == OS_KEY_D)
        translateX += 0.1f;
    if(key == OS_KEY_A)
        translateX -= 0.1f;
    if(key == OS_KEY_W)
        translateY += 0.1f;
    if(key == OS_KEY_S)
        translateY -= 0.1f;
    if(key == OS_KEY_Q)
        translateZ += 0.1f;
    if(key == OS_KEY_E)
        translateZ -= 0.1f;
}
