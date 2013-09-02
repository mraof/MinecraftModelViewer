#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED
#include <vector>
#include <map>
#include <string>

class Box
{
public:
    float x, y, z, width, height, length;
    Box(float x, float y, float z, float width, float height, float length);
    void render();
};
class ModelRenderer
{
public:
    float textureWidth;
    float textureHeight;
    int textureOffsetX;
    int textureOffsetY;
    float rotationPointX;
    float rotationPointY;
    float rotationPointZ;
    float rotateAngleX;
    float rotateAngleY;
    float rotateAngleZ;

    float offsetX;
    float offsetY;
    float offsetZ;
    std::vector<Box*> boxes;

    ModelRenderer();
    void addBox(float par1, float par2, float par3, int par4, int par5, int par6);
    void setRotationPoint(float par1, float par2, float par3);
    void render();
};
class Model
{
public:
    std::map<std::string, ModelRenderer*> parts;
    std::string modelClass;
    Model(const std::string& modelClass);
    void addPart(std::string& name);
    ModelRenderer getPart(std::string& name);
    void render();
};


#endif // RENDER_H_INCLUDED
