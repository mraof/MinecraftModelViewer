#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>

extern GLuint sprites[];
extern GLuint backgrounds[];
class Graphics
{
public:
    static int offsetX, offsetY;
    static void init();
    static void renderBox(float x, float y, float z, float width, float height, float length);
    static void drawSprite(int x, int y, int width, int height, GLuint texture, bool withOffset = true);
    static void drawBackground(int width, int height, GLuint texture, float offsetX = 0, float offsetY = 0);
    static void drawText(int x, int y, int width, int height, int* textures);
    static int loadImage(const std::string& filename);
//    static void screenshot(const sf::RenderWindow& window);
    static void deinit();
};


#endif // GRAPHICS_H_INCLUDED
