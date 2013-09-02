#include "render.h"
#include "graphics.h"
#include <iostream>

extern int rotQuad;

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
    glRotatef(rotQuad, rotationPointX, rotationPointY, rotationPointZ);
    for(int boxNum = 0; boxNum < boxes.size(); boxNum++)
        boxes[boxNum]->render();
}
Model::Model(const std::string& modelClass)
{
    this->modelClass = modelClass;
}
void Model::addPart(std::string &name)
{
    parts[name] = new ModelRenderer();

}
void Model::render()
{
    for(auto& part : parts)
    {
        part.second->render();
    }
}
ModelRenderer Model::getPart(std::string &name)
{

}
