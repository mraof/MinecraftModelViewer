#include "render.h"
#include "graphics.h"

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
void Model::addPart(const std::string &name)
{
    parts.push_back(new ModelRenderer());
}
void Model::render()
{
    for(int partNum = 0; partNum < parts.size(); partNum++)
        parts[partNum]->render();
}
