#include "graphics.h"
#include "globals.h"
#include "os.h"
#include "render.h"
#include "parser.h"
#include <string>
#include <iostream>

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
int main()
{
    running = true;
    OS::init();
    Graphics::init();
    resizeGL(640, 480);
    std::string modelClass = "ModelNull";
    Model model(modelClass);
    //temporary, only for testing
    std::string inputSrc = "\
public class ModelImp extends ModelBase\n\
{\n\
	//fields\n\
	ModelRenderer Head;\n\
	ModelRenderer Body;\n\
	ModelRenderer Armright;\n\
	ModelRenderer Armleft;\n\
	ModelRenderer Legleft;\n\
	ModelRenderer Legright;\n\
\n\
	public ModelImp()\n\
	{\n\
		textureWidth = 32;\n\
		textureHeight = 32;\n\
\n\
		Head = new ModelRenderer(this, 0, 0);\n\
		Head.addBox(-3F, -3F, -5F, 5, 5, 5);\n\
		Head.setRotationPoint(0F, 15F, 0F);\n\
		Head.mirror = true;\n\
		setRotation(Head, 0F, 0F, 0F); \n\
		Body = new ModelRenderer(this, 0, 10);\n\
		Body.addBox(-3F, -4F, -2F, 5, 6, 4);\n\
		Body.setRotationPoint(0F, 19F, 0F);\n\
		Body.mirror = true;\n\
		setRotation(Body, 0F, 0F, 0F);\n\
		Armright = new ModelRenderer(this, 0, 20);\n\
		Armright.addBox(-1F, 0F, -1F, 1, 5, 1);\n\
		Armright.setRotationPoint(-3F, 16F, 0F);\n\
		Armright.mirror = true;\n\
		setRotation(Armright, 0F, 0.0371786F, 0.0371786F); \n\
		Armleft = new ModelRenderer(this, 0, 20);\n\
		Armleft.addBox(0F, 0F, -1F, 1, 5, 1);\n\
		Armleft.setRotationPoint(2F, 16F, 0F);\n\
		Armleft.mirror = true;\n\
		setRotation(Armleft, 0F, 0F, 0F);\n\
		Legleft = new ModelRenderer(this, 4, 20);\n\
		Legleft.addBox(-1F, 0F, 0F, 1, 3, 1);\n\
		Legleft.setRotationPoint(-1F, 21F, 0F);\n\
		Legleft.mirror = true;\n\
		setRotation(Legleft, 0F, 0F, 0F);\n\
		Legright = new ModelRenderer(this, 4, 20);\n\
		Legright.addBox(0F, 0F, 0F, 1, 3, 1);\n\
		Legright.setRotationPoint(0F, 21F, 0F);\n\
		Legright.mirror = true;\n\
		setRotation(Legright, 0F, 0F, 0F);\n\
	}\n\
}\n\
";
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
