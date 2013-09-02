#include "parser.h"
#include <sstream>

void createModelFromSource(Model* model, std::string &src)
{
    std::istringstream srcStream;
    srcStream.str(src);
    std::string line;
    while(std::getline(srcStream, line))
    {
        ;
    }

}
void createSourceFromModel(Model* model, std::string &src)
{
    std::ostringstream srcStream;
    srcStream << "import net.minecraft.client.model.ModelBase;\nimport net.minecraft.client.model.ModelRenderer;"
        "\npublic class " << model->modelClass << " extends ModelBase\n{";
    for(auto& part : model->parts)
        srcStream << "\n    ModelRenderer " << part.first << ";";
    srcStream << "\n    " << model->modelClass << "()" << "\n   {";
    for(auto& part : model->parts)
    {
        srcStream << "\n        " << part.first << " = new ModelRenderer(this, " << part.second->textureOffsetX << ", " << part.second->textureOffsetY << ");";
        for(int i = 0; i < part.second->boxes.size(); i++)
        {
            Box* box = part.second->boxes[i];
            srcStream << "\n        " << part.first << ".addBox(" << box->x << ", " << box->y << ", " << box->z << ", " << box->width << ", " << box->height << ", " << box->length << ");";
        }
        srcStream << "\n        " << part.first << ".setRotationPoint(" << part.second->rotationPointX << ", " << part.second->rotationPointY << ", " << part.second->rotationPointZ << ");";
    }
    srcStream << "\n    }" << "\n}";
    src = srcStream.str();
}
