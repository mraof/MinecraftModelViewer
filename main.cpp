#include "graphics.h"
#include "globals.h"
#include "os.h"
#include "render.h"
#include "parser.h"
#include <string>
#include <iostream>
#include <fstream>

<<<<<<< HEAD
float modelSize;
=======
float modelSize;
>>>>>>> c40284f... I probably fixed something
float rotY;
float rotZ;
float translateX;
float translateY;
float translateZ;
bool running;


void resizeGL(unsigned int width, unsigned int height)
{
    /* prevent divide-by-zero */
    glRotatef(rotY, 0, 1.0, 0);
    glRotatef(rotZ, 0, 0, 1.0);
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
//    rotZ += 0.5f;
    /* swap the buffers if we have doublebuffered */
//    if (doubleBuffered)
//    {
//        glXSwapBuffers(display, window);
//    }
}
int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        std::cout << "please provide a file";
        exit(1);
    }
    std::string filename(argv[1]);
    running = true;
    OS::init();
    Graphics::init();
    resizeGL(640, 480);
    modelSize = 48;
    std::string modelClass = "ModelNull";
    Model model(modelClass);
<<<<<<< HEAD
    std::ifstream sourceFile(filename);
    if(!sourceFile.is_open())
    {
        std::cout << "file " << filename << "could not be opened\n";
        OS::deinit();
        exit(1);
    }
    else if(sourceFile.bad())
    {
        std::cout << "file " << filename << "is bad\n";
        OS::deinit();
        exit(1);
    }
=======
    std::ifstream sourceFile("models/ModelBasilisk.java");
>>>>>>> c40284f... I probably fixed something
    sourceFile.seekg(0, std::ios::end);
    size_t fileSize = sourceFile.tellg();
    std::string inputSrc(fileSize, ' ');
    sourceFile.seekg(0);
    sourceFile.read(&inputSrc[0], fileSize);
    createModelFromSource(&model, inputSrc);
    std::string src = "";
    createSourceFromModel(&model, src);
    std::cout << src;
    while(running)
    {
        renderGL();
        model.render();

        OS::refresh();
        SLEEP(20);
    }
    OS::deinit();
}
