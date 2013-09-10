#include "parser.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

size_t endOfNum(std::string &line, size_t start)
{
    size_t varEnd = line.find_first_of("Ff,)", start);
//    if(varEnd == std::string::npos)
//    {
//        varEnd = line.find("f", start);
//        if(varEnd == std::string::npos)
//            varEnd = line.find(",", start);
//    }
    return varEnd;
}
//far from perfect, but it should work usually
void createModelFromSource(Model* model, std::string &src)
{
    std::istringstream srcStream;
    srcStream.str(src);
    std::string line;
    while(std::getline(srcStream, line))
    {
        size_t var = line.find("class");
        size_t varEnd;
        if(var != std::string::npos)
        {
            var = line.find(" ", var) + 1;
            varEnd = line.find(" ", var) - var;
            model->modelClass = line.substr(var, varEnd);
        }
        var = line.find("ModelRenderer ");
        if(var != std::string::npos && line[var - 1] != '(')
        {
            var = line.find(" ", var) + 1;
            varEnd = line.find(";", var) - var;
            std::string partName = line.substr(var, varEnd);
            std::cout << partName << " | " << line << "\n";
            model->addPart(partName);
        }
        for(auto& part : model->parts)
        {
            if(line.find(part.first))
            {
                var = line.find("new ModelRenderer(");
                if(var != std::string::npos)
                {
                    var = line.find(", ", var) + 2;
                    varEnd = line.find(", ", var) - var;
                    std::string partName = line.substr(var, varEnd);
                    part.second->textureOffsetX = atoi(partName.c_str());
                    var = line.find(", ", var) + 2;
                    varEnd = line.find(")") - var;
                    partName = line.substr(var, varEnd);
                    part.second->textureOffsetY = atoi(partName.c_str());
                }
                //Wow this isn't working right at all
                var = line.find(part.first + ".addBox", var + 1);
                if(var != std::string::npos)
                {
                    var = line.find("(", var) + 1;
//                    if(line[var] == '\"')
                        var = line.find_first_of("1234567890-.", var);
                    float nums[6];
                    for(int i = 0; i < 6; i++)
                    {
                        varEnd = endOfNum(line, var) - var;
                        std::string value = line.substr(var, varEnd).c_str();
                        std::cout << value << " | " << var << " | " << varEnd << "\n";
                        nums[i] = atof(value.c_str());
                        var = line.find(", ", var) + 2;
                    }
                    part.second->addBox(nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]);
                }
                var = line.find(part.first + ".setRotationPoint", var + 1);
                if(var != std::string::npos)
                {
                    var = line.find("(", var) + 1;
                    float nums[3];
                    for(int i = 0; i < 3; i++)
                    {
                        varEnd = endOfNum(line, var) - var;
                        std::string value = line.substr(var, varEnd).c_str();
                        std::cout << value << " | " << var << " | " << varEnd << "\n";
                        nums[i] = atof(value.c_str());
                        var = line.find(", ", var) + 2;
                    }
                    part.second->setRotationPoint(nums[0], nums[1], nums[2]);
                }
            }
        }
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
