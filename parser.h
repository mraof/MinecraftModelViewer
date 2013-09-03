#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "render.h"
#include <string>

void createModelFromSource(Model *model, std::string &src);
void createSourceFromModel(Model *model, std::string &src);

#endif // PARSER_H_INCLUDED
