#include "graphics.h"
#include "globals.h"
#include "os.h"
#include "render.h"

float rotQuad;
float translateX;
float translateY;
float translateZ;


void resizeGL(unsigned int width, unsigned int height)
{
    /* prevent divide-by-zero */
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(95.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void renderGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(translateX, translateY, translateZ);
//    Graphics::renderBox(-3, 0, 4, 10, 1, 1);
//    Graphics::renderBox(-3, -3, 0, 10, 1, 1);
//    rotQuad += 0.5f;
    /* swap the buffers if we have doublebuffered */
//    if (doubleBuffered)
//    {
//        glXSwapBuffers(display, window);
//    }
}
int main()
{
    OS::init();
    Graphics::init();
    resizeGL(640, 480);
    Model model;
    model.addPart("Head");
    model.parts[0]->setRotationPoint(1.0f, 0.5f, 0.25f);
    model.parts[0]->addBox(-3, -3, 0, 10, 1, 1);
    model.parts[0]->addBox(-3, 0, 4, 10, 1, 1);
    while(1)
    {
        renderGL();
        model.render();
        OS::refresh();
        SLEEP(20);
    }
    OS::deinit();
}
