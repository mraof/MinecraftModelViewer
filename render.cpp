#include "render.h"
#include "graphics.h"
#include <iostream>
#include <math.h>

extern float rotY;
extern float rotZ;
extern float modelSize;

Box::Box(float x, float y, float z, float width, float height, float length)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->length = length;
}
void Box::render()
{
    Graphics::renderBox(x, y, z, width, height, length);
}
ModelRenderer::ModelRenderer()
{

}
void ModelRenderer::addBox(float x, float y, float z, int width, int height, int length)
{
    boxes.push_back(new Box(x, y, z, width, height, length));
}
void ModelRenderer::setRotationPoint(float par1, float par2, float par3)
{
    rotationPointX = par1;
    rotationPointY = par2;
    rotationPointZ = par3;
}
void ModelRenderer::render()
{
//    glPushMatrix();
//    std::cout << rotationPointX << ", " << rotationPointY << ", " << rotationPointZ << "\n";
    glTranslatef(rotationPointX, rotationPointY, rotationPointZ);
    for(unsigned int boxNum = 0; boxNum < boxes.size(); boxNum++)
        boxes[boxNum]->render();
    glTranslatef(-rotationPointX, -rotationPointY, -rotationPointZ);
//    glPopMatrix();
}
Model::Model(const std::string& modelClass)
{
    this->modelClass = modelClass;
}
void Model::addPart(std::string &name)
{
    std::cout << "adding part " << name << "\n";
    parts[name] = new ModelRenderer();

}
void Model::render()
{
    glPushMatrix();
    glTranslatef(0, 16, 0);
//    std::cout << rotY << ", " << rotZ << "\n";
    glRotatef(rotZ, 0, 0, 1.0);
    glRotatef(rotY, -sin(rotZ), cos(rotZ), 0);
    glTranslatef(0, -16, 0);
    for(auto& part : parts)
    {
        part.second->render();
    }
    glPopMatrix();
}
ModelRenderer* Model::getPart(std::string &name)
{
    return parts[name];
}
