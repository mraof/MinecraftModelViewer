#include "globals.h"
#include "graphics.h"
#include "stb_image.h"
#include <iostream>
#include <ctime>
#include <cstdio>

extern int rotQuad;

GLuint sprites[20];
int Graphics::offsetX;
int Graphics::offsetY;
void Graphics::init()
{
    // load resources, initialize the OpenGL states,

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    /* we use resizeGL once to set up our initial perspective */
//    resizeGL(WINDOW_WIDTH, WINDOW_HEIGHT);
    /* Reset the rotation angle of our object */
    rotQuad = 0;
    glFlush();

//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    glOrtho (0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
//    glMatrixMode (GL_MODELVIEW);
//    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glLoadIdentity();
//    //Displacement trick for exact pixelization
//    glTranslatef(0.375, 0.375, 0);

//    sprites[0] = loadImage("resources/Untitled.png");
//    sprites[1] = loadImage("resources/Untitled2.png");
//    sprites[2] = loadImage("resources/Untitled3.png");
//    sprites[3] = loadImage("resources/Untitled4.png");
//    sprites[4] = loadImage("resources/Untitled5.png");
//    sprites[5] = loadImage("resources/Untitled6.png");
//    sprites[6] = loadImage("resources/artifact0.png");
//    sprites[7] = loadImage("resources/a6Uw4Yc.png");
//    sprites[8] = loadImage("resources/Loading.png");
//    sprites[9] = loadImage("resources/Tile0.png");
//    sprites[10] = loadImage("resources/Tile1.png");

}

void Graphics::renderBox(float x, float y, float z, float width, float height, float length)
{
    glBegin(GL_QUADS);
        /* top of cube */
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x + width, y + height, z);
        glVertex3f(x, y + height, z);
        glVertex3f(x, y + height, z + length);
        glVertex3f(x + width, y + height, z + length);
        /* bottom of cube */
        glColor3f(x + width, 0.5f, 0.0f);
        glVertex3f(x + width, y, z + length);
        glVertex3f(x, y, z + length);
        glVertex3f(x, y, z);
        glVertex3f(x + width, y, z);
        /* front of cube */
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x + width, y + height, z + length);
        glVertex3f(x, y + height, z + length);
        glVertex3f(x, y, z + length);
        glVertex3f(x + width, y, z + length);
        /* back of cube */
        glColor3f(x + width, 1.0f, 0.0f);
        glVertex3f(x, y + height, z);
        glVertex3f(x + width, y + height, z);
        glVertex3f(x + width, y, z);
        glVertex3f(x, y, z);
        /* right side of cube */
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(x + width, y + height, z);
        glVertex3f(x + width, y + height, z + length);
        glVertex3f(x + width, y, z + length);
        glVertex3f(x + width, y, z);
        /* left side of cube */
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(x, y + height, z + length);
        glVertex3f(x, y + height, z);
        glVertex3f(x, y, z);
        glVertex3f(x, y, z + length);
    glEnd();
}
void Graphics::drawSprite(int x, int y, int width, int height, GLuint texture, bool withOffset)
{
    if(withOffset)
    {
        x = x - offsetX;
        y = y - offsetY;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2d(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glTexCoord2d(1.0f, 1.0f);
    glVertex2f(x + width, y + height);
    glTexCoord2d(1.0f, 0.0f);
    glVertex2f(x + width, y);
    glEnd();
}
void Graphics::drawBackground(int width, int height, GLuint texture, float offsetX, float offsetY)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2d(offsetX, offsetY);
    glVertex2f(0, 0);
    glTexCoord2d(offsetX, WINDOW_HEIGHT/height + offsetY);
    glVertex2f(0, WINDOW_HEIGHT);
    glTexCoord2d(WINDOW_WIDTH/width + offsetX, WINDOW_HEIGHT/height + offsetY);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glTexCoord2d(WINDOW_WIDTH/width + offsetX, offsetY);
    glVertex2f(WINDOW_WIDTH, 0);
    glEnd();
}
int Graphics::loadImage(const std::string& filename)
{
    GLuint texture_handle;
//    sf::Image img_data;
//    if (!img_data.loadFromFile(filename));
    int width, height, channels;
    unsigned char* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        width, height,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, ptr
    );
    return texture_handle;
}
